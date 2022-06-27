#ifndef SARGASSO_FILE_SYSTEM_H_
#define SARGASSO_FILE_SYSTEM_H_

#include "sargasso/common/typedefs.h"
#include "sargasso/project_config.h"

#include <filesystem>

namespace sargasso {

class FileSystem {
   public:
    FileSystem(const ProjectConfig& config, const char* argv0);
    ~FileSystem();

    FileSystem() = delete;
    FileSystem(const FileSystem&) = delete;
    FileSystem(const FileSystem&&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;
    FileSystem&& operator=(const FileSystem&&) = delete;

    // API
   private:
    static const std::filesystem::path GAME_ROOT;
    const ProjectConfig& _projectConfig;
    std::filesystem::path _prefsDirectory;
    std::filesystem::path _executablePath;

    bool init(const char* argv0);
    bool setGameDirectory();
    bool testGameDirectory();
    bool setUserDirectory();
    bool testUserDirectory();
};

}  // namespace sargasso

#endif  // SARGASSO_FILE_SYSTEM_H_
