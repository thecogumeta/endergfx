#include <functional>
#include <string>

namespace endergfx {

enum class LogLevel { Debug, Info, Warning, Error };

using LogCallback =
    std::function<void(LogLevel level, const std::string &message)>;

void setLogCallback(LogCallback callback);
void log(LogLevel level, const std::string &message);

} // namespace endergfx
