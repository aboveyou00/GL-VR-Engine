#pragma once

namespace GlEngine
{
    class ENGINE_SHARED ViewPort
    {
    public:
        ViewPort();
        ~ViewPort();

        virtual void Push() = 0;
        virtual void Pop() = 0;

        virtual void SetSize(int width, int height);
        virtual void SetWidth(int width);
        virtual void SetHeight(int height);

        virtual int width();
        virtual int height();

    private:
        int _width, _height;
    };
}
