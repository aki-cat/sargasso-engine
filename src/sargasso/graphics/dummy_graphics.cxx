
#include "sargasso/graphics/dummy_graphics.h"

namespace sargasso {
namespace graphics {

const char* DummyGraphics::NAME = "Dummy";
const char* DummyGraphics::VERSION = "v1.0";

bool DummyGraphics::initialize(void* proc_address) {
    return false;
}

void DummyGraphics::setViewport(int x, int y, uint32_t width, uint32_t height) {
    // empty on purpose
}

void DummyGraphics::setClearColor(Color color) {
    // empty on purpose
}

void DummyGraphics::clear() {
    // empty on purpose
}

const char* DummyGraphics::getName() const {
    return NAME;
}

const char* DummyGraphics::getVersionString() const {
    return VERSION;
}

const int DummyGraphics::getVersionMajor() const {
    return 1;
};

const int DummyGraphics::getVersionMinor() const {
    return 0;
};

}  // namespace graphics
}  // namespace sargasso
