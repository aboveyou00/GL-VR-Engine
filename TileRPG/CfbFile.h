#pragma once

#include "IComponent.h"

namespace TileRPG
{
    namespace CFB
    {
        class CfbStream;
        struct CfbHeader;

        class CfbFile
        {
        public:
            CfbFile(const char *path);
            ~CfbFile();

            bool open();
            void close();

            CfbStream *getStream(const char *key);
            CfbStream *getOrCreateStream(const char *key);
            CfbStream *createStream(const char *key);

            void removeStream(const char *key);

        private:
            std::vector<CfbStream*> myOpenStreams;
            const char *path;
            std::fstream file;
            CfbHeader *header;
            bool is_open, header_dirty;



            class SectorCache
            {
            public:
                SectorCache(CfbFile &parent);
                ~SectorCache();

                template <typename SectorT>
                SectorT *getOrCreate(unsigned idx)
                {
                    assert(false); //Not implemented
                }

            private:
                CfbFile &parent;
            };



            class __DIFAT
            {
            public:
                __DIFAT(CfbFile &parent);
                ~__DIFAT();

                uint32_t operator[](unsigned idx);

            private:
                CfbFile &parent;
            } DIFAT;



            class __FAT
            {
            public:
                __FAT(CfbFile &parent);
                ~__FAT();

                uint32_t operator[](unsigned idx);

            private:
                CfbFile &parent;
            } FAT;



            class __MiniFAT
            {
            public:
                __MiniFAT(CfbFile &parent);
                ~__MiniFAT();

                uint32_t operator[](unsigned idx);

            private:
                CfbFile &parent;
            } MiniFAT;




        };
    }
}
