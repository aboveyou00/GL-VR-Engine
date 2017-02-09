#pragma once

#include "VBOFactory.h"
#include <functional>
#include <tuple>
#include "RandomUtils.h"
#include "TemplateUtils.h"

template <typename... TArgs>
class PointVolume
{
private:
    PointVolume() {}
    ~PointVolume() {}

public:
    static GlEngine::VboFactory<GlEngine::VboType::Float, Vector<3>, TArgs...> *Generate(Vector<3> low, Vector<3> high, unsigned count, GlEngine::ShaderFactory::Property<TArgs>*... props, std::function<std::tuple<TArgs...>(Vector<3>)> fun)
    {
        auto factory = GlEngine::VboFactory<GlEngine::VboType::Float, Vector<3>, TArgs...>::CreateArray(&GlEngine::ShaderFactory::prop_Position, props...);

        std::function<void(Vector<3>, TArgs...)> addVertexFn([factory](Vector<3> pos, TArgs... args)
        {
            factory->AddVertex(pos, args...);
        });

        for (size_t q = 0; q < count; q++)
        {
            float x = low[0] + GlEngine::Util::random(high[0] - low[0]);
            float y = low[1] + GlEngine::Util::random(high[1] - low[1]);
            float z = low[2] + GlEngine::Util::random(high[2] - low[2]);
            auto tup = fun({ x, y, z });
            GlEngine::Util::call(addVertexFn, tup, Vector<3> { x, y, z });
        }

        return factory;
    }
};

template <>
class PointVolume<>
{
private:
    PointVolume() {}
    ~PointVolume() {}

public:
    static GlEngine::VboFactory<GlEngine::VboType::Float, Vector<3>> *Generate(Vector<3> low, Vector<3> high, unsigned count)
    {
        auto factory = GlEngine::VboFactory<GlEngine::VboType::Float, Vector<3>>::CreateArray(&GlEngine::ShaderFactory::prop_Position);

        for (size_t q = 0; q < count; q++)
        {
            float x = low[0] + GlEngine::Util::random(high[0] - low[0]);
            float y = low[1] + GlEngine::Util::random(high[1] - low[1]);
            float z = low[2] + GlEngine::Util::random(high[2] - low[2]);
            factory->AddVertex({ x, y, z });
        }

        return factory;
    }
};
