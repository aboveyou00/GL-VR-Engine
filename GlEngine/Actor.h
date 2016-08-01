#pragma once

#include "Body.h"

namespace GlEngine
{
	class Force;

	class Actor
	{
	public:
		Actor();
		~Actor();

		bool active;

		Body body;

		static const int maxForces = 16;
		Force* forces[maxForces];
		int numForces = 0;

		Vector<3> position;
		Vector<3> velocity;

		void Tick(float delta);
		void AddForce(Force* force);
	};
}