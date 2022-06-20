#ifndef SARGASSO_GRAPHICS_MESH_MANAGER_H_
#define SARGASSO_GRAPHICS_MESH_MANAGER_H_

#include "sargasso/geometry/mesh.h"

#include <cstdint>
#include <vector>

namespace sargasso {
namespace graphcis {

typedef uint32_t MeshId;
typedef uint32_t GlBufferId;

class GlMeshManager {
   public:
    explicit GlMeshManager();
    ~GlMeshManager();

    // Deleted constructors
    GlMeshManager(GlMeshManager&&) = delete;
    GlMeshManager(const GlMeshManager&) = delete;
    GlMeshManager& operator=(GlMeshManager&&) = delete;
    GlMeshManager& operator=(const GlMeshManager&) = delete;

    // Methdods
    MeshId addMesh(const geometry::Mesh& meshData);
    void draw();

   private:
    struct GlMeshBuffer {
        size_t triCount;
        GlBufferId vaoId;
        GlBufferId vertexBufferId;
        GlBufferId indexBufferId;
    };
    GlMeshBuffer _meshes[1024];
    MeshId _meshCount = 0;
};

}  // namespace graphcis
}  // namespace sargasso

#endif  // SARGASSO_GRAPHICS_MESH_MANAGER_H_
