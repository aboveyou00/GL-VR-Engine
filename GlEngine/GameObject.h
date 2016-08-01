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

	enum class GameObjectType
	{
		Object3d,
		Object2d,
		Camera,
	};

	class ENGINE_SHARED GameObject: public IGameComponent
	{
	public:
        GameObject(GameObjectType type, Vector<3> position = Vector<3> { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
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

		virtual void SetPosition(Vector<3> pos);
		virtual void SetOrientation(Matrix<4, 4> orientation);
		virtual void ApplyOrientation(Matrix<4, 4> relative);
		
		virtual void Rotate(float radians, Vector<3> axis);
		
		virtual void RotateX(float radians);
		virtual void RotateY(float radians);
		virtual void RotateZ(float radians);

		void RotateDegrees(float degrees, Vector<3> axis);
		void RotateDegreesX(float degrees);
		void RotateDegreesY(float degrees);
		void RotateDegreesZ(float degrees);

		GameObjectType type;

    private:
        bool _requiresTick, _requiresGraphicsTick;
        Frame *_frame;
	};
}
