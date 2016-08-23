#pragma once

#include "GameObject.h"

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

	class ENGINE_SHARED CameraGameObject : public GameObject
	{
	public:
		CameraGameObject();
		~CameraGameObject();

		void SetTargetObject(GameObject* gameObject);

		virtual const char * name() override;
		virtual GameObjectType type() const override;
		virtual GraphicsObject * CreateGraphicsObject(GraphicsContext & ctx) override;
		
		virtual void Tick(float delta) override;

		virtual void SetLock(int lockFlags);
		virtual void Lock(int lockFlags);

		virtual void FindOrientation();

		GameObject* target;

		Vector<3> relativePosition;
		Matrix<4, 4> relativeOrientation;

		bool lockRelativePosition;
		bool lockRelativeOrientation;
		bool lockAbsolutePosition;
		bool lockAbsoluteOrientation;

		virtual void SetPosition(Vector<3> pos) override;
	};
}