#pragma once

#include "GameObject.h"
#include "PlaneGraphicsObject.h"

namespace GlEngine
{
    class ENGINE_SHARED PlaneGameObject : public GameObject
    {
    private:
        PlaneGameObject(PlaneGraphicsObject *gobj);

    public:
        template <typename... TArgs>
        PlaneGameObject(TArgs... args)
            : PlaneGameObject(new PlaneGraphicsObject(args...))
        {
        }
        ~PlaneGameObject();

        GraphicsObject *graphicsObject() const;

        virtual std::string name() override;
        
        virtual GraphicsObject *CreateGraphicsObject(GraphicsContext *ctx) override;

    private:
        GraphicsObject *_gfxObj;
    };
}
