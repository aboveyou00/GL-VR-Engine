#pragma once

#include "GameObject.h"
#include "CubeGraphicsObject.h"

namespace GlEngine
{
    class ENGINE_SHARED CubeGameObject : public GameObject
    {
    private:
        CubeGameObject(CubeGraphicsObject *gobj);

    public:
        template <typename... TArgs>
        CubeGameObject(TArgs... args)
            : CubeGameObject(new CubeGraphicsObject(args...))
        {
        }
        ~CubeGameObject();

        Vector<3> rotationSpeed();
        void SetRotationSpeed(Vector<3> rot);

        GraphicsObject *graphicsObject() const;

        virtual void Tick(float delta) override;

        virtual const char *name() override;
        
        virtual GraphicsObject *CreateGraphicsObject(GraphicsContext & ctx) override;

    private:
        Vector<3> _rotationSpeed;
        GraphicsObject *_gfxObj;
    };
}
