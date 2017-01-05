#include "stdafx.h"
#include "Attribute.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        //Attribute::Attribute(std::vector<Property*> uniforms, std::vector<AttributeComponent> attributeComponents)
        //    : uniforms(uniforms), attributeComponents(attributeComponents)
        //{
        //}
        //Attribute::~Attribute()
        //{
        //}

        //AttributeComponent::AttributeComponent(std::vector<Property*> constants, std::vector<Property*> ins, std::vector<Snippet> snippets)
        //    : constants(constants), ins(ins), snippets(snippets)
        //{
        //}
        //AttributeComponent::~AttributeComponent()
        //{
        //}
        //
        //Attribute attr_Position = Attribute(
        //    { &prop_ModelMatrix, &prop_ViewMatrix, &prop_ProjectionMatrix },
        //    {
        //        { // Vertex
        //            {}, 
        //            {&prop_Position}, 
        //            {
        //                {"gl_Position = projection_matrix * view_matrix * model_matrix * in_position;"}
        //            }
        //        },
        //        { // TessC
        //        },
        //        { // TessE
        //        },
        //        { // Geometry
        //        },
        //        { // Fragment
        //        }
        //    }
        //);

        //Attribute attr_AmbientLight = Attribute(
        //    {},
        //    {
        //        { // Vertex
        //            {},
        //            { &prop-LightColor &prop_AmbientLightColor },
        //            {
        //                {"out_light_color += ambient_light_color;"}
        //            }
        //        },
        //        { // TessC
        //        },
        //        { // TessE
        //        },
        //        { // Geometry
        //        },
        //        { // Fragment
        //        }
        //    }
        //);
    }
}
