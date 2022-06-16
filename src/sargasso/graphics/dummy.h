#ifndef SARGASSO_GRAPHICS_DUMMY_H_
#define SARGASSO_GRAPHICS_DUMMY_H_

#include "sargasso/graphics/graphics.h"

namespace sargasso {
namespace graphics {

class DummyGraphics : virtual public IGraphicsManager {
   public:
    DummyGraphics() : IGraphicsManager() {}
    DummyGraphics(const DummyGraphics&) = delete;
    DummyGraphics(const DummyGraphics&&) = delete;

    bool initialize(void* proc_address) override;
    void setViewport(int x, int y, uint32_t width, uint32_t height) override;
    void setClearColor(Color color) override;
    void clear() override;

    const char* getName() const override;
    const char* getVersionString() const override;
    int getVersionMajor() const override;
    int getVersionMinor() const override;
};

}  // namespace graphics
}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_DUMMY_H_
