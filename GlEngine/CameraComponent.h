#pragma once

#include "GameComponent.h"

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

    class ENGINE_SHARED CameraComponent : public GameComponent
    {
    public:
        CameraComponent();
        ~CameraComponent();



        //From CameraGameObject.cpp:
        static GameObject *Create(Frame *frame, std::string name);

        void SetTargetObject(GameObject* gameObject);

        virtual std::string name() override;
        
        virtual void Tick(float delta) override;

        virtual void SetLock(int lockFlags);
        virtual void Lock(int lockFlags);

        virtual void FindOrientation();

        GameObject *target;

        Vector<3> relativePosition;
        Matrix<4, 4> relativeOrientation;



        //From Camera.cpp:
        void Push();
        void Pop();



    private:
        bool lockRelativePosition;
        bool lockRelativeOrientation;
        bool lockAbsolutePosition;
        bool lockAbsoluteOrientation;

        Vector<3> eye, forward, up;
        Matrix<4, 4> view;
    };
}