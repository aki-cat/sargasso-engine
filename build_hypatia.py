import sys
import os
from pathlib import Path

LIB_HYPATIA_NAME = "hypatia"
LIB_HYPATIA_SOURCE_PATH = Path(
    Path.cwd(), "third_party", "hypatia", "hypatia.h")
LIB_HYPATIA_INSTALL_PATH = Path(Path.cwd(), "lib", LIB_HYPATIA_NAME)
LIB_HYPATIA_HEADER_PATH = Path(LIB_HYPATIA_INSTALL_PATH, "hypatia.h")


def build() -> None:
    if os.system("mkdir -p %s" % LIB_HYPATIA_INSTALL_PATH) != 0:
        raise Exception("Make directory step failed")
    if os.system("cp %s %s" % (LIB_HYPATIA_SOURCE_PATH, LIB_HYPATIA_HEADER_PATH)) != 0:
        raise Exception("Install step failed")
