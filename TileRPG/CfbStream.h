#pragma once

namespace TileRPG
{
    namespace CFB
    {
        class CfbFile;

        class CfbStream : std::iostream
        {
        public:
            CfbStream(CfbFile *file, const char *key);
            ~CfbStream();


        };
    }
}
