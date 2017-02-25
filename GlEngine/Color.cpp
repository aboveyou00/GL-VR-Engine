#include "stdafx.h"
#include "Color.h"
#include <cmath>

namespace GlEngine
{
    Color HsvToRgb(Color hsv)
    {
        return HsvToRgb(hsv[0], hsv[1], hsv[2]);
    }
    Color HsvToRgb(float h, float s, float v)
    {
        float chroma = v * s;
        float huePrime = h * 6;
        float fX = chroma * (1 - fabs((float)fmod(huePrime, 2) - 1));
        float fM = v - chroma;

        float r, g, b;

        if (0 <= huePrime && huePrime < 1) {
            r = chroma;
            g = fX;
            b = 0;
        }
        else if (1 <= huePrime && huePrime < 2) {
            r = fX;
            g = chroma;
            b = 0;
        }
        else if (2 <= huePrime && huePrime < 3) {
            r = 0;
            g = chroma;
            b = fX;
        }
        else if (3 <= huePrime && huePrime < 4) {
            r = 0;
            g = fX;
            b = chroma;
        }
        else if (4 <= huePrime && huePrime < 5) {
            r = fX;
            g = 0;
            b = chroma;
        }
        else if (5 <= huePrime && huePrime < 6) {
            r = chroma;
            g = 0;
            b = fX;
        }
        else {
            r = 0;
            g = 0;
            b = 0;
        }

        return Color { r + fM, g + fM, b + fM };
    }
    Color HsvToRgb(unsigned h, unsigned s, unsigned v)
    {
        return HsvToRgb(h / 255.f, s / 255.f, v / 255.f);
    }
    Color RgbToHsv(Color rgb)
    {
        return RgbToHsv(rgb[0], rgb[1], rgb[2]);
    }
    Color RgbToHsv(float r, float g, float b)
    {
        float maxc = max(max(r, g), b);
        float minc = min(min(r, g), b);
        float delta = maxc - minc;

        float h, s, v;

        if (delta > 0) {
            if (maxc == r) h = 60 * ((float)fmod(((g - b) / delta), 6));
            else if (maxc == g) h = 60 * (((b - r) / delta) + 2);
            else h = 60 * (((r - g) / delta) + 4);

            if (maxc > 0) s = delta / maxc;
            else s = 0;
        }
        else {
            h = 0;
            s = 0;
        }

        v = maxc;
        if (h < 0) h = 360 + h;

        return { h / 360.f, s, v };
    }
    Color RgbToHsv(unsigned r, unsigned g, unsigned b)
    {
        return RgbToHsv(r / 255.f, g / 255.f, b / 255.f);
    }
}
