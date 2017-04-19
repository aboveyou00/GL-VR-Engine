#include "stdafx.h"
#include "CharEvent.h"

namespace GlEngine::Events
{
    CharEvent::CharEvent(char chr, unsigned repeat, unsigned scanCode, bool isExtended)
        : _chr(chr), _repeat(repeat), _scanCode(scanCode), _isExtended(isExtended)
    {
    }
    CharEvent::~CharEvent()
    {
    }

    char CharEvent::chr() const
    {
        return _chr;
    }
    unsigned CharEvent::repeat() const
    {
        return _repeat;
    }
    unsigned CharEvent::scanCode() const
    {
        return _scanCode;
    }
    bool CharEvent::isExtended() const
    {
        return _isExtended;
    }

    std::ostream &CharEvent::stringify(std::ostream &stream) const
    {
        return stream << "Character typed: " << _chr << std::endl;
    }
}
