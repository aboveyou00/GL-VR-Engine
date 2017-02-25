#pragma once

namespace GlEngine
{
    typedef Vector<3> Color;

    Color ENGINE_SHARED HsvToRgb(Color hsv);
    Color ENGINE_SHARED HsvToRgb(float h, float s, float v);
    Color ENGINE_SHARED HsvToRgb(unsigned h, unsigned s, unsigned v);
    Color ENGINE_SHARED RgbToHsv(Color rgb);
    Color ENGINE_SHARED RgbToHsv(float r, float g, float b);
    Color ENGINE_SHARED RgbToHsv(unsigned r, unsigned g, unsigned b);
}
