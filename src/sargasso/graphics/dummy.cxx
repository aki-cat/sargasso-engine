
#include "sargasso/graphics/dummy.h"

#include <sml/color.h>

namespace sargasso {
namespace graphics {

bool DummyGraphics::initialize() {
    return false;
}

void DummyGraphics::setViewport(int x, int y, uint32_t width, uint32_t height) {
    // empty on purpose
}

void DummyGraphics::setClearColor(sml::Color color) {
    // empty on purpose
}

void DummyGraphics::clear() {
    // empty on purpose
}

const EGraphicsBackend DummyGraphics::getType() const {
    return EGraphicsBackend::kDummy;
}

const char* DummyGraphics::getName() const {
    return "Dummy";
}

const char* DummyGraphics::getVersionString() const {
    return "v1.0";
}

const int DummyGraphics::getVersionMajor() const {
    return 1;
};

const int DummyGraphics::getVersionMinor() const {
    return 0;
};

}  // namespace graphics
}  // namespace sargasso
