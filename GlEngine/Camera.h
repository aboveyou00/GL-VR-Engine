#pragma once

#include "CameraImpl.h"

namespace GlEngine
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void ApplyView();
		void ApplyProjection();

		Vector<3> GetEye();
		Vector<3> GetUp();
		Vector<3> GetCenter();

		void SetEye(Vector<3> eye);
		void SetUp(Vector<3> up);
		void SetCenter(Vector<3> center);

		inline Impl::CameraImpl &GetImpl()
		{
			return *pimpl;
		}

	private:
		Impl::CameraImpl * pimpl;

	};
}