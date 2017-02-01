#pragma once

#include "CameraImpl.h"

namespace GlEngine
{
    class ENGINE_SHARED Camera
    {
    public:
        Camera();
        ~Camera();

        void Push();
        void Pop();

        Vector<3> GetEye();
        Vector<3> GetUp();
        Vector<3> GetForward();

        void SetEye(Vector<3> eye);
        void SetUp(Vector<3> up);
        void SetForward(Vector<3> forward);

        void SetGameObject(GameObject* obj);

        inline Impl::CameraImpl &GetImpl()
        {
            return *pimpl;
        }

    private:
        Impl::CameraImpl *pimpl;

    };
}
