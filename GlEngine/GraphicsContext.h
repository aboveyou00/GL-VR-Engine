#pragma once

#include "EngineShared.h"
#include "IComponent.h"
#include "TransformedGraphicsObject.h"
#include <set>
#include <unordered_map>
#include "Camera.h"
#include "GameObject.h"
#include "GlRenderTarget.h"

namespace GlEngine
{
	class ENGINE_SHARED GraphicsContext : public IComponent 
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		std::mutex _lock;
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
	
	private:

		static const int maxRenderTargets = 256;
		GlRenderTarget * renderTargets[maxRenderTargets];
		int renderTargetCount = 0;
	};
}