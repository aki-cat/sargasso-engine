import build_glfw as GLFWBuilder
import build_glm as GLMBuilder
from pathlib import Path

import os

EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 5)

SOURCE_PWD: Path = Path.cwd()
SOURCE_DIRECTORY: Path = Path(SOURCE_PWD, "src")
SOURCE_CXX_FILES: str = \
    [str(file_name) for file_name in SOURCE_DIRECTORY.glob("**/*.cc")]

TEST_SOURCE_DIRECTORY: Path = Path(SOURCE_PWD, "tests")
TEST_SOURCE_CXX_FILES: str = \
    [str(file_name) for file_name in TEST_SOURCE_DIRECTORY.glob("**/*.cc")]

PROJECT_NAME: str = "SargassoEngine"
BINARY_PATH: str = str(Path(SOURCE_PWD, "bin", PROJECT_NAME))
TESTS_PATH: str = str(Path(SOURCE_PWD, "bin", "RunTests"))

LIB_GLEW_BUILD_FLAG_CMD = "pkg-config glew --libs --static"

CXXFLAGS = [
    "-O0", "-Wall", "-Wignored-qualifiers", "-Wtype-limits", "-Wcast-qual", "-Wcast-align", "-Wundef", "-Wc++14-compat", "-Wpedantic", "-Wbad-function-cast", "-Wconversion", "-Wparentheses", "-Wempty-body",
    "-std=c++14", "-DGL_SILENCE_DEPRECATION"]

# GLFW Library
GLFWBuilder.build()

# GLM Library
GLMBuilder.build()

# Environment setup
env = Environment(
    CCFLAGS=CXXFLAGS,
    CPPPATH=[str(SOURCE_DIRECTORY)],
    parse_flags="-I" + GLMBuilder.LIB_GLM_INCLUDE_PATH)

env.ParseConfig(GLFWBuilder.LIB_GLFW_BUILD_FLAG_CMD)
env.ParseConfig(LIB_GLEW_BUILD_FLAG_CMD)
env.AppendUnique(FRAMEWORKS=["OpenGL"])
env.Program(BINARY_PATH, SOURCE_CXX_FILES)

env.Program(TESTS_PATH, TEST_SOURCE_CXX_FILES)
