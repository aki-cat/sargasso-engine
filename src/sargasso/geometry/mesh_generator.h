#ifndef SARGASSO_ENGINE_MESH_GENERATOR_H
#define SARGASSO_ENGINE_MESH_GENERATOR_H

#include "sargasso/geometry/mesh_raw.h"

#include <sml/matrix4.h>

namespace SargassoEngine {
namespace Geometry {

using namespace sml;

class MeshGenerator {
   public:
    MeshGenerator() = delete;
    ~MeshGenerator() = delete;
    static MeshRaw generate_square();
    static Mat4 generate_sample_camera(const float width, const float height);
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
