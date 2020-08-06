import build_glfw as GLFWBuilder
from pathlib import Path

import os

EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 5)

SOURCE_PWD: Path = Path.cwd()
SOURCE_DIRECTORY: Path = Path(SOURCE_PWD, "src")
SOURCE_CXX_FILES: str = \
    [str(file_name) for file_name in SOURCE_DIRECTORY.glob("**/*.cc")]

PROJECT_NAME: str = "SargassoEngine"
BINARY_PATH: str = str(Path(SOURCE_PWD, "bin", PROJECT_NAME))

# GLFW Library
GLFWBuilder.build()

# Environment setup
env = Environment(
    CCFLAGS=["-O0", "-Werror", "-Wall",
             "-pedantic", "-std=c++11", "-DGL_SILENCE_DEPRECATION"],
    CPPPATH=[str(SOURCE_DIRECTORY)])

env.ParseConfig(GLFWBuilder.LIB_GLFW_BUILD_FLAG_CMD)
env.AppendUnique(FRAMEWORKS=["OpenGL"])
env.Program(BINARY_PATH, SOURCE_CXX_FILES)
