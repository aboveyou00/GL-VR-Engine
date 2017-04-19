#pragma once

namespace GlEngine
{
    class IWritable
    {
    public:
        virtual bool Write(std::string string) = 0;
    };
}
