
#include "sargasso/viewport.h"

#include "sargasso/common/log.h"

#include <cstdio>
#include <exception>
#include <sml/matrix4.h>

namespace sargasso {

static const common::Log logger("Viewport");

static constexpr void dirtyWarning(const Viewport& viewport, const char* funcName) {
    if (viewport.isDirty()) {
        logger.warning(
            "@%s() Querying value of dirty viewport (%p). Run `clearDirty()` method first to avoid "
            "issues.\n",
            funcName, &viewport);
    }
}

static constexpr float DEFAULT_ANGLE = 75.f * sml::TAU / 360.f;  // 75 degrees
static constexpr float DEFAULT_Z_NEAR = -1000.f;
static constexpr float DEFAULT_Z_FAR = 1000.f;
static constexpr int DIRTY_TRUE = 0xffffffff;
static constexpr int DIRTY_FALSE = 0x00000000;
static constexpr uint DEFAULT_UNIT = 1;

Viewport::Viewport(ProjectionType projType, uint width, uint height, uint unit, float angle,
                   float minZ, float maxZ)
    : _projType(projType),
      _width(width),
      _height(height),
      _unit(unit),
      _angle(angle),
      _zNear(minZ),
      _zFar(maxZ) {
    setDirty();
    clearDirty();
}

Viewport Viewport::ortho(uint width, uint height, uint unit) {
    return Viewport(ProjectionType::kOrtho, width, height, unit, DEFAULT_ANGLE, DEFAULT_Z_NEAR,
                    DEFAULT_Z_FAR);
}

Viewport Viewport::conical(uint width, uint height, float angle, float zNear, float zFar) {
    return Viewport(ProjectionType::kConical, width, height, DEFAULT_UNIT, angle, zNear, zFar);
}

void Viewport::setWidth(const uint value) {
    _width = value;
    setDirty();
}

void Viewport::setHeight(const uint value) {
    _height = value;
    setDirty();
}

void Viewport::setUnitSize(const uint value) {
    _unit = value;
    setDirty();
}

void Viewport::setCameraAngle(const float value) {
    _angle = value;
    setDirty();
}

void Viewport::setNearZ(const float value) {
    _zNear = value;
    setDirty();
}

void Viewport::setFarZ(const float value) {
    _zFar = value;
    setDirty();
}

void Viewport::setProjectionType(ProjectionType projType) {
    _projType = projType;
    setDirty();
}

void Viewport::clearDirty() {
    if (!isDirty()) {
        return;
    }

    _dirty = DIRTY_FALSE;

    const float aspect = getAspect();
    const float height = .5f * _height / _unit;
    const float width = aspect * height;
    char errMessage[32];
    sml::Mat4 projection;

    switch (_projType) {
        case ProjectionType::kOrtho:
            projection = sml::Mat4::orthogonal_projection(-width, height, width, -height,
                                                          DEFAULT_Z_NEAR, DEFAULT_Z_FAR);
            _projection = projection;
            break;
        case ProjectionType::kConical:
            projection = sml::Mat4::conical_projection(_angle, aspect, _zNear, _zFar);
            _projection = projection;
            break;
        default:
            std::snprintf(errMessage, 32, "Invalid ProjectionType: %d", _projType);
            throw std::invalid_argument(errMessage);
    }
}

uint Viewport::getWidth() const {
    dirtyWarning(*this, __func__);
    return _width;
}

uint Viewport::getHeight() const {
    dirtyWarning(*this, __func__);
    return _height;
}

float Viewport::getAspect() const {
    dirtyWarning(*this, __func__);
    return 1.f * _width / _height;
}

float Viewport::getUnitSize() const {
    dirtyWarning(*this, __func__);
    return _unit;
}

float Viewport::getCameraAngle() const {
    dirtyWarning(*this, __func__);
    return _angle;
}

float Viewport::getNearZ() const {
    dirtyWarning(*this, __func__);
    return _zNear;
}

float Viewport::getFarZ() const {
    dirtyWarning(*this, __func__);
    return _zFar;
}

const sml::Mat4& Viewport::getProjMatrix() const {
    dirtyWarning(*this, __func__);
    return _projection;
}

constexpr bool Viewport::isDirty() const {
    return _dirty & DIRTY_TRUE;
}

void Viewport::setDirty() {
    _dirty = DIRTY_TRUE;
}

}  // namespace sargasso
