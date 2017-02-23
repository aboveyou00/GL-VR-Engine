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
        this->_width = width;
    }
    void ViewPort::SetHeight(int height)
    {
        this->_height = height;
    }

    int ViewPort::width()
    {
        return _width;
    }
    int ViewPort::height()
    {
        return _height;
    }
}
