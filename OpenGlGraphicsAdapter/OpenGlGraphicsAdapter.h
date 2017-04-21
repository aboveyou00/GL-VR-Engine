#pragma once

#include "../GlEngine/GraphicsAdapter.h"
#include <stack>
#include <unordered_map>

namespace GlEngine::Adapters
{
    typedef std::unordered_map<GraphicsCap, bool> CapMap;
    typedef std::stack<CapMap> CapStack;

    class ADAPTER_SHARED OpenGlGraphicsAdapter : public GraphicsAdapter
    {
    private:
        OpenGlGraphicsAdapter();
        ~OpenGlGraphicsAdapter();

        static OpenGlGraphicsAdapter *_inst;

    public:
        static OpenGlGraphicsAdapter *Instance();

    public:
        //MakeDefaultContext.cpp
        virtual bool MakeDefaultContext(HDC hdc) override;

        //Uniforms.cpp
        virtual void SetUniform(unsigned uniformLocation, const bool &val) override;
        virtual void SetUniform(unsigned uniformLocation, const int &val) override;
        virtual void SetUniform(unsigned uniformLocation, const unsigned &val) override;
        virtual void SetUniform(unsigned uniformLocation, const float &val) override;
        virtual void SetUniform(unsigned uniformLocation, const double &val) override;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, bool> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, bool> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, bool> &val) override;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, int> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, int> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, int> &val) override;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, unsigned> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, unsigned> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, unsigned> &val) override;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4> &val) override;

        virtual void SetUniform(unsigned uniformLocation, const Vector<2, double> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<3, double> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Vector<4, double> &val) override;

        virtual void SetUniform(unsigned uniformLocation, const Matrix<2, 2> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<2, 3> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<2, 4> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<3, 2> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<3, 3> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<3, 4> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<4, 2> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<4, 3> &val) override;
        virtual void SetUniform(unsigned uniformLocation, const Matrix<4, 4> &val) override;

        virtual void SetSubroutineUniform(const unsigned &sr_loc) override;

        //Capabilities.cpp
        virtual void ForkCapabilities() override;
        virtual void PopCapabilities() override;
        virtual void SetCapability(GraphicsCap cap, bool enabled) override;
        virtual bool GetCapability(GraphicsCap cap) override;

    private:
        CapStack *capabilityStack;
    };
}
