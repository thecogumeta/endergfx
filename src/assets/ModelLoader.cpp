#include "endergfx/ModelLoader.hpp"
#include "endergfx/Log.hpp"
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include <tiny_obj_loader.h>

namespace endergfx {

std::vector<Mesh> ModelLoader::loadOBJ(const std::string &path) {
  tinyobj::ObjReaderConfig config;
  config.triangulate = true;

  tinyobj::ObjReader reader;
  if (!reader.ParseFromFile(path, config)) {
    if (!reader.Error().empty()) {
      log(LogLevel::Error, "ModelLoader: " + reader.Error());
    }
    return {};
  }

  if (!reader.Warning().empty()) {
    log(LogLevel::Warning, "ModelLoader: " + reader.Warning());
  }

  const auto &attrib = reader.GetAttrib();
  const auto &shapes = reader.GetShapes();

  std::vector<Mesh> meshes;

  for (const auto &shape : shapes) {
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    std::unordered_map<std::string, uint16_t> uniqueVertices;

    for (size_t faceStart = 0; faceStart < shape.mesh.indices.size();
         faceStart += 3) {
      const std::array<int, 3> order = {0, 2, 1};

      for (int k : order) {
        const auto &index = shape.mesh.indices[faceStart + k];

        Vertex vertex{};
        vertex.x = attrib.vertices[3 * index.vertex_index + 0];
        vertex.y = attrib.vertices[3 * index.vertex_index + 1];
        vertex.z = attrib.vertices[3 * index.vertex_index + 2];

        if (index.normal_index >= 0) {
          vertex.nx = attrib.normals[3 * index.normal_index + 0];
          vertex.ny = attrib.normals[3 * index.normal_index + 1];
          vertex.nz = attrib.normals[3 * index.normal_index + 2];
        }

        if (index.texcoord_index >= 0) {
          vertex.u = attrib.texcoords[2 * index.texcoord_index + 0];
          vertex.v = attrib.texcoords[2 * index.texcoord_index + 1];
        }

        vertex.abgr = 0xffffffff;

        std::string key = std::to_string(index.vertex_index) + "/" +
                          std::to_string(index.normal_index) + "/" +
                          std::to_string(index.texcoord_index);

        auto it = uniqueVertices.find(key);
        if (it != uniqueVertices.end()) {
          indices.push_back(it->second);
        } else {
          uint16_t newIndex = static_cast<uint16_t>(vertices.size());
          vertices.push_back(vertex);
          uniqueVertices[key] = newIndex;
          indices.push_back(newIndex);
        }
      }
    }

    if (!vertices.empty() && !indices.empty()) {
      log(LogLevel::Debug, "Mesh: " + std::to_string(vertices.size()) +
                               " vertices, " + std::to_string(indices.size()) +
                               " indices");
      meshes.emplace_back(vertices, indices);
    }
  }

  if (meshes.empty()) {
    log(LogLevel::Error, "ModelLoader: OBJ file produced no geometry: " + path);
  }

  return meshes;
}

} // namespace endergfx
