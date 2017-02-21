#pragma once

#include "VboGraphicsObject.h"
#include <unordered_map>

namespace GlEngine
{
    class ENGINE_SHARED FbxGraphicsObject : public VboGraphicsObject
    {
    private:
        FbxGraphicsObject(std::string name, const char *const filename);
        ~FbxGraphicsObject();

    public:
        static FbxGraphicsObject *Create(std::string name, const char *filename);
        
        virtual bool InitializeAsync() override;

    private:
        const char *filename;
        bool initialized;
    };
}
