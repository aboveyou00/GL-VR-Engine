#pragma once

#include "EngineShared.h"
#include "IComponent.h"
#include "TransformedGraphicsObject.h"
#include <set>
#include <unordered_map>
#include "Camera.h"
#include "GameObject.h"
#include "GlRenderTarget.h"

#include "GameLoop.h"

namespace GlEngine
{
	class ENGINE_SHARED GraphicsContext : public IComponent 
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		std::unordered_map<GameObject *, GraphicsObject *> objs;
		
		static const int maxGraphicsObjects = 100000;
		TransformedGraphicsObject transformed[maxGraphicsObjects];
		int transformedCount = 0;
		
		Camera camera;

		bool Initialize();
		void Shutdown();

		void Update();
		void Register(GameObject * gameObject, GraphicsObject * graphicsObject);
		void UnRegister(GameObject * gameObject);

		void AddRenderTarget(GlRenderTarget * renderTarget);

		void Render();

        inline rt_mutex &GetMutex()
        {
            return _lock;
        }
	
	private:
        rt_mutex _lock;

		static const int maxRenderTargets = 256;
		GlRenderTarget * renderTargets[maxRenderTargets];
		size_t renderTargetCount = 0;
        GameLoop _loop;

        bool InitializeRenderTargets();
        void Tick(float delta);
        void ShutdownRenderTargets();
	};
}
