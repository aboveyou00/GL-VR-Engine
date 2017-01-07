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
            KeyboardEvent(unsigned int vkCode, KeyboardEventType type);
            ~KeyboardEvent();
            
            inline unsigned int GetVirtualKeyCode()
            {
                return _vkCode;
            }
            inline KeyboardEventType GetEventType()
            {
                return _type;
            }
            inline bool IsPressed()
            {
                return _type == KeyboardEventType::KeyPressed;
            }
            inline bool IsReleased()
            {
                return _type == KeyboardEventType::KeyReleased;
            }
            inline bool IsTyped()
            {
                return _type == KeyboardEventType::KeyTyped;
            }

            std::ostream &stringify(std::ostream &stream) const override;

        private:
            unsigned int _vkCode;
            KeyboardEventType _type;
        };
    }
}
