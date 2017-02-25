#pragma once

#include "Event.h"
#include "KeyboardEventType.h"

namespace GlEngine
{
    namespace Events
    {
        class ENGINE_SHARED KeyboardEvent : public Event
        {
        public:
            KeyboardEvent(unsigned int vkCode, KeyboardEventType type, bool control, bool shift, bool alt);
            ~KeyboardEvent();
            
            unsigned int GetVirtualKeyCode() const;
            KeyboardEventType type() const;
            bool IsPressed() const;
            bool IsReleased() const;
            bool IsTyped() const;

            bool isControlPressed() const;
            bool isAltPressed() const;
            bool isShiftPressed() const;

            std::ostream &stringify(std::ostream &stream) const override;

        private:
            unsigned int _vkCode;
            bool _ctrl, _alt, _shift;
            KeyboardEventType _type;
        };
    }
}
