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

            MouseButton GetButton() const;
            MouseEventType GetEventType() const;

            Vector<2> GetMousePosition() const;
            bool IsControlPressed() const;
            bool IsAltPressed() const;
            bool IsShiftPressed() const;

            std::ostream &stringify(std::ostream &stream) const override;

        private:
            Vector<2> _mousePos;
            bool _ctrl, _alt, _shift;
            MouseButton _btn;
            MouseEventType _type;
        };
    }
}
