import os
from pathlib import Path

LIB_GLM_NAME = "glm"
LIB_GLM_SOURCE_PATH = str(Path(Path.cwd(), "third_party",
                               LIB_GLM_NAME, LIB_GLM_NAME))
LIB_GLM_INCLUDE_PATH = str(Path(Path.cwd(), "lib", LIB_GLM_NAME))


def build() -> None:
    if os.system("cp -R %s %s" % (LIB_GLM_SOURCE_PATH, LIB_GLM_INCLUDE_PATH)) != 0:
        raise Exception("GLM copy failed!")
