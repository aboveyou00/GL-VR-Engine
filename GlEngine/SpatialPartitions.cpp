#include "stdafx.h"
#include "SpatialPartitions.h"

namespace GlEngine
{
    SpatialPartitions::SpatialPartitions()
    {
    }

    SpatialPartitions::~SpatialPartitions()
    {
    }

    void SpatialPartitions::AddStaticMesh(MeshComponent * mesh)
    {
        AddMesh(mesh);
    }

    void SpatialPartitions::RemoveStaticMesh(MeshComponent * mesh)
    {
        RemoveMesh(mesh);
    }

#ifdef _DEBUG
    std::string SpatialPartitions::debugString(Vector<3>)
    {
        return "[No debug info provided from SpatialPartitions class]";
    }
#else
    std::string SpatialPartitions::debugString(Vector<3>)
    {
        return "[Spatial partitioning debug information disabled in release build]";
    }
#endif // _DEBUG
}
