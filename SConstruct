import build_glfw as GLFWBuilder
import build_glm as GLMBuilder
import build_hypatia as HypatiaBuilder
from pathlib import Path

import os


EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 5)


SOURCE_PWD: Path = Path.cwd()
SOURCE_DIRECTORY: Path = Path(SOURCE_PWD, "src")
SOURCE_CXX_FILES: list = \
    [str(file_name) for file_name in SOURCE_DIRECTORY.glob("**/*.cc")]
SOURCE_CXX_FILES_MAIN = str(Path(SOURCE_DIRECTORY, "main.cc"))


TEST_SOURCE_DIRECTORY: Path = Path(SOURCE_PWD, "tests")
TEST_SOURCE_CXX_FILES: list = \
    [str(file_name) for file_name in TEST_SOURCE_DIRECTORY.glob("**/*.cc")]
TEST_SOURCE_CXX_FILES = TEST_SOURCE_CXX_FILES + SOURCE_CXX_FILES
TEST_SOURCE_CXX_FILES.remove(SOURCE_CXX_FILES_MAIN)


PROJECT_NAME: str = "SargassoEngine"
BINARY_PATH: str = str(Path(SOURCE_PWD, "bin", PROJECT_NAME))
TESTS_PATH: str = str(Path(SOURCE_PWD, "bin", "RunTests"))


CXXFLAGS = [
    "-O0", "-Wall", "-Wignored-qualifiers", "-Wtype-limits", "-Wcast-qual", "-Wcast-align", "-Wundef", "-Wc++14-compat", "-Wpedantic", "-Wbad-function-cast", "-Wconversion", "-Wparentheses", "-Wempty-body",
    "-std=c++14", "-DGL_SILENCE_DEPRECATION"]


# GLFW Library
LIB_GLEW_BUILD_FLAG_CMD = "pkg-config glew --libs --static"
GLFWBuilder.build()

# GLM Library
GLMBuilder.build()

# Hypatia Library
HypatiaBuilder.build()

# Environment setup
env = Environment(
    CCFLAGS=CXXFLAGS,
    CPPPATH=[str(SOURCE_DIRECTORY)],
    parse_flags=["-isystem" + GLMBuilder.LIB_GLM_INCLUDE_PATH,
                 "-isystem" + HypatiaBuilder.LIB_HYPATIA_INCLUDE_PATH])

env.ParseConfig(GLFWBuilder.LIB_GLFW_BUILD_FLAG_CMD)
env.ParseConfig(LIB_GLEW_BUILD_FLAG_CMD)
env.AppendUnique(FRAMEWORKS=["OpenGL"])
env.Program(BINARY_PATH, SOURCE_CXX_FILES)

env.Program(TESTS_PATH, TEST_SOURCE_CXX_FILES)
