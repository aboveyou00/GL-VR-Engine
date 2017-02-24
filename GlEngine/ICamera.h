#pragma once

namespace GlEngine
{
    class Frame;

    class ENGINE_SHARED ICamera
    {
    public:
        virtual void Push() = 0;
        virtual void Pop() = 0;

        virtual Frame *frame() = 0;

        virtual Vector<3> clearColor();

        virtual bool isReady();
    };
}
