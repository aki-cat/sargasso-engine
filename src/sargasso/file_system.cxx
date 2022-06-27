#include "sargasso/file_system.h"

#include "sargasso/common/log.h"
#include "sargasso/common/typedefs.h"
#include "sargasso/config.h"

#include <exception>
#include <filesystem>
#include <physfs.h>

namespace sargasso {

const std::filesystem::path FileSystem::GAME_ROOT = "GameRoot/";

static const common::Log logger("Filesystem");
static std::string errCode;

constexpr void checkSuccess(bool success) {
    if (!success) {
        errCode = std::to_string(PHYSFS_getLastErrorCode());
        throw std::runtime_error("Error: " + errCode);
    }
}

FileSystem::FileSystem(const ProjectConfig& config, const char* argv0) : _projectConfig(config) {
    checkSuccess(init(argv0));
    checkSuccess(setGameDirectory());
    checkSuccess(testGameDirectory());
    checkSuccess(setUserDirectory());
    checkSuccess(testUserDirectory());
}

FileSystem::~FileSystem() {
    // TBD: handle lingering write operations

    if (PHYSFS_isInit()) {
        PHYSFS_deinit();
    }
}

bool FileSystem::init(const char* argv0) {
    if (!PHYSFS_init(argv0)) {
        return false;
    }

    // TBD: platform specific
    _executablePath = argv0;

    return true;
}

bool FileSystem::setGameDirectory() {
    if (!PHYSFS_isInit()) {
        return false;
    }

    const char* executableDir = _executablePath.remove_filename().c_str();
    logger.debug("GamePath: %s", executableDir);

    if (!PHYSFS_mount(executableDir, GAME_ROOT.c_str(), 0)) {
        return false;
    }
    return true;
}

bool FileSystem::testGameDirectory() {
    if (!PHYSFS_isInit()) {
        return false;
    }

    const std::filesystem::path fragShaderPath = GAME_ROOT / "shaders/fragment_default.glsl";
    if (PHYSFS_exists(fragShaderPath.c_str())) {
        logger.debug("Fragment shader file found @ `%s` !", fragShaderPath.c_str());
    }

    PHYSFS_File* fragShaderFile = PHYSFS_openRead(fragShaderPath.c_str());
    if (fragShaderFile == NULL) {
        return false;
    }
    logger.debug("Opened '%s' for reading!", fragShaderPath.c_str());

    char readBuffer[1024];
    long byteCount = PHYSFS_readBytes(fragShaderFile, readBuffer, 1024);
    if (byteCount <= 0) {
        return false;
    }
    logger.debug("Buffered first %ld bytes of '%s'!", byteCount, fragShaderPath.c_str());

    if (!PHYSFS_close(fragShaderFile)) {
        return false;
    }
    logger.debug("Closed '%s'!", fragShaderPath.c_str());
    logger.debug("%s contents:\n%s\n", fragShaderPath.c_str(), readBuffer);
    return true;
}

bool FileSystem::setUserDirectory() {
    if (!PHYSFS_isInit()) {
        return false;
    }

    _prefsDirectory =
        PHYSFS_getPrefDir(_projectConfig.organizationName, _projectConfig.projectName);
    if (!PHYSFS_exists(_prefsDirectory.c_str())) {
        PHYSFS_mkdir(_prefsDirectory.c_str());
    }

    logger.debug("UserPath: %s", _prefsDirectory.c_str());

    if (!PHYSFS_setWriteDir(_prefsDirectory.c_str())) {
        return false;
    }

    if (!PHYSFS_mount(_prefsDirectory.c_str(), nullptr, 0)) {
        return false;
    }

    return true;
}

// create a file in user directory and write some data into it
bool FileSystem::testUserDirectory() {
    if (!PHYSFS_isInit()) {
        return false;
    }
    const std::filesystem::path testFilePath = "prefs.txt";

    logger.debug("Opening '%s' for writing...", testFilePath.c_str());
    PHYSFS_File* testWriteFile = PHYSFS_openWrite(testFilePath.c_str());
    if (testWriteFile == NULL) {
        return false;
    }
    logger.debug("Opened '%s' for writing!", testFilePath.c_str());

    logger.debug("Writing into '%s'...", testFilePath.c_str());
    const char* writeBuff = "{ \"hello\": \"world\" }\n";
    if (PHYSFS_writeBytes(testWriteFile, writeBuff, std::strlen(writeBuff)) <= 0) {
        return false;
    }

    if (!PHYSFS_close(testWriteFile)) {
        return false;
    }
    logger.debug("Writing successful! Check written contents @ %s", testFilePath.c_str());

    return true;
}

}  // namespace sargasso
