#include "stdafx.h"
#include "Program.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		Program::Program(bool useTesselation, bool useGeometry)
			: components(numComponents)
		{
			components[ComponentType::Vertex] = new Component(ComponentType::Vertex);
			components[ComponentType::Fragment] = new Component(ComponentType::Fragment);
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
			for (int i = 0; i < numComponents; i++)
			{
				if (components[i] != nullptr)
					delete components[i];
			}
		}

		void Program::AddUniform(Property* property)
		{
			for (int i = 0; i < numComponents; i++)
				components[i]->uniforms.push_back(property);
		}
		void Program::AddIn(ComponentType type, Property* property)
		{
			components[type]->ins.push_back(property);
		}
		void Program::AddOut(ComponentType type, Property* property)
		{
			components[type]->outs.push_back(property);
		}
		void Program::AddSnippet(ComponentType type, Snippet* snippet)
		{
			components[type]->snippets.insert(snippet);
		}
	}
}