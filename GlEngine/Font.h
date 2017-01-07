#pragma once

namespace GlEngine
{
    class Font
    {
    public:
        Font(const char * const filename, int size);
        ~Font();

        void Use();
        float StringWidth(const char * const str);
        float StringHeight(const char * const str);
        void Render(const char * const str);

    private:
        int size;
    };
}
