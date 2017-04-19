#pragma once

#include "Event.h"

namespace GlEngine::Events
{
    class ENGINE_SHARED CharEvent: public Event
    {
    public:
        CharEvent(char chr, unsigned repeat, unsigned scanCode, bool isExtended);
        ~CharEvent();

        char chr() const;
        unsigned repeat() const;
        unsigned scanCode() const;
        bool isExtended() const;

        virtual std::ostream &stringify(std::ostream &stream) const override;

    private:
        char _chr;
        unsigned _repeat, _scanCode;
        bool _isExtended;
    };
}
