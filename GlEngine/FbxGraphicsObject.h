#pragma once

#include "VboGraphicsObject.h"
#include <unordered_map>

namespace GlEngine
{
    class ENGINE_SHARED FbxGraphicsObject : public VboGraphicsObject
    {
    private:
        FbxGraphicsObject(const char *const filename);
        ~FbxGraphicsObject();

    public:
        static FbxGraphicsObject *Create(const char* name);
        
        virtual bool InitializeAsync() override;

        virtual std::string name() override;

    private:
        const char *filename;
        bool initialized;
    };
}
