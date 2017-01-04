#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
    class ENGINE_SHARED ObjGraphicsObject : public VboGraphicsObject<>
    {
    public:
        ObjGraphicsObject() : VboGraphicsObject() {}
        ObjGraphicsObject(const char *const filename);
        ObjGraphicsObject(const char *const filename, VaObject vao);
        ObjGraphicsObject(const char *const filename, VaObject vao, Material *mat);

        static ObjGraphicsObject *Create(const char *name, Material *mat);

        bool Initialize() override;

        const char *name() override;

    private:
        const char * filename;
    };
}
