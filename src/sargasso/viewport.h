#ifndef SARGASSO_VIEWPORT_H_
#define SARGASSO_VIEWPORT_H_

#include "sargasso/common/typedefs.h"

#include <cstdint>
#include <cstdio>
#include <sml/constants.h>
#include <sml/matrix4.h>

namespace sargasso {

inline float VIEW_X = 0, VIEW_Y = 0, VIEW_Z = 10.f;

class Viewport {
   public:
    enum ProjectionType { kOrtho, kConical };
    Viewport(ProjectionType projType, uint width, uint height, uint unit, float angle, float zNear,
             float zFar);

    static Viewport ortho(uint width, uint height, uint unit);
    static Viewport conical(uint width, uint height, float angle, float zNear, float zFar);

    void setWidth(const uint value);
    void setHeight(const uint value);
    void setUnitSize(const uint value);
    void setCameraAngle(const float value);
    void setNearZ(const float value);
    void setFarZ(const float value);
    void setProjectionType(ProjectionType value);
    void clearDirty();

    uint getWidth() const;
    uint getHeight() const;
    float getAspect() const;
    float getUnitSize() const;
    float getCameraAngle() const;
    float getNearZ() const;
    float getFarZ() const;
    const sml::Mat4& getProjMatrix() const;
    constexpr bool isDirty() const;

   private:
    // 16*4 + 8*4 = 24*4 = 96 bytes
    ProjectionType _projType;
    int _dirty;
    uint _width;
    uint _height;
    uint _unit;
    float _angle;
    float _zNear;
    float _zFar;
    sml::Mat4 _projection{};

    void setDirty();
};

}  // namespace sargasso

#endif  // SARGASSO_VIEWPORT_H_
