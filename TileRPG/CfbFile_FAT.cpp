#include "stdafx.h"
#include "CfbFile.h"

#include "CfbFATSector.h"

namespace TileRPG
{
    namespace CFB
    {
        CfbFile::__FAT::__FAT(CfbFile &parent)
            : parent(parent)
        {
        }
        CfbFile::__FAT::~__FAT()
        {
        }

        uint32_t CfbFile::__FAT::operator[](unsigned idx)
        {
            //unsigned difat_idx = parent.DIFAT[idx / 128];
            //auto fat = parent.cache.getOrCreate<CfbFatSector>(difat_idx);
            //return fat[idx - (idx / 128)];

            idx;
            assert(false); //Not implemented
            return 0;
        }
    }
}
