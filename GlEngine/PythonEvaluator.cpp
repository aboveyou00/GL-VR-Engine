#include "stdafx.h"

#ifdef _DEBUG

#undef _DEBUG
#include "Python.h"
#define _DEBUG 1

#else

#include "Python.h"

#endif

#include "PythonEvaluator.h"

namespace GlEngine
{
    PythonEvaluator::PythonEvaluator(Frame* context)
        : ScriptEvaluator(context)
    {
        Py_Initialize();

        globals = PyDict_New();
        locals = PyDict_New();
    }
    PythonEvaluator::~PythonEvaluator()
    {
        Py_Finalize();
    }

    void PythonEvaluator::Evaluate(std::string code)
    {
    }

    std::string PythonEvaluator::EvaluateSingle(std::string code)
    {
        PyObject* pyCode = Py_CompileString(code.c_str(), "<REPL>", Py_eval_input);
        if (pyCode == nullptr)
            return "Error";

        PyObject* pyResult = PyEval_EvalCode(pyCode, globals, locals);
        if (pyResult == nullptr)
            return "Error";

        PyObject* pyResultString = PyObject_Str(pyResult);
        if (pyResultString == nullptr)
            return "Error";

        char* result = PyUnicode_AsUTF8(pyResultString);
        
        Py_DECREF(pyResultString);
        Py_DECREF(pyResult);
        Py_DECREF(pyCode);
        
        return std::string(result);
    }
}
