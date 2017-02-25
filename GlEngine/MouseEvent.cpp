#include "stdafx.h"
#include "MouseEvent.h"
#include "Environment.h"

namespace GlEngine
{
    namespace Events
    {
        MouseEvent::MouseEvent(Vector<2> mousePos, bool control, bool shift, bool alt, MouseEventType type, MouseButton btn)
            : _mousePos(mousePos), _ctrl(control), _shift(shift), _alt(alt), _type(type), _btn(btn)
        {
            ShaderFactory::Environment::GetInstance().SetMouseScreenPosition(mousePos);
        }
        MouseEvent::~MouseEvent()
        {
        }

        MouseButton MouseEvent::button() const
        {
            return _btn;
        }
        MouseEventType MouseEvent::type() const
        {
            return _type;
        }

        Vector<2> MouseEvent::position() const
        {
            return _mousePos;
        }
        bool MouseEvent::isControlPressed() const
        {
            return _ctrl;
        }
        bool MouseEvent::isAltPressed() const
        {
            return _alt;
        }
        bool MouseEvent::isShiftPressed() const
        {
            return _shift;
        }

        std::ostream &MouseEvent::stringify(std::ostream &stream) const
        {
            stream << _type << ": " << _btn << " " << _mousePos;
            if (_ctrl) stream << " +ctrl";
            if (_alt) stream << " +alt";
            if (_shift) stream << " +shift";
            return stream;
        }
    }
}
