#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "IGameComponent.h"

namespace GlEngine
{
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

        virtual bool Initialize();
        virtual void Shutdown();
        virtual void Tick(float delta);

        void HandleEvent(Events::Event &evt);

		Vector<3> position;
		Matrix<4, 4> orientation;

    private:
        bool _requiresTick;
	};
}
