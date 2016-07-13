#include "stdafx.h"
#include "CfbFile.h"

namespace TileRPG
{
    namespace CFB
    {
        CfbFile::__MiniFAT::__MiniFAT(CfbFile &parent)
            : parent(parent)
        {
        }
        CfbFile::__MiniFAT::~__MiniFAT()
        {
        }

        uint32_t CfbFile::__MiniFAT::operator[](unsigned idx)
        {
            idx;
            assert(false); //Not implemented
            return 0;
        }
    }
}
