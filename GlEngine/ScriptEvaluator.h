#pragma once

#include "Frame.h"

namespace GlEngine
{
    class ENGINE_SHARED ScriptEvaluator
    {
    public:
        ScriptEvaluator(Frame* context);
        ~ScriptEvaluator();

        Frame* context();

        virtual void Evaluate(std::string code) = 0;
        virtual std::string EvaluateSingle(std::string code);

    private:
        Frame* _context;

    };
}