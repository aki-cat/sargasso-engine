import sys
import os
from pathlib import Path

PLATFORM_WINDOWS = "win32"

LIB_GLFW_NAME = "glfw3"
LIB_GLFW_SOURCE_PATH = Path(Path.cwd(), "third_party", "glfw")
LIB_GLFW_INSTALL_PATH = Path(Path.cwd(), "lib", LIB_GLFW_NAME)
LIB_GLFW_BUILD_PATH = Path(LIB_GLFW_SOURCE_PATH, "build")
LIB_GLFW_CMAKE_FLAGS = """-G 'Unix Makefiles' \
                          -DCMAKE_INSTALL_PREFIX='%s' \
                          -B '%s'""" % (LIB_GLFW_INSTALL_PATH, LIB_GLFW_BUILD_PATH)
LIB_GLFW_MAKE_FLAGS = "-j4 -C %s" % (LIB_GLFW_BUILD_PATH)
LIB_GLFW_PKG_CONFIG = Path(LIB_GLFW_INSTALL_PATH,
                           "lib", "pkgconfig", "glfw3.pc")
LIB_GLFW_BUILD_FLAG_CMD = "pkg-config --cflags --libs --static %s" % LIB_GLFW_PKG_CONFIG


def build() -> None:
    if sys.platform != PLATFORM_WINDOWS:
        if os.system("cmake %s '%s'" %
                     (LIB_GLFW_CMAKE_FLAGS,
                      LIB_GLFW_SOURCE_PATH)) != 0:
            raise Exception("CMake step failed")
        if os.system("make %s" % LIB_GLFW_MAKE_FLAGS) != 0:
            raise Exception("Make step failed")
        if os.system("make %s install" % LIB_GLFW_MAKE_FLAGS) != 0:
            raise Exception("Install step failed")
    else:
        raise Exception("Building on Windows is not yet implemented")
