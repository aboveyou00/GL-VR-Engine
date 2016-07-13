#include "stdafx.h"
#include "CfbFile.h"

#include "CfbHeader.h"

namespace TileRPG
{
    namespace CFB
    {
        CfbFile::CfbFile(const char *path)
            : path(path),
              DIFAT(*this),
              FAT(*this),
              MiniFAT(*this)
        {
        }
        CfbFile::~CfbFile()
        {
            close();
        }

        bool CfbFile::open()
        {
            if (is_open) return true;

            file.open(path, std::ios::binary | std::ios::in | std::ios::out);
            if (!file) return false;

            assert(false); //Not implemented
            return false;
        }
        void CfbFile::close()
        {
            if (!is_open) return;

            file.close();

        }
    }
}
