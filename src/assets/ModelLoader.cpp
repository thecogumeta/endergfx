#include "endergfx/ModelLoader.hpp"
#include "endergfx/Log.hpp"

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace endergfx {

namespace {

struct RawIndex {
  int v = 0;
  int vt = 0;
  int vn = 0;

  bool operator==(const RawIndex &other) const {
    return v == other.v && vt == other.vt && vn == other.vn;
  }
};

struct RawIndexHash {
  size_t operator()(const RawIndex &idx) const {
    return std::hash<int>()(idx.v) ^ (std::hash<int>()(idx.vt) << 1) ^
           (std::hash<int>()(idx.vn) << 2);
  }
};

RawIndex parseFaceToken(const std::string &token) {
  RawIndex idx;
  size_t firstSlash = token.find('/');

  if (firstSlash == std::string::npos) {
    idx.v = std::stoi(token);
    return idx;
  }

  idx.v = std::stoi(token.substr(0, firstSlash));

  size_t secondSlash = token.find('/', firstSlash + 1);
  if (secondSlash == std::string::npos) {
    idx.vt = std::stoi(token.substr(firstSlash + 1));
    return idx;
  }

  std::string vtStr =
      token.substr(firstSlash + 1, secondSlash - firstSlash - 1);
  if (!vtStr.empty()) {
    idx.vt = std::stoi(vtStr);
  }

  std::string vnStr = token.substr(secondSlash + 1);
  if (!vnStr.empty()) {
    idx.vn = std::stoi(vnStr);
  }

  return idx;
}

struct GroupBuilder {
  std::vector<Vertex> vertices;
  std::vector<uint16_t> indices;
  std::unordered_map<RawIndex, uint16_t, RawIndexHash> uniqueVertices;
};

void recenterGroup(GroupBuilder &group) {
  if (group.vertices.empty()) {
    return;
  }

  float minX = group.vertices[0].x, maxX = group.vertices[0].x;
  float minY = group.vertices[0].y, maxY = group.vertices[0].y;
  float minZ = group.vertices[0].z, maxZ = group.vertices[0].z;

  for (const auto &v : group.vertices) {
    minX = std::min(minX, v.x);
    maxX = std::max(maxX, v.x);
    minY = std::min(minY, v.y);
    maxY = std::max(maxY, v.y);
    minZ = std::min(minZ, v.z);
    maxZ = std::max(maxZ, v.z);
  }

  float cx = (minX + maxX) * 0.5f;
  float cy = (minY + maxY) * 0.5f;
  float cz = (minZ + maxZ) * 0.5f;

  for (auto &v : group.vertices) {
    v.x -= cx;
    v.y -= cy;
    v.z -= cz;
  }
}

} // namespace

std::vector<Mesh> ModelLoader::loadOBJ(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    log(LogLevel::Error, "ModelLoader: failed to open OBJ file: " + path);
    return {};
  }

  std::vector<float> positions;
  std::vector<float> texcoords;
  std::vector<float> normals;

  std::vector<GroupBuilder> groups;
  groups.emplace_back();

  auto resolveVertex = [&](const RawIndex &raw,
                           GroupBuilder &group) -> uint16_t {
    auto it = group.uniqueVertices.find(raw);
    if (it != group.uniqueVertices.end()) {
      return it->second;
    }

    Vertex vertex{};

    if (raw.v != 0) {
      int i = (raw.v > 0) ? (raw.v - 1)
                          : static_cast<int>(positions.size() / 3) + raw.v;
      vertex.x = positions[i * 3 + 0];
      vertex.y = positions[i * 3 + 1];
      vertex.z = positions[i * 3 + 2];
    }

    if (raw.vt != 0) {
      int i = (raw.vt > 0) ? (raw.vt - 1)
                           : static_cast<int>(texcoords.size() / 2) + raw.vt;
      vertex.u = texcoords[i * 2 + 0];
      vertex.v = texcoords[i * 2 + 1];
    }

    if (raw.vn != 0) {
      int i = (raw.vn > 0) ? (raw.vn - 1)
                           : static_cast<int>(normals.size() / 3) + raw.vn;
      vertex.nx = normals[i * 3 + 0];
      vertex.ny = normals[i * 3 + 1];
      vertex.nz = normals[i * 3 + 2];
    }

    vertex.abgr = 0xffffffff;

    uint16_t index = static_cast<uint16_t>(group.vertices.size());
    group.vertices.push_back(vertex);
    group.uniqueVertices[raw] = index;
    return index;
  };

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix == "v") {
      float x, y, z;
      iss >> x >> y >> z;
      positions.push_back(x);
      positions.push_back(y);
      positions.push_back(z);
    } else if (prefix == "vt") {
      float u, v;
      iss >> u >> v;
      texcoords.push_back(u);
      texcoords.push_back(v);
    } else if (prefix == "vn") {
      float x, y, z;
      iss >> x >> y >> z;
      normals.push_back(x);
      normals.push_back(y);
      normals.push_back(z);
    } else if (prefix == "o" || prefix == "g") {
      if (!groups.back().indices.empty()) {
        groups.emplace_back();
      }
    } else if (prefix == "f") {
      std::vector<RawIndex> faceIndices;
      std::string token;
      while (iss >> token) {
        faceIndices.push_back(parseFaceToken(token));
      }

      if (faceIndices.size() < 3) {
        continue;
      }

      GroupBuilder &group = groups.back();
      for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
        group.indices.push_back(resolveVertex(faceIndices[0], group));
        group.indices.push_back(resolveVertex(faceIndices[i], group));
        group.indices.push_back(resolveVertex(faceIndices[i + 1], group));
      }
    }
  }

  std::vector<Mesh> meshes;
  for (auto &group : groups) {
    if (group.vertices.empty() || group.indices.empty()) {
      continue;
    }
    recenterGroup(group);
    meshes.emplace_back(group.vertices, group.indices);
  }

  if (meshes.empty()) {
    log(LogLevel::Error, "ModelLoader: OBJ file produced no geometry: " + path);
  }

  return meshes;
}

} // namespace endergfx
