#ifndef SARGASSO_ENGINE_MESH_GENERATOR_H
#define SARGASSO_ENGINE_MESH_GENERATOR_H

#include "common/math.h"
#include "geometry/mesh_raw.h"

namespace SargassoEngine {
namespace Geometry {

using namespace Common::Math;

class MeshGenerator {
   public:
    MeshGenerator() = delete;
    ~MeshGenerator() = delete;
    static const MeshRaw generate_square();
    static const Matrix4 generate_sample_camera();
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
