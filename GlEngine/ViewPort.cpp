#include "stdafx.h"
#include "ViewPort.h"
#include "MatrixStack.h"

namespace GlEngine
{
    ViewPort::ViewPort()
    {
    }
    ViewPort::~ViewPort()
    {
    }

    void ViewPort::SetSize(int width, int height)
    {
        SetWidth(width);
        SetHeight(height);
    }
    void ViewPort::SetWidth(int width)
    {
        this->width = width;
    }
    void ViewPort::SetHeight(int height)
    {
        this->height = height;
    }

    int ViewPort::GetWidth()
    {
        return width;
    }

    int ViewPort::GetHeight()
    {
        return height;
    }
}