#pragma once

#include "RigidBody.h"

namespace GlEngine
{
	class BoxBody : public RigidBody
	{
	public:
		BoxBody(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
		~BoxBody();

		float minX, maxX, minY, maxY, minZ, maxZ;

		virtual const char * name();
		virtual bool Collide(Body * other, bool trySwitch = true) override;

		virtual float MinX() override;
		virtual float MaxX() override;
		virtual float MinY() override;
		virtual float MaxY() override;
		virtual float MinZ() override;
		virtual float MaxZ() override;

	private:
		static void BacktrackSingle(Body * first, Body * second); // Backtracks the second argument
		static void Backtrack(Body * first, Body * second);
	};
}