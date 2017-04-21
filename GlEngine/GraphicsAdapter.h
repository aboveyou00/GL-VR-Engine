#pragma once

namespace GlEngine
{
    enum class GraphicsCap : unsigned
    {
        DepthTest = 0,
        CullFace = 1,
        Blend = 2
    };

    class ENGINE_SHARED GraphicsAdapter
    {
    public:
        GraphicsAdapter();
        ~GraphicsAdapter();

        virtual bool MakeDefaultContext(HDC hdc) = 0;

        virtual void SetUniform(unsigned uniformLocation, const bool &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const int &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const unsigned &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const float &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const double &val) = 0;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, bool> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, bool> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, bool> &val) = 0;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, int> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, int> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, int> &val) = 0;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, unsigned> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, unsigned> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, unsigned> &val) = 0;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4> &val) = 0;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, double> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, double> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, double> &val) = 0;

        virtual void SetUniform(unsigned uniformLocation, const Matrix<2, 2> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<2, 3> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<2, 4> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<3, 2> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<3, 3> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<3, 4> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<4, 2> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<4, 3> &val) = 0;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<4, 4> &val) = 0;

        virtual void SetSubroutineUniform(const unsigned &sr_loc) = 0;

        virtual void ForkCapabilities() = 0;
        virtual void PopCapabilities() = 0;
        virtual void SetCapability(GraphicsCap cap, bool enabled) = 0;
        virtual bool GetCapability(GraphicsCap cap) = 0;
    };
}
