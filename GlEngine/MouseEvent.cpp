#include "stdafx.h"
#include "MouseEvent.h"

namespace GlEngine
{
    namespace Events
    {
        MouseEvent::MouseEvent(Vector<2> mousePos, bool control, bool shift, bool alt, MouseEventType type, MouseButton btn, void *sender)
            : Event(sender), _mousePos(mousePos), _ctrl(control), _shift(shift), _alt(alt), _type(type), _btn(btn)
        {
        }
        MouseEvent::~MouseEvent()
        {
        }

        std::ostream &MouseEvent::stringify(std::ostream &stream) const
        {
            stream << "TODO(Impl MouseEvent::stringify)";
            return stream;
        }
    }
}
