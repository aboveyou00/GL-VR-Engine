#pragma once

namespace GlEngine
{
    namespace Events
    {
        class Event
        {
        public:
            Event(void *sender = nullptr)
                : _sender(sender)
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

            inline void *GetSender()
            {
                return _sender;
            }
            template <typename T>
            inline T *GetSender()
            {
                return dynamic_cast<T*>(_sender);
            }

            inline friend std::ostream &operator<<(std::ostream &stream, Event &evt)
            {
                return evt.stringify(stream);
            }
            virtual std::ostream &stringify(std::ostream &stream) const = 0;

        private:
            bool _handled;
            void *_sender;
        };
    }
}
