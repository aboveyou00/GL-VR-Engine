#pragma once

#include "Sector.h"

namespace TileRPG
{
    namespace CFB
    {
        #pragma pack(4)
        struct CfbFATSector
        {
            CfbFATSector()
                : fat { Sector::FreeSector }
            {
            }
            ~CfbFATSector()
            {
            }

            uint32_t fat[128];
        };
    }
}
