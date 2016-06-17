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
            MouseEvent(Vector<2> mousePos, bool control, bool shift, bool alt, MouseEventType type, MouseButton btn, IEventSender *sender = nullptr);
            ~MouseEvent();

            inline MouseButton GetButton() const
            {
                return _btn;
            }
            inline MouseEventType GetEventType() const
            {
                return _type;
            }

            inline Vector<2> GetMousePosition() const
            {
                return _mousePos;
            }
            inline bool IsControlPressed() const
            {
                return _ctrl;
            }
            inline bool IsAltPressed() const
            {
                return _alt;
            }
            inline bool IsShiftPressed() const
            {
                return _shift;
            }

            std::ostream &stringify(std::ostream &stream) const override;

        private:
            Vector<2> _mousePos;
            bool _ctrl, _alt, _shift;
            MouseButton _btn;
            MouseEventType _type;
        };
    }
}
