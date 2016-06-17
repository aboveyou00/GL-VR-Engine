#pragma once

namespace GlEngine
{
    namespace Events
    {
        class IEventSender
        {
        public:

        private:
            virtual void doSomething() = 0;
        };
    }
}
