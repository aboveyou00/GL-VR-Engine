#pragma once

#include "VboFactoryGraphicsObjectImpl.h"

#include "VboGraphicsSection.h"
#include "VaoFactory.h"
#include "ShaderFactory.h"
#include "VboPropertySource.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory;

    template <VboType type, typename... TArgs>
    class VboFactoryGraphicsObject : public Impl::VboFactoryGraphicsObjectImpl
    {
    public:
        typedef VboFactory<type, TArgs...> TFactory;
        typedef VboFactory<ElementVboFactoryVboType, array_index_t> TFacesFactory;

        VboFactoryGraphicsObject(std::string name, TFactory *vertices, TFacesFactory *faces = nullptr, CreateFactoryFn createFactory = [](Material*) { return nullptr; })
            : VboFactoryGraphicsObject(name, VaObject(), vertices, faces, createFactory)
        {
        }
        VboFactoryGraphicsObject(std::string name, VaObject vao, TFactory *vertices = nullptr, TFacesFactory *faces = nullptr, CreateFactoryFn createFactory = [](Material*) { return nullptr; })
            : VboFactoryGraphicsObjectImpl(name, faces != nullptr, vertices->elementCount(), vao, createFactory),
              _verticesFactory(vertices),
              _facesFactory(faces)
        {
            if (finalized)
            {
                assert(!_verticesFactory);
                assert(!_facesFactory);
            }
            else
            {
                assert(_verticesFactory && _verticesFactory->mode() == BufferMode::Array);
                assert(!_facesFactory || _facesFactory->mode() == BufferMode::ElementArray);
            }
        }
        ~VboFactoryGraphicsObject()
        {
            SafeDelete(_verticesFactory);
            SafeDelete(_facesFactory);
        }

        virtual int AddVertex(TArgs... args)
        {
            assert(!finalized);
            _verticesFactory->AddVertex(args..., false);
            return elemIdx++;
        }

        virtual void PrepareShaderFactory(ShaderFactory::ShaderFactory *factory) override
        {
            std::vector<ShaderFactory::ShaderProp*> props;
            for (size_t q = 0; q < _verticesFactory->properties().size(); q++)
            {
                props.push_back(_verticesFactory->properties()[q]);
            }
            props.push_back(&ShaderFactory::prop_InstanceModelMatrix);
            factory->AddPropertySource(new ShaderFactory::VboPropertySource(props));
        }

        virtual bool InitializeGraphics() override
        {
            if (_verticesFactory == nullptr) return false;
            assert(allowFaces || !elemIdx || currentGraphicsSection);
            return VboFactoryGraphicsObjectImpl::InitializeGraphics();
        }

        virtual void BuildVao(VaoFactory &vao) override
        {
            if (_verticesFactory != nullptr)
            {
                for (size_t q = 0; q < graphicsSections.size(); q++)
                    graphicsSections[q]->Finalize(_facesFactory);

                vao.Add(_verticesFactory);
                if (_facesFactory != nullptr) vao.Add(_facesFactory);

                SafeDelete(_verticesFactory);
                SafeDelete(_facesFactory);
            }
            else if (_vao.isReady()) vao.Add(_vao);
        }

    private:
        TFactory *_verticesFactory;
        TFacesFactory *_facesFactory;
    };
}
