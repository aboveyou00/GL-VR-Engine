#include "stdafx.h"
#include "EventQueue.h"
#include "Event.h"

namespace GlEngine
{
    namespace Events
    {
        EventQueue::EventQueue()
        {
        }
        EventQueue::~EventQueue()
        {
        }

        Event *EventQueue::PeekEvent()
        {
            if (_bottom == _top) return nullptr;
            return _queue[_bottom];
        }
        Event *EventQueue::RemoveEvent()
        {
            if (_bottom == _top) return nullptr;
            auto next = _queue[_bottom];
            _bottom++;
            if (_bottom >= MAX_EVENTS) _bottom = 0;
            return next;
        }
        bool EventQueue::PushEvent(Event *evt)
        {
            if ((_bottom == 0 && _top == MAX_EVENTS - 1) || (_bottom == _top + 1)) return false;
            _queue[_top++] = evt;
            if (_top >= MAX_EVENTS) _top = 0;
            std::cout << "Pushing event: " << *evt << std::endl;
            return true;
        }

        void EventQueue::Clear()
        {
            Event *evt;
            while ((evt = RemoveEvent()) != nullptr)
                delete evt;
        }
    }
}
