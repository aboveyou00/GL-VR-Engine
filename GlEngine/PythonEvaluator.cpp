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
    typedef struct {
        PyObject_HEAD
        IWritable* writable;
    } outputWrapper;

    PyObject* outputWrapper_Write(PyObject* self, PyObject* args)
    {
        args;
        auto wrapper = (outputWrapper*)self;
        wrapper;
        //PyObject* pyString = PyArg_ParseTuple(args, "S");
        //wrapper->writable->Write();
        return Py_None;
    }

    static PyMethodDef outputWrapperWriteMethods[] = {
        {"write", (PyCFunction)outputWrapper_Write, METH_VARARGS}
    };

    static PyTypeObject outputWrapperType = {
        PyVarObject_HEAD_INIT(NULL, 0)
        "OutputWrapper",           /* tp_name */
        sizeof(outputWrapper),     /* tp_basicsize */
        0,                         /* tp_itemsize */
        0,                         /* tp_dealloc */
        0,                         /* tp_print */
        0,                         /* tp_getattr */
        0,                         /* tp_setattr */
        0,                         /* tp_reserved */
        0,                         /* tp_repr */
        0,                         /* tp_as_number */
        0,                         /* tp_as_sequence */
        0,                         /* tp_as_mapping */
        0,                         /* tp_hash  */
        0,                         /* tp_call */
        0,                         /* tp_str */
        0,                         /* tp_getattro */
        0,                         /* tp_setattro */
        0,                         /* tp_as_buffer */
        Py_TPFLAGS_DEFAULT,        /* tp_flags */
        "Wrapper for output",      /* tp_doc */
        0,                         /* tp_traverse */
        0,                         /* tp_clear */
        0,                         /* tp_richcompare */
        0,                         /* tp_weaklistoffset */
        0,                         /* tp_iter */
        0,                         /* tp_iternext */
        0,                         /* tp_methods */
    };

    PythonEvaluator::PythonEvaluator(Frame* context)
        : ScriptEvaluator(context)
    {
        Py_Initialize();

        globals = PyDict_New();
        locals = PyDict_New();

        CreateOutputWrapper();
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

    void PythonEvaluator::SetOut(IWritable* writable)
    {
        this->writable = writable;
        auto wrapper = (outputWrapper*)pyWritable;
        wrapper->writable = writable;
    }

    void PythonEvaluator::CreateOutputWrapper()
    {
        outputWrapperType.tp_new = PyType_GenericNew;
        pyWritable = (PyObject*)PyObject_New(outputWrapper, &outputWrapperType);
    }
}
