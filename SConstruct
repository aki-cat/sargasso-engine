from pathlib import Path
import os

EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 5)

SOURCE_PWD = Path.cwd()
SOURCE_CXX_FILES = \
    [str(file_name) for file_name in Path(SOURCE_PWD, "src").glob("**/*.cc")]

# GLFW Library
LIB_GLFW_PATH = \
    str(Path(SOURCE_PWD, "lib", "glfw"))
LIB_PKG_CONFIG = \
    str(Path(LIB_GLFW_PATH, "lib", "pkgconfig", "glfw3.pc"))


# Environment setup
env = Environment(
    CCFLAGS=["-O0", "-Werror", "-Wall"])

env.ParseConfig("pkg-config --cflags --libs --static " + LIB_PKG_CONFIG)
env.Program("bin/coffee-engine", SOURCE_CXX_FILES)
