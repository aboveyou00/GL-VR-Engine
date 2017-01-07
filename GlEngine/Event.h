#pragma once

namespace GlEngine
{
    namespace Events
    {
        class ENGINE_SHARED Event
        {
        public:
            Event();
            ~Event();

            bool IsHandled() const;
            void Handle();

            virtual std::ostream &stringify(std::ostream &stream) const = 0;

        private:
            bool _handled;
        };

        ENGINE_SHARED std::ostream &operator<<(std::ostream &stream, Event &evt);
    }
}
