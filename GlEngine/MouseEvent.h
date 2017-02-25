#pragma once

#include "Event.h"
#include "MouseButton.h"
#include "MouseEventType.h"
#include "Vector.h"

namespace GlEngine
{
    namespace Events
    {
        class ENGINE_SHARED MouseEvent : public Event
        {
        public:
            MouseEvent(Vector<2> mousePos, bool control, bool shift, bool alt, MouseEventType type, MouseButton btn);
            ~MouseEvent();

            MouseButton button() const;
            MouseEventType type() const;

            Vector<2> position() const;
            bool isControlPressed() const;
            bool isAltPressed() const;
            bool isShiftPressed() const;

            std::ostream &stringify(std::ostream &stream) const override;

        private:
            Vector<2> _mousePos;
            bool _ctrl, _alt, _shift;
            MouseButton _btn;
            MouseEventType _type;
        };
    }
}
