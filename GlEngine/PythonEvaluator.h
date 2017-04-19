#pragma once
#include "ScriptEvaluator.h"

#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif

namespace GlEngine
{
    class ENGINE_SHARED PythonEvaluator : public ScriptEvaluator
    {
    public:
        PythonEvaluator(Frame* context);
        ~PythonEvaluator();

        virtual void Evaluate(std::string code) override;
        virtual std::string EvaluateSingle(std::string code) override;

    private:
        std::vector<PyObject*> results;
        PyObject* globals;
        PyObject* locals;
    };
}
