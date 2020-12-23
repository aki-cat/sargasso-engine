#ifndef SARGASSO_ENGINE_GEOMETRY_VERTEX_H
#define SARGASSO_ENGINE_GEOMETRY_VERTEX_H

#include <sml/vector3.h>

namespace SargassoEngine {
namespace Geometry {

struct Vertex {
    SML::Vec3 position;
    SML::Vec3 rgb_color;
    float alpha;
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
