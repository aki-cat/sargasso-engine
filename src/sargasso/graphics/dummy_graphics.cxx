
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

const char* DummyGraphics::getVersion() const {
    return VERSION;
}

}  // namespace graphics
}  // namespace sargasso
