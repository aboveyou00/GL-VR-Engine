#pragma once

#include "CameraImpl.h"

namespace GlEngine
{
	class ENGINE_SHARED Camera
	{
	public:
		Camera();
		~Camera();

		void Apply();
		
		void Push();
		void Pop();

		Vector<3> GetEye();
		Vector<3> GetUp();
		Vector<3> GetTarget();

		void SetEye(Vector<3> eye);
		void SetUp(Vector<3> up);
		void SetTarget(Vector<3> target);

		inline Impl::CameraImpl &GetImpl()
		{
			return *pimpl;
		}

	private:
		Impl::CameraImpl * pimpl;

	};
}