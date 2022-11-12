#ifndef SARGASSO_FILESYSTEM_FILESYSTEM_H_
#define SARGASSO_FILESYSTEM_FILESYSTEM_H_

#include "sargasso/common/typedefs.h"
#include "sargasso/project_config.h"

#include <filesystem>
#include <unordered_map>

namespace sargasso {
namespace filesystem {

enum FileMode { kRead, kWrite, kAppend };

// This immutable instance is just as a means to get internally stored file.
struct FileHandle {
    FileHandle(const std::filesystem::path& filePath, FileMode mode, void* handle)
        : filePath(filePath), mode(mode), handle(handle) {}
    FileHandle() = delete;

    const std::filesystem::path filePath;
    const FileMode mode;
    const void* handle;
};

class FileSystemInitializer {
   private:
    FileSystemInitializer(const char* argv0);
    ~FileSystemInitializer();

    friend class FileSystem;
};

class FileSystem : public FileSystemInitializer {
   public:
    FileSystem(const ProjectConfig& config, const char* argv0);
    ~FileSystem();

    FileSystem() = delete;
    FileSystem(const FileSystem&) = delete;
    FileSystem(const FileSystem&&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;
    FileSystem&& operator=(const FileSystem&&) = delete;

    // PUBLIC API

    // Return executable directory path.
    const std::filesystem::path& getExecutableDirectory() const;
    // Return user directory path.
    const std::filesystem::path& getUserDirectory() const;

    bool isFile(const std::filesystem::path& path) const;
    bool isDirectory(const std::filesystem::path& path) const;

    /**
     * @brief
     *
     * @param path
     * @param mode
     * @return FileHandle
     */
    FileHandle openFile(const std::filesystem::path& path, FileMode mode);
    bool closeFile(const FileHandle& fileHandle);

    // These two are for common operations, but they might not be the best in terms of efficiency.

    /**
     * @brief Reads a file and return its contents up to 'maxByteCount' in length.
     * Throws if file does not exist.
     *
     * @param filePath
     * @param maxByteCount
     * @return std::string
     */
    const std::string readFile(const std::filesystem::path& filePath, size_t maxByteCount);

    // Writes to a file up to 'byteCount' bytes. If file does not exist, it is created.
    void writeFile(const std::filesystem::path& filePath, const char* data, size_t byteCount);

   private:
    const ProjectConfig& _projectConfig;
    const std::filesystem::path _executablePath;
    const std::filesystem::path _prefsDirectory;
    std::unordered_map<const void*, const FileHandle> _openedFiles;
};

}  // namespace filesystem
}  // namespace sargasso

#endif  // SARGASSO_FILESYSTEM_FILESYSTEM_H_
