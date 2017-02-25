#include "stdafx.h"
#include "KeyboardEvent.h"

namespace GlEngine
{
    namespace Events
    {
        KeyboardEvent::KeyboardEvent(unsigned int vkCode, KeyboardEventType type, bool control, bool shift, bool alt)
            : _vkCode(vkCode), _type(type), _ctrl(control), _shift(shift), _alt(alt)
        {
        }
        KeyboardEvent::~KeyboardEvent()
        {
        }

        unsigned int KeyboardEvent::GetVirtualKeyCode() const
        {
            return _vkCode;
        }
        KeyboardEventType KeyboardEvent::type() const
        {
            return _type;
        }
        bool KeyboardEvent::IsPressed() const
        {
            return _type == KeyboardEventType::KeyPressed;
        }
        bool KeyboardEvent::IsReleased() const
        {
            return _type == KeyboardEventType::KeyReleased;
        }
        bool KeyboardEvent::IsTyped() const
        {
            return _type == KeyboardEventType::KeyTyped;
        }

        bool KeyboardEvent::isControlPressed() const
        {
            return _ctrl;
        }
        bool KeyboardEvent::isAltPressed() const
        {
            return _alt;
        }
        bool KeyboardEvent::isShiftPressed() const
        {
            return _shift;
        }

        std::ostream &KeyboardEvent::stringify(std::ostream &stream) const
        {
            stream << _type << ": " << _vkCode;
            if (_ctrl) stream << " +ctrl";
            if (_alt) stream << " +alt";
            if (_shift) stream << " +shift";
            return stream;
        }
    }
}
