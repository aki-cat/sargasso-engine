import build_glfw as GLFWBuilder
from pathlib import Path

import os

EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 5)

SOURCE_PWD = Path.cwd()
SOURCE_CXX_FILES = \
    [str(file_name) for file_name in Path(SOURCE_PWD, "src").glob("**/*.cc")]

# GLFW Library
GLFWBuilder.build()

# Environment setup
env = Environment(
    CCFLAGS=["-O0", "-Werror", "-Wall"])

env.ParseConfig(GLFWBuilder.LIB_GLFW_BUILD_FLAG_CMD)
env.Program("bin/coffee-engine", SOURCE_CXX_FILES)
