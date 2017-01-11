#pragma once

#include "ComponentType.h"
#include "limits.h"
#include <map>

namespace GlEngine
{
    namespace ShaderFactory
    {
        //TODO iterator
        template<typename T>
        class ComponentArray
        {
        public:
            ComponentArray(std::map<ComponentType, T> data = {})
                : _components({})
            {
                for (auto type = std::numeric_limits<ComponentType>::min(); type <= std::numeric_limits<ComponentType>::max(); type++)
                {
                    _components[type] = data[type];
                    if (_components.find(type) == _components.end()) _components[type] = T();
                }
            }
            ComponentArray(T vertex, T fragment)
                : ComponentArray(vertex, T(), T(), T(), fragment)
            {
            }
            ComponentArray(T vertex, T tessControl, T tessEvaluation, T fragment)
                : ComponentArray(vertex, tessControl, tessEvaluation, T(), fragment)
            {
            }
            ComponentArray(T vertex, T tessControl, T tessEvaluation, T geometry, T fragment)
            {
                _components[ComponentType::Input] = T();
                _components[ComponentType::Vertex] = vertex;
                _components[ComponentType::TessControl] = tessControl;
                _components[ComponentType::TessEvaluation] = tessEvaluation;
                _components[ComponentType::Geometry] = geometry;
                _components[ComponentType::Fragment] = fragment;
                _components[ComponentType::Output] = T();
            }
            ~ComponentArray()
            {
            }

            T& operator[](unsigned index)
            {
                return (*this)[static_cast<ComponentType>(index)];
            }
            const T& operator[](unsigned index) const
            {
                return (*this)[static_cast<ComponentType>(index)];
            }
            T& operator[](ComponentType type)
            {
                return _components.at(type);
            }
            const T& operator[](ComponentType type) const
            {
                return _components.at(type);
            }

            inline T& vertex()
            {
                return (*this)[ComponentType::Vertex];
            }
            inline T& tessControl()
            {
                return (*this)[ComponentType::TessControl];
            }
            inline T& tessEvaluation()
            {
                return (*this)[ComponentType::TessEvaluation];
            }
            inline T& geometry()
            {
                return (*this)[ComponentType::Geometry];
            }
            inline T& fragment()
            {
                return (*this)[ComponentType::Fragment];
            }

        private:
            std::map<ComponentType, T> _components;
        };

        typedef ComponentArray<std::string*> ShaderSource;
    }
}
