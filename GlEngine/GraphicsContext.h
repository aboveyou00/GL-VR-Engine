#pragma once

#include "EngineShared.h"
#include "IComponent.h"
#include "TransformedGraphicsObject.h"
#include "Camera.h"
#include "GameObject.h"
#include "GlRenderTarget.h"
#include "GameLoop.h"
#include <unordered_map>

namespace GlEngine
{
    class GraphicsObject;
    class FrameStack;
    using graphics_object_map = std::unordered_map<GameObject*, GraphicsObject*>;
	
	class ENGINE_SHARED GraphicsContext : public IComponent
	{
	public:
		GraphicsContext(FrameStack *frames);
		~GraphicsContext();

		static const int maxGraphicsObjects = 1024;
		TransformedGraphicsObject transformed[maxGraphicsObjects];
		int transformedCount = 0;
		
		Camera camera;

		bool Initialize();
		void Shutdown();

		void AddRenderTarget(GlRenderTarget * renderTarget);

		void Update(const graphics_object_map &objs);
		void UpdateCamera(GameObject*);
		void Render();

        inline rt_mutex &GetMutex()
        {
            return _lock;
        }

        const char *name() override;
	
	private:
        rt_mutex _lock;

		static const int maxRenderTargets = 256;
		GlRenderTarget * renderTargets[maxRenderTargets];
		size_t renderTargetCount = 0;
        GameLoop _loop;
        FrameStack *frames;

        bool InitializeRenderTargets();
        void Tick(float delta);
        void ShutdownRenderTargets();
	};
}
