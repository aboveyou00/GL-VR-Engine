#pragma once

namespace TileRPG
{
    namespace CFB
    {
        enum Sector : uint32_t
        {
            MaxRegularSector = 0xFFFFFFFA,
            DIFATSector = 0xFFFFFFFC,
            FATSector = 0xFFFFFFFD,
            EndChainSector = 0xFFFFFFFE,
            FreeSector = 0xFFFFFFFF
        };
    }
}
