#include "stdafx.h"
#include "CfbFile.h"

namespace TileRPG
{
    namespace CFB
    {
        CfbFile::SectorCache::SectorCache(CfbFile &parent)
            : parent(parent)
        {
        }
        CfbFile::SectorCache::~SectorCache()
        {
        }
    }
}
