#include "stdafx.h"
#include "Camera.h"

namespace GlEngine
{
	Camera::Camera()
		: pimpl(new Impl::CameraImpl())
	{
	}
	Camera::~Camera()
	{
		if (pimpl != nullptr)
		{
			delete pimpl;
			pimpl = nullptr;
		}
	}

	void Camera::Push()
	{
		pimpl->Push();
	}
	void Camera::Pop()
	{
		pimpl->Pop();
	}

	Vector<3> Camera::GetEye()
	{
		return pimpl->eye;
	}
	Vector<3> Camera::GetUp()
	{
		return pimpl->up;
	}
	Vector<3> Camera::GetTarget()
	{
		return pimpl->target;
	}

	void Camera::SetEye(Vector<3> eye)
	{
		pimpl->eye = eye;
	}
	void Camera::SetUp(Vector<3> up)
	{
		pimpl->up = up;
	}
	void Camera::SetTarget(Vector<3> target)
	{
		pimpl->target = target;
	}
}