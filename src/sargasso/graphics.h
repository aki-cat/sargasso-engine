#ifndef SARGASSO_COMMON_GRAPHICS_H_
#define SARGASSO_COMMON_GRAPHICS_H_

#include "sargasso/common/reference.h"
#include "sargasso/geometry/mesh.h"
#include "sargasso/geometry/rect.h"

namespace sargasso {

class Graphics {
   public:
    explicit Graphics();

    Graphics(Graphics&&) = delete;
    Graphics(const Graphics&&) = delete;
    Graphics&& operator=(Graphics&&) = delete;
    Graphics&& operator=(const Graphics&&) = delete;

    // methods

    common::Reference<geometry::Rect> newRect(float w, float h) const;
};

inline Graphics::Graphics() {}

inline common::Reference<geometry::Rect> Graphics::newRect(float w, float h) const {
    common::Reference<geometry::Rect> rect = new geometry::Rect(w, h);
    return rect;
}

}  // namespace sargasso

#endif  // SARGASSO_COMMON_GRAPHICS_H_
