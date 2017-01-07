#include "stdafx.h"
#include "Event.h"

namespace GlEngine
{
    namespace Events
    {
        Event::Event()
            : _handled(false)
        {
        }
        Event::~Event()
        {
        }

        bool Event::IsHandled() const
        {
            return _handled;
        }
        void Event::Handle()
        {
            _handled = true;
        }

        std::ostream &operator<<(std::ostream &stream, Event &evt)
        {
            return evt.stringify(stream);
        }
    }
}
