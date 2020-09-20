#ifndef SARGASSO_ENGINE_MESH_GENERATOR_H
#define SARGASSO_ENGINE_MESH_GENERATOR_H

#include "common/math/matrix4.h"
#include "geometry/mesh_raw.h"

namespace SargassoEngine {
namespace Geometry {

using namespace Common::Math;

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
