#pragma once

#include "Sector.h"

namespace TileRPG
{
    namespace CFB
    {
        #pragma pack(2)
        struct CfbHeader
        {
            CfbHeader()
                : signature(0xD0CF11E0A1B11AE1Ui64),
                  CLSID { 0, 0, 0, 0 },
                  version { 0x003E, 0x0003 },
                  byte_order(0xFFFE),
                  sector_shift(0x0009),
                  mini_sector_shift(0x0006),
                  reserved { 0, 0, 0 },
                  directory_sector_count(0),
                  fat_sector_count(0),
                  first_directory_sector(Sector::EndChainSector),
                  transaction_signature_number(0),
                  mini_stream_cutoff_size(0x00001000),
                  first_mini_fat_sector(Sector::EndChainSector),
                  mini_fat_sector_count(0),
                  first_difat_sector(Sector::EndChainSector),
                  difat_sector_count(0),
                  difat { 0 }
            {
            }
            ~CfbHeader()
            {
            }

            uint64_t signature;
            uint32_t CLSID[4];
            struct
            {
                uint16_t minor;
                uint16_t major;
            } version;
            uint16_t byte_order;
            uint16_t sector_shift;
            uint16_t mini_sector_shift;
            uint16_t reserved[3];
            uint32_t directory_sector_count;
            uint32_t fat_sector_count;
            uint32_t first_directory_sector;
            uint32_t transaction_signature_number;
            uint32_t mini_stream_cutoff_size;
            uint32_t first_mini_fat_sector;
            uint32_t mini_fat_sector_count;
            uint32_t first_difat_sector;
            uint32_t difat_sector_count;
            uint32_t difat[109];
        };
    }
}
