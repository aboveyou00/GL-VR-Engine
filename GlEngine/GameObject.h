#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "IGameComponent.h"

namespace GlEngine
{
    class Frame;
    class GraphicsContext;
    class GraphicsObject;
    namespace Events
    {
        class Event;
    }

	class ENGINE_SHARED GameObject: public IGameComponent
	{
	public:
        GameObject(Vector<3> position = Vector<3> { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
		~GameObject();

        inline void RequireTick(bool require = true)
        {
            _requiresTick = require;
        }
        inline bool RequiresTick()
        {
            return _requiresTick;
        }
        inline void RequireGraphicsTick(bool require = true)
        {
            _requiresGraphicsTick = require;
        }
        inline bool RequiresGraphicsTick()
        {
            return _requiresGraphicsTick;
        }

        bool Initialize() override;
        void Shutdown() override;
        void Tick(float delta) override;

        virtual void AddToFrame(Frame *frame);
        virtual void RemoveFromFrame(Frame *frame);

        virtual void HandleEvent(Events::Event &evt);

        virtual GraphicsObject *CreateGraphicsObject(GraphicsContext &ctx) = 0;
        virtual void UpdateGraphicsObject(GraphicsContext &ctx, GraphicsObject *object);

		Vector<3> position;
		Matrix<4, 4> orientation;

    private:
        bool _requiresTick, _requiresGraphicsTick;
        Frame *_frame;
	};
}
