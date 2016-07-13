#include "stdafx.h"
#include "CfbFile.h"

#include "CfbHeader.h"
#include "CfbDIFATSector.h"

namespace TileRPG
{
    namespace CFB
    {
        CfbFile::__DIFAT::__DIFAT(CfbFile &parent)
            : parent(parent)
        {
        }
        CfbFile::__DIFAT::~__DIFAT()
        {
        }

        uint32_t CfbFile::__DIFAT::operator[](unsigned idx)
        {
            //if (idx < 108) return parent.header->difat[idx];
            //idx -= 109;
            //CfbDIFATSector *difat = &parent.cache.getOrCreate<CfbDIFATSector>(parent.header->first_difat_sector);
            //while (idx >= 127)
            //{
            //    difat = &parent.cache.getOrCreate<CfbDIFATSector>(difat->next_difat);
            //    idx -= 127;
            //}
            //return difat->difat[idx];

            idx;
            assert(false); //Not implemented
            return 0;
        }
    }
}
