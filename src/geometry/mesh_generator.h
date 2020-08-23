#ifndef SARGASSO_ENGINE_MESH_GENERATOR_H
#define SARGASSO_ENGINE_MESH_GENERATOR_H

#include "geometry/mesh_raw.h"

namespace SargassoEngine {
namespace Geometry {

class MeshGenerator {
   public:
    MeshGenerator() = delete;
    ~MeshGenerator() = delete;
    static const MeshRaw& generate_square();
};

}  // namespace Geometry
}  // namespace SargassoEngine

#endif
