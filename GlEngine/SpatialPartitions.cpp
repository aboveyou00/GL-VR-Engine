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

#ifdef _DEBUG
    std::string SpatialPartitions::debugString(Vector<3>)
    {
        return "[No debug info provided from SpatialPartitions class]";
    }
#endif // _DEBUG
}
