#pragma once

#include "ComponentType.h"
#include "limits.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        //TODO iterator
        template<typename T>
        class ComponentArray
        {
        public:
            ComponentArray(unsigned length = (unsigned)std::numeric_limits<ComponentType>::max() - (unsigned)std::numeric_limits<ComponentType>::min())
            {
                _components = std::vector<T>(length);
                _size = length;
            }
            ComponentArray(std::vector<T> data)
            {
                _components = std::vector<T>(data.size());
                _size = data.size();
                for (unsigned i = 0; i < data.size(); i++)
                    _components[i] = data[i];
            }
            ~ComponentArray()
            {
            }

            T& operator[](int index)
            {
                return _components[index];
            }
            T& operator[](ComponentType index)
            {
                return _components[static_cast<unsigned>(index)];
            }
            size_t size()
            {
                return _size;
            }

        private:
            size_t _size;
            std::vector<T> _components;
        };
    }
}
