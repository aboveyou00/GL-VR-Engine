#pragma once

namespace GlEngine
{
    namespace Events
    {
        class Event;

        class EventQueue
        {
        public:
            EventQueue();
            ~EventQueue();

            Event *PeekEvent();
            Event *RemoveEvent();
            bool PushEvent(Event *evt);

            void Clear();

        private:
            static const int MAX_EVENTS = 256;
            Event *_queue[MAX_EVENTS];
            int _bottom, _top;
        };
    }
}
