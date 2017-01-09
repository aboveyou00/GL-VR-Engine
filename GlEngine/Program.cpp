#include "stdafx.h"
#include "Program.h"
#include "Attribute.h"
#include "Snippet.h"
#include "ComponentType_attribs.h"
#include "LogUtils.h"
#include <fstream>
#include <direct.h>

#include "RawComponent.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Program::Program(bool useTesselation, bool useGeometry)
            : components(numComponents)
        {
            components[ComponentType::Input] = new Component(ComponentType::Input);
            components[ComponentType::Output] = new Component(ComponentType::Output);

            components[ComponentType::Vertex] = new Component(ComponentType::Vertex);
            components[ComponentType::Fragment] = new Component(ComponentType::Fragment);

//            components[ComponentType::Vertex] = new RawComponent(ComponentType::Vertex, R"raw(
//#version 430
//
//layout(location = 0) in vec3 in_position;
//layout(location = 1) in vec3 in_normal;
//
//layout(location = 0) uniform mat4 projection_matrix;
//layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform vec3 direct_light_position;
//layout(location = 3) uniform vec3 direct_light_color;
//layout(location = 4) uniform vec3 reflection_coefficient;
//
//layout(location = 0) out vec3 out_light_color;
//
//void main(void)
//{
//    gl_Position = projection_matrix * model_view_matrix * vec4(in_position, 1);
//	
//    vec4 temp_0074E428_0 = (model_view_matrix * vec4(in_position, 1));
//    vec4 direct_light_direction = normalize(temp_0074E428_0 - vec4(direct_light_position, 0));
//
//    float direct_light_amt = clamp(dot(direct_light_direction, vec4(in_normal, 0)), 0.0, 1.0);
//    vec3 direct_light = reflection_coefficient * direct_light_amt * direct_light_color;
//    //out_light_color = ambient_light_color + direct_light;
//	
//    out_light_color = direct_light;
//}
//)raw");
//
//            components[ComponentType::Fragment] = new RawComponent(ComponentType::Fragment, R"raw(
//#version 430
//
//layout(location = 0) in vec3 in_light_color;
//
////layout(location = 0) uniform mat4 projection_matrix;
////layout(location = 1) uniform mat4 model_view_matrix;
////layout(location = 2) uniform vec3 direct_light_direction;
////layout(location = 3) uniform vec3 direct_light_color;
////layout(location = 4) uniform vec3 ambient_light_color;
//
//layout(location = 0) out vec4 out_color;
//
//void main(void)
//{
//    vec4 direct_color = vec4(base_color, 1) * vec4(in_light_color, 1);
//    out_color = direct_color;
//
//    //const vec4 fog_color = vec4(0.0, 0.0, 0.0, 1.0);
//
//    //float dist = gl_FragCoord.z / gl_FragCoord.w;
//    //float fog_amt = clamp(sqrt(dist) / 6, 0.0, 1.0);
//    //out_color = mix(direct_color, fog_color, fog_amt);
//}
//)raw");

            if (useTesselation)
            {
                components[ComponentType::TessControl] = new Component(ComponentType::TessControl);
                components[ComponentType::TessEvaluation] = new Component(ComponentType::TessEvaluation);
            }
            if (useGeometry)
            {
                components[ComponentType::Geometry] = new Component(ComponentType::Geometry);
            }
        }
        Program::~Program()
        {
            for (unsigned i = 0; i < numComponents; i++)
            {
                if (components[i] != nullptr)
                    delete components[i];
            }
        }

        void Program::AddPropertySource(PropertySource *propSource)
        {
            assert(!compilationStarted);
            this->propSources.push_back(propSource);
        }
        void Program::AddAttribute(Attribute* attribute)
        {
            assert(!compilationStarted);
            for (unsigned i = 0; i < attribute->numComponents; i++)
            {
                if (components[i] == nullptr)
                {
                    assert(attribute->snippets[i].size() == 0);
                    continue;
                }
                for (Snippet* snippet : attribute->snippets[i])
                    components[i]->unresolvedSnippets.insert(snippet);
            }
        }

        ShaderSource *Program::Compile()
        {
            assert(!compilationStarted);
            compilationStarted = true;
            
            BootstrapInputs();
            BootstrapOutputs();

            ResolveProperties();
            auto source = new ComponentArray<std::string*>();

            for (auto type = ComponentType::Vertex; type != ComponentType::Output; type++)
            {
                if (components[type] == nullptr) continue;
                (*source)[type] = new std::string(components[type]->Compile());
                Util::Log(LogType::Info, "%s:\n%s", NameOf(type).c_str(), (*source)[type]->c_str());
            }

            return source;
        }

        void Program::BootstrapInputs()
        {
        }

        void Program::BootstrapOutputs()
        {
            components[ComponentType::Output]->unresolvedSnippets.insert(new Snippet("", { &prop_RgbaColor }, std::vector<ShaderProp*>()));
            // TODO: delete
        }

        void Program::ResolveProperties()
        {
            for (unsigned i = 0; i < numComponents; i++)
            {
                if (components[i] == nullptr)
                    continue;

                while (true)
                {
                    components[i]->ResolveSnippets();
                    if (components[i]->unresolvedSnippets.size() == 0)
                        break;

                    for (ShaderProp* input : components[i]->unresolvedInputs)
                    {
                        for (int j = i - 1; j >= 0; j--)
                        {
                            if (components[j] == nullptr)
                                continue;

                            auto props = components[j]->availableLocalProps;
                            if (std::find(props.begin(), props.end(), input) != props.end())
                            {
                                ConnectComponentsProperty(j, i, input);
                                goto found;
                            }
                        }
                        for (PropertySource* source : propSources)
                        {
                            if (source->HasProperty(input))
                            {
                                source->ProvideProperty(input, this, (ComponentType)i);
                                goto found;
                            }
                        }
                    }

                    // CANNOT RESOLVE DEPENDENCIES

                    //Util::Log(LogType::Error, "Could not resolve dependencies when compiling %s shader; enable level logging 'info' to view snippet data", NameOf((ComponentType)i));
                    //for (Snippet* snippet : components[i]->unresolvedSnippets)
                    //    Util::Log(LogType::Info, "\nSnippetDecl:\n%s\nSnippet Main:\n%s", snippet->declSource, snippet->mainSource);    
                    for (ShaderProp* prop : components[i]->unresolvedOutputs)
                        components[i]->availableLocalProps.insert(prop);
                    break;
                
                found:;
                }
            }
        }

        int Program::FindUniform(ShaderProp *prop)
        {
            for (auto it : uniforms)
                if (it.second == prop)
                    return it.first;
            return -1;
        }
        unsigned Program::FindOrCreateUniform(ShaderProp *prop)
        {
            auto location = FindUniform(prop);
            if (location != -1) return static_cast<unsigned>(location);

            unsigned idx = uniforms.size();
            uniforms[idx] = prop;
            return idx;
        }
        void Program::ConnectComponentsProperty(unsigned firstIndex, unsigned lastIndex, ShaderProp * prop)
        {
            assert(firstIndex < lastIndex);
            components[firstIndex]->orderedSnippets.push_back(Snippet::IdentitySnippet(prop, false, true));
            unsigned idx = components[firstIndex]->FindOrCreateOutput(prop);
            for (unsigned i = firstIndex + 1; i < lastIndex; i++)
            {
                if (components[i] == nullptr)
                    continue;

                components[i]->ins[idx] = prop;
                components[i]->orderedSnippets.push_back(Snippet::IdentitySnippet(prop, true, true));
                idx = components[i]->FindOrCreateOutput(prop);
            }
            components[lastIndex]->ins[idx] = prop;
            components[lastIndex]->orderedSnippets.insert(components[lastIndex]->orderedSnippets.begin(), Snippet::IdentitySnippet(prop, true, false));
        }

        void Program::WriteToDisk(std::string name)
        {
            assert(name.length() > 0);
            _mkdir("generated_shader");
            for (unsigned i = 0; i < numComponents; i++)
            {
                ComponentType type = (ComponentType)i;
                if (type == ComponentType::Input || type == ComponentType::Output || components[type] == nullptr)
                    continue;
                std::ofstream outFile;
                outFile.open("generated_shader/" + name + "." + NameOf(type) + ".shader");
                outFile << components[type]->compiled;
                outFile.close();
            }
        }
    }
}
