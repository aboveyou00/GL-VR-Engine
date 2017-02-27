#pragma once

#include "GameComponent.h"
#include "ICamera.h"

namespace GlEngine
{
    class ENGINE_SHARED CameraLock
    {
    public:
        static const int RELATIVE_POSITION = 2;
        static const int RELATIVE_ORIENTATION = 4;
        static const int ABSOLUTE_POSITION = 8;
        static const int ABSOLUTE_ORIENTATION = 16;
    };

    class Frame;

    class ENGINE_SHARED CameraComponent : public GameComponent, public ICamera
    {
    public:
        CameraComponent();
        ~CameraComponent();

        virtual Vector<3> clearColor() override;
        void SetClearColor(Vector<3> color);

        static GameObject *Create(Frame *frame, std::string name);

        virtual std::string name() override;
        
        virtual void Tick(float delta) override;

        virtual void Push() override;
        virtual void Pop() override;

        virtual Frame *frame() override;

    private:
        bool lockRelativePosition;
        bool lockRelativeOrientation;
        bool lockAbsolutePosition;
        bool lockAbsoluteOrientation;

        Vector<3> eye, forward, up, right;
        Matrix<4, 4> view;

        Vector<3> _clearColor;
    };
}
