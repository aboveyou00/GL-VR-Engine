#pragma once

namespace GlEngine
{
    namespace Events
    {
        class ENGINE_SHARED IEventSender
        {
        public:

        private:
            virtual void doSomething() = 0;
        };
    }
}
