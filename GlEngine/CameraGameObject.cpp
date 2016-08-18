#include "stdafx.h"
#include "CameraGameObject.h"

namespace GlEngine
{
	CameraGameObject::CameraGameObject() : GameObject() 
	{
		RequireTick(true);
		relativeOrientation = Matrix<4, 4>::Identity();
	}
	CameraGameObject::~CameraGameObject() {}
	
	const char * CameraGameObject::name()
	{
		return "CameraGameObject";
	}

	GameObjectType CameraGameObject::type()
	{
		return GameObjectType::Camera;
	}

	GraphicsObject * CameraGameObject::CreateGraphicsObject(GraphicsContext &)
	{
		return nullptr;
	}

	void CameraGameObject::Tick(float)
	{
		if (lockRelativePosition)
			position = target->position + relativePosition;
		//if (lockRelativeOrientation)
		//	orientation = target->orientation * relativeOrientation;
	}

	void CameraGameObject::SetTargetObject(GameObject * obj)
	{
		target = obj;
		FindOrientation();
	}

	void CameraGameObject::FindOrientation()
	{
		if (target == nullptr)
			return;
		auto diff = target->position - position;
		float angleLat = atan2(diff[1], Vector<2>{diff[0], diff[2]}.Length());
		float angleLong = atan2(diff[0], diff[2]);
		orientation = Matrix<4, 4>::RollMatrix(angleLat) * Matrix<4, 4>::YawMatrix(angleLong);
	}

	void CameraGameObject::SetLock(int lockFlags)
	{
		lockRelativePosition    = (lockFlags & CameraLock::RELATIVE_POSITION) != 0;
		lockRelativeOrientation = (lockFlags & CameraLock::RELATIVE_ORIENTATION) != 0;
		lockAbsolutePosition    = (lockFlags & CameraLock::ABSOLUTE_POSITION) != 0;
		lockAbsoluteOrientation = (lockFlags & CameraLock::ABSOLUTE_ORIENTATION) != 0;
	}
	
	void CameraGameObject::Lock(int lockFlags)
	{
		lockRelativePosition    |= ((lockFlags & CameraLock::RELATIVE_POSITION) != 0);
		lockRelativeOrientation |= ((lockFlags & CameraLock::RELATIVE_ORIENTATION) != 0);
		lockAbsolutePosition    |= ((lockFlags & CameraLock::ABSOLUTE_POSITION) != 0);
		lockAbsoluteOrientation |= ((lockFlags & CameraLock::ABSOLUTE_ORIENTATION) != 0);
	}

	void CameraGameObject::SetPosition(Vector<3> pos)
	{
		if (lockAbsolutePosition)
			return;
		GameObject::SetPosition(pos);
		if (target != nullptr)
			relativePosition = target->position - position;
		FindOrientation();
	}

}