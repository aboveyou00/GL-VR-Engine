#include "stdafx.h"
#include "MouseEvent.h"

namespace GlEngine
{
    namespace Events
    {
        MouseEvent::MouseEvent(Vector<2> mousePos, bool control, bool shift, bool alt, MouseEventType type, MouseButton btn)
            : _mousePos(mousePos), _ctrl(control), _shift(shift), _alt(alt), _type(type), _btn(btn)
        {
        }
        MouseEvent::~MouseEvent()
        {
        }

        MouseButton MouseEvent::GetButton() const
        {
            return _btn;
        }
        MouseEventType MouseEvent::GetEventType() const
        {
            return _type;
        }

        Vector<2> MouseEvent::GetMousePosition() const
        {
            return _mousePos;
        }
        bool MouseEvent::IsControlPressed() const
        {
            return _ctrl;
        }
        bool MouseEvent::IsAltPressed() const
        {
            return _alt;
        }
        bool MouseEvent::IsShiftPressed() const
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
