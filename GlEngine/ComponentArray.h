#pragma once

#include "ComponentType.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        //TODO iterator
        template<typename T>
        class ComponentArray
        {
        public:
            ComponentArray(unsigned length)
            {
                _components = new T[length];
                _size = length;
            }
            ComponentArray(std::vector<T> data)
            {
                _components = new T[data.size()];
                _size = data.size();
                for (unsigned i = 0; i < data.size(); i++)
                    _components[i] = data[i];
            }
            ~ComponentArray()
            {
                delete[] _components;
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
            T* _components;
        };
    }
}
