#include "stdafx.h"
#include "OpenGlGraphicsAdapter.h"
#include "OpenGl.h"

namespace GlEngine::Adapters
{
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const bool &val)
    {
        glUniform1i(uniformLocation, val);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const int &val)
    {
        glUniform1i(uniformLocation, val);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const unsigned &val)
    {
        glUniform1ui(uniformLocation, val);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const float &val)
    {
        glUniform1f(uniformLocation, val);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const double &val)
    {
        glUniform1d(uniformLocation, val);
        checkForGlError();
    }

    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<2, bool> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<3, bool> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<4, bool> &val)
    {
        uniformLocation; val;
        assert(false);
    }

    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<2, int> &val)
    {
        glUniform2i(uniformLocation, val[0], val[1]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<3, int> &val)
    {
        glUniform3i(uniformLocation, val[0], val[1], val[2]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<4, int> &val)
    {
        glUniform4i(uniformLocation, val[0], val[1], val[2], val[3]);
        checkForGlError();
    }

    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<2, unsigned> &val)
    {
        glUniform2ui(uniformLocation, val[0], val[1]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<3, unsigned> &val)
    {
        glUniform3ui(uniformLocation, val[0], val[1], val[2]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<4, unsigned> &val)
    {
        glUniform4ui(uniformLocation, val[0], val[1], val[2], val[3]);
        checkForGlError();
    }

    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<2> &val)
    {
        glUniform2f(uniformLocation, val[0], val[1]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<3> &val)
    {
        glUniform3f(uniformLocation, val[0], val[1], val[2]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<4> &val)
    {
        glUniform4f(uniformLocation, val[0], val[1], val[2], val[3]);
        checkForGlError();
    }

    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<2, double> &val)
    {
        glUniform2d(uniformLocation, val[0], val[1]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<3, double> &val)
    {
        glUniform3d(uniformLocation, val[0], val[1], val[2]);
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Vector<4, double> &val)
    {
        glUniform4d(uniformLocation, val[0], val[1], val[2], val[3]);
        checkForGlError();
    }

    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<2, 2> &val)
    {
        glUniformMatrix2fv(uniformLocation, 1, false, val.getAddr());
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<2, 3> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<2, 4> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<3, 2> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<3, 3> &val)
    {
        glUniformMatrix3fv(uniformLocation, 1, false, val.getAddr());
        checkForGlError();
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<3, 4> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<4, 2> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<4, 3> &val)
    {
        uniformLocation; val;
        assert(false);
    }
    void OpenGlGraphicsAdapter::SetUniform(unsigned uniformLocation, const Matrix<4, 4> &val)
    {
        glUniformMatrix4fv(uniformLocation, 1, true, val.getAddr());
        checkForGlError();
    }

    void OpenGlGraphicsAdapter::SetSubroutineUniform(const unsigned &sr_loc)
    {
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &sr_loc);
        checkForGlError();
    }
}
