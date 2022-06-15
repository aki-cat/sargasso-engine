#ifndef SARGASSO_GRAPHICS_DUMMY_H_
#define SARGASSO_GRAPHICS_DUMMY_H_

#include "sargasso/graphics/graphics.h"

namespace sargasso {
namespace graphics {

class DummyGraphics : virtual public IGraphicsManager {
   public:
    DummyGraphics() : IGraphicsManager() {}

    bool initialize(void* proc_address) override;
    void setViewport(int x, int y, uint32_t width, uint32_t height) override;
    void setClearColor(Color color) override;
    void clear() override;

    const char* getName() const override;
    const char* getVersionString() const override;
    const int getVersionMajor() const override;
    const int getVersionMinor() const override;

   private:
    static const char* NAME;
    static const char* VERSION;
};

}  // namespace graphics
}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_DUMMY_H_
