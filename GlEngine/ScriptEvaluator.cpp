#include "stdafx.h"
#include "ScriptEvaluator.h"

namespace GlEngine
{
    ScriptEvaluator::ScriptEvaluator(Frame* context)
        : _context(context)
    {
    }
    ScriptEvaluator::~ScriptEvaluator()
    {
    }

    Frame * ScriptEvaluator::context()
    {
        return _context;
    }

    void ScriptEvaluator::Evaluate(std::string code)
    {
    }
    std::string ScriptEvaluator::EvaluateSingle(std::string code)
    {
        Evaluate(code);
        return ""s;
    }
}
