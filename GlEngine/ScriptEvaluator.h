#pragma once

#include "Frame.h"
#include "IWritable.h"

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

        virtual void SetOut(IWritable* writable) = 0;
            
    private:
        Frame* _context;

    };
}