#include "sargasso/filesystem/filesystem.h"

#include "sargasso/common/log.h"
#include "sargasso/common/typedefs.h"
#include "sargasso/config.h"

#include <exception>
#include <filesystem>
#include <physfs.h>
#include <sstream>

namespace sargasso {
namespace filesystem {

static const char* GAME_ROOT = "GameRoot/";

static const common::Log logger("Filesystem");

static bool initPhysfs(const char* argv0);
static bool deinitPhysfs();

static bool setGameDirectory(const FileSystem&);
static bool testGameDirectory(FileSystem&);
static bool setUserDirectory(const FileSystem&);
static bool testUserDirectory(FileSystem&);

#define S(x)      #x
#define SS(x)     S(x)
#define GET_WHERE std::string(__FILE__ ":" SS(__LINE__) " in fn ") + std::string(__func__) + "()"
#define CHECK_SUCCESS(success) \
    if (!(success)) throwErr(GET_WHERE)

static std::string errCode;

static void throwErr(const std::string& where) {
    const PHYSFS_ErrorCode errCode = PHYSFS_getLastErrorCode();
    const char* errDesc = PHYSFS_getErrorByCode(errCode);
    std::stringstream stream;
    stream << where << " Error[" << errCode << "] " << errDesc << std::endl;
    throw std::runtime_error(stream.str());
}

#if SARGASSO_WINDOWS
static std::string toUTF8(const std::wstring& wstr) {
    std::string strTo;
    char* szTo = new char[wstr.length() + 1];
    szTo[wstr.size()] = '\0';
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int) wstr.length(), NULL, NULL);
    std::string out = szTo;
    delete[] szTo;
    return out;
}
#endif

struct FileReference {
    const void* ptr;
    operator const void*() {
        return ptr;
    }
    operator PHYSFS_File*() {
        return (PHYSFS_File*) ptr;
    }
};

static std::string extractPlatformExecutablePath(const char* argv0) {
    logger.info("Extract platform-specific executable path...");
    std::string executablePath(reinterpret_cast<const char*>(argv0));
#if SARGASSO_WINDOWS
    // Shamelessly stolen and adapted from Love2D's Filesystem.cpp @ github.com/love2d/love
    wchar_t buffer[MAX_PATH + 1] = {0};
    if (GetModuleFileNameW(nullptr, buffer, MAX_PATH) == 0) {
        logger.error("WINDOWS: Unable to fetch filename!?");
        throw;
    }
    executablePath = toUTF8(buffer);
    logger.info("Executable path: %s", executablePath.c_str());
#endif

    return executablePath;
}

FileSystemInitializer::FileSystemInitializer(const char* argv0) {
    CHECK_SUCCESS(initPhysfs(argv0));
}

FileSystemInitializer::~FileSystemInitializer() {
    CHECK_SUCCESS(deinitPhysfs());
}

FileSystem::FileSystem(const ProjectConfig& config, const char* argv0)
    : FileSystemInitializer(argv0),
      _projectConfig(config),
      _executablePath(extractPlatformExecutablePath(argv0)),
      _prefsDirectory(
          PHYSFS_getPrefDir(_projectConfig.organizationName, _projectConfig.projectName)) {
    CHECK_SUCCESS(setGameDirectory(*this));
    CHECK_SUCCESS(testGameDirectory(*this));
    CHECK_SUCCESS(setUserDirectory(*this));
    CHECK_SUCCESS(testUserDirectory(*this));
}

FileSystem::~FileSystem() {
    if (_openedFiles.empty()) {
        return;
    }

    logger.warning(
        "%d unclosed files found! Remember to always close files after you're done with them.",
        _openedFiles.size());

    for (const auto& fileHandle : _openedFiles) {
        const void* handle = fileHandle.first;
        const FileHandle& fileInfo = fileHandle.second;

        std::string modeName;
        if (fileInfo.mode == FileMode::kRead) {
            modeName = "read";
        } else if (fileInfo.mode == FileMode::kWrite) {
            modeName = "write";
        } else {
            modeName = "append";
        }
        logger.warning("--> Closing file '%s (%s)'...", fileInfo.filePath.c_str(),
                       modeName.c_str());
        CHECK_SUCCESS(PHYSFS_close(FileReference{handle}));
    }
}

// public API

std::string FileSystem::getExecutableDirectory() const {
    std::filesystem::path execPath = std::filesystem::path(_executablePath).parent_path();
#if SARGASSO_WINDOWS
    return toUTF8(execPath.native());
#else
    return execPath.native();
#endif
}

std::string FileSystem::getUserDirectory() const {
    return _prefsDirectory;
}

std::string FileSystem::readFile(const std::string& filePath, size_t maxByteCount) {
    auto fileHandle = openFile(filePath, FileMode::kRead);
    char* buffer = new char[maxByteCount];

    CHECK_SUCCESS(PHYSFS_readBytes(FileReference{fileHandle.handle}, buffer, maxByteCount) > 0);
    CHECK_SUCCESS(closeFile(fileHandle));

    const std::string result = buffer;
    delete[] buffer;
    return result;
}

void FileSystem::writeFile(const std::string& filePath, const char* data, size_t maxByteCount) {
    const auto fileHandle = openFile(filePath, FileMode::kWrite);

    CHECK_SUCCESS(PHYSFS_writeBytes(FileReference{fileHandle.handle}, data, maxByteCount) ==
                  maxByteCount);
    CHECK_SUCCESS(closeFile(fileHandle));
}

FileHandle FileSystem::openFile(const std::string& path, FileMode mode) {
    logger.info("Opening file: %s...", path.c_str());
    PHYSFS_File* openedFile = nullptr;
    const char* filepath = path.c_str();

    switch (mode) {
        case FileMode::kRead:
            openedFile = PHYSFS_openRead(filepath);
            break;
        case FileMode::kWrite:
            openedFile = PHYSFS_openWrite(filepath);
            break;
        case FileMode::kAppend:
            openedFile = PHYSFS_openAppend(filepath);
            break;
        default:
            break;
    }

    CHECK_SUCCESS(openedFile);
    FileHandle fileHandle = FileHandle(path, mode, openedFile);
    _openedFiles.emplace(openedFile, fileHandle);
    return fileHandle;
}

bool FileSystem::closeFile(const FileHandle& fileHandle) {
    _openedFiles.erase(fileHandle.handle);
    return PHYSFS_close(FileReference{fileHandle.handle});
}

// private

// Set game project directory, where we'll read the game's definition data from.
static bool setGameDirectory(const FileSystem& fileSystem) {
    if (!PHYSFS_isInit()) {
        return false;
    }

    const std::string baseDir = PHYSFS_getBaseDir();
    logger.info("base dir: %s", baseDir.c_str());

    if (!PHYSFS_mount(baseDir.c_str(), GAME_ROOT, 0)) {
        return false;
    }
    return true;
}

// Test the game project directory by reading a default shader file.
static bool testGameDirectory(FileSystem& fileSystem) {
    if (!PHYSFS_isInit()) {
        return false;
    }
    const std::string testFilePath = std::string(GAME_ROOT) + "shaders/vertex_default.glsl";
    const char* filePathRaw = testFilePath.c_str();

    if (PHYSFS_exists(filePathRaw)) {
        logger.debug("Test file found @ `%s` !", filePathRaw);
    }

    std::string contents = fileSystem.readFile(testFilePath, 1024);
    logger.debug("%s contents:\n%s\n", filePathRaw, contents.c_str());
    return true;
}

// Set the user directory, where we'll write the game's user data (like saves and preferences).
static bool setUserDirectory(const FileSystem& fileSystem) {
    if (!PHYSFS_isInit()) {
        return false;
    }

    std::string prefsDirPath = fileSystem.getUserDirectory();
    const char* prefsDirRaw = prefsDirPath.c_str();
    logger.info("UserPath: %s", prefsDirRaw);

    if (!PHYSFS_exists(prefsDirRaw)) {
        PHYSFS_mkdir(prefsDirRaw);
    }

    if (!PHYSFS_setWriteDir(prefsDirRaw)) {
        return false;
    }

    if (!PHYSFS_mount(prefsDirRaw, nullptr, 0)) {
        return false;
    }

    return true;
}

// Test creating a file in user directory and write some data into it.
static bool testUserDirectory(FileSystem& fileSystem) {
    if (!PHYSFS_isInit()) {
        return false;
    }
    const std::string testFilePath = "prefs.txt";
    const std::string writeBuff = "{ \"hello\": \"world\" }\n";

    fileSystem.writeFile(testFilePath, writeBuff.c_str(), writeBuff.size());
    logger.debug("Writing successful! Check written contents @ %s", testFilePath.c_str());

    return true;
}

static bool initPhysfs(const char* argv0) {
    return bool(PHYSFS_init(argv0));
}

static bool deinitPhysfs() {
    return PHYSFS_isInit() && PHYSFS_deinit();
}

#undef CHECK_SUCCESS
#undef GET_WHERE
#undef SS
#undef S

}  // namespace filesystem
}  // namespace sargasso
