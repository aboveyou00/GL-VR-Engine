#pragma once

#include "ComponentType.h"
#include "PropertySourceFlag.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ShaderProp;
        class Program;

        class ENGINE_SHARED PropertySource
        {
        public:
            PropertySource(PropertySourceFlag flags = PropertySourceFlag::None, std::vector<ComponentType> supportedComponents = {ComponentType::Vertex, ComponentType::TessControl, ComponentType::TessEvaluation, ComponentType::Geometry, ComponentType::Fragment});
            ~PropertySource();

            virtual bool HasProperty(ShaderProp* prop) = 0;
            virtual void Inject(Program* program, ComponentType type) = 0;
            virtual void ProvideInput(Program* program, ShaderProp* prop, ComponentType inputType, ComponentType sourceType);
            virtual const std::vector<ShaderProp*> outProperties() = 0;
            virtual const std::vector<ShaderProp*> inProperties();
            virtual std::string PropertyName(ShaderProp* prop);

            PropertySourceFlag flags;

            bool hasFlag(PropertySourceFlag flag) const;
            void SetFlag(PropertySourceFlag flag, bool val);
            void SetFlag(PropertySourceFlag flag);
            void ResetFlag(PropertySourceFlag flag);
            // TODO: add isFallback();

            std::vector<ComponentType> supportedComponents;

            std::vector<ComponentType> componentsEarliest();
            std::vector<ComponentType> componentsLatest();
            std::vector<ComponentType> componentsDefault();

            bool noSideEffects() const;
            bool hasSideEffects() const;

            static PropertySource *resolvedPropertySource;
        };
    }
}
