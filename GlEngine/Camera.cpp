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

	void Camera::ApplyView()
	{
		pimpl->ApplyView();
	}
	
	void Camera::ApplyProjection()
	{
		pimpl->ApplyProjection();
	}

	Vector<3> Camera::GetEye()
	{
		return pimpl->eye;
	}
	Vector<3> Camera::GetUp()
	{
		return pimpl->up;
	}
	Vector<3> Camera::GetCenter()
	{
		return pimpl->center;
	}

	void Camera::SetEye(Vector<3> eye)
	{
		pimpl->eye = eye;
	}
	void Camera::SetUp(Vector<3> up)
	{
		pimpl->up = up;
	}
	void Camera::SetCenter(Vector<3> center)
	{
		pimpl->center = center;
	}
}