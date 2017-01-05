#include "stdafx.h"
#include "Program.h"
#include "Component.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Program::Program(bool useTesselation, bool useGeometry)
            : components(numComponents)
        {
            useTesselation; useGeometry;
            //components[ComponentType::Vertex] = new Component(ComponentType::Vertex);
            //components[ComponentType::Fragment] = new Component(ComponentType::Fragment);
            //if (useTesselation)
            //{
            //    components[ComponentType::TessControl] = new Component(ComponentType::TessControl);
            //    components[ComponentType::TessEvaluation] = new Component(ComponentType::TessEvaluation);
            //}
            //if (useGeometry)
            //{
            //    components[ComponentType::Geometry] = new Component(ComponentType::Geometry);
            //}
        }
        Program::~Program()
        {
            for (unsigned i = 0; i < numComponents; i++)
            {
                if (components[i] != nullptr) { ; }
                    //delete components[i]; //Note: this will throw a compile-time error until we remove the comments on the Component class in 
                components[i] = nullptr;
            }
        }

        //void Program::AddAttribute(Attribute* attribute)
        //{
        //    for (Property* uniform : attribute->uniforms)
        //        AddUniform(uniform);

        //    for (unsigned i = 0; i < attribute->numComponents; i++)
        //    {
        //        if (components[i] == nullptr)
        //            continue;
        //        AttributeComponent ac = attribute->attributeComponents[i];
        //        for (Property* prop : ac.constants)
        //            AddConstant((ComponentType)i, prop);
        //        for (Property* prop : ac.ins)
        //        {
        //            AddIn((ComponentType)i, prop);
        //            if ((ComponentType)i != ComponentType::Vertex)
        //                AddOut(LastComponentType(i), prop);
        //        }
        //        for (Snippet snippet : ac.snippets)
        //            AddSnippet((ComponentType)i, &snippet);
        //    }
        //}

        //void Program::AddConstant(ComponentType type, Property* property)
        //{
        //    components[type]->constants.push_back(property);
        //}
        //void Program::AddUniform(Property* property)
        //{
        //    for (int i = 0; i < numComponents; i++)
        //        components[i]->uniforms.push_back(property);
        //}
        //void Program::AddIn(ComponentType type, Property* property)
        //{
        //    components[type]->ins.push_back(property);
        //}
        //void Program::AddOut(ComponentType type, Property* property)
        //{
        //    components[type]->outs.push_back(property);
        //}
        //void Program::AddSnippet(ComponentType type, Snippet* snippet)
        //{
        //    components[type]->snippets.insert(snippet);
        //}

        ComponentType Program::NextComponentType(ComponentType type)
        {
            return NextComponentType((unsigned)type);
        }
        ComponentType Program::NextComponentType(unsigned type)
        {
            type = (type + 1) % numComponents;
            while (components[type] == nullptr)
                type = (type + 1) % numComponents;
            return (ComponentType)type;
        }
        ComponentType Program::LastComponentType(ComponentType type)
        {
            return LastComponentType((unsigned)type);
        }
        ComponentType Program::LastComponentType(unsigned type)
        {
            type = (type - 1 + numComponents) % numComponents;
            while (components[type] == nullptr)
                type = (type - 1 + numComponents) % numComponents;
            return (ComponentType)type;
        }
    }
}
