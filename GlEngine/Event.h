#pragma once

#include "IEventSender.h"

namespace GlEngine
{
    namespace Events
    {
        class ENGINE_SHARED Event
        {
        public:
            Event()
                : _handled(false)
            {
            }
            ~Event()
            {
            }

            inline bool IsHandled()
            {
                return _handled;
            }
            inline void Handle()
            {
                _handled = true;
            }

            inline friend std::ostream &operator<<(std::ostream &stream, Event &evt)
            {
                return evt.stringify(stream);
            }
            virtual std::ostream &stringify(std::ostream &stream) const = 0;

        private:
            bool _handled;
        };
    }
}
