#pragma once

#include "Sector.h"

namespace TileRPG
{
    namespace CFB
    {
#pragma pack(4)
        struct CfbDIFATSector
        {
            CfbDIFATSector()
                : difat { Sector::FreeSector },
                  next_difat(Sector::EndChainSector)
            {
            }
            ~CfbDIFATSector()
            {
            }

            uint32_t difat[127];
            uint32_t next_difat;
        };
    }
}
