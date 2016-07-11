#include "stdafx.h"
#include "FbxLoader.h"
#include "Engine.h"
#include "ILogger.h"
#include "StringUtils.h"
#include <sstream>
#include "VBOFactory.h"

namespace GlEngine
{
	char * FbxLoader::currentFilename;

	void eatWhitespaceAndComments(std::istream& in)
	{
		while (Util::isWhitespace((char)in.peek()) || (char)in.peek() == ';')
		{
			Util::eatWhitespace(in);
			if (in.peek() == ';')
			{
				while (in.get() != '\n')
					if (in.eof() || in.fail())
						return;
				Util::eatWhitespace(in);
			}
		}
	}

	bool FbxLoader::Load(const char * const filename, FbxGraphicsObject * out)
	{	
		currentFilename = (char *)filename;
		std::ifstream in;
		in.open(filename);
		if (!in)
			return false;
		if (!Load(in, out))
			return false;
		in.close();
		return true;
	}

	bool FbxLoader::Load(std::istream& in, FbxGraphicsObject * out)
	{
		static const int x = sizeof(GraphicsObject);

		auto topNode = ParseAsciiNode(in);	
		return Convert(topNode, out);
	}

	bool FbxLoader::Convert(Fbx::Node * node, FbxGraphicsObject * out)
	{
		auto objectNode = node->PropertyWithName("Objects")->AsNode();
		for (auto modelNode_it = objectNode->PropertiesWithName("Model"); !modelNode_it.ended(); modelNode_it++)
		{
			auto modelNode = modelNode_it->AsNode();
			auto vertices = modelNode->PropertyWithName("Vertices")->Float32Values();
			
			auto rawVertexIndeces = modelNode->PropertyWithName("PolygonVertexIndex")->Int32Values();
			int * vertexIndeces = new int[rawVertexIndeces.size() * 3];
			int vertexIndecesCount;
			ConvertIndeces(rawVertexIndeces, vertexIndecesCount, vertexIndeces);

			auto normalsNode = modelNode->PropertyWithName("LayerElementNormal")->AsNode();
			auto normals = normalsNode->PropertyWithName("Normals")->Float32Values();
			std::string * normalMappingType = normalsNode->PropertyWithName("MappingInformationType")->AsString();

			normalMappingType;

			// TODO: switch above to resource thread and below to graphics thread

			VboFactory<VboType::Float, Vector<3>/*, Vector<2>, Vector<3>*/> verticesFactory(BufferMode::Array);
			for (size_t i = 0; i < vertices.size() / 3; i++)
			{
				verticesFactory.AddVertex({ vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2] });
			}
			out->subObjects.push_back(VboGraphicsObject());
		}
		return true;
	}

	void FbxLoader::ConvertIndeces(std::vector<int32_t> indeces, int& t_size, int32_t * triangulated)
	{
		// CONCAVE N-GONS NOT SUPPORTED!!

		t_size = 0;

		int polyFirst = 0;
		int polyRecent = 0;

		int i_count = 0;
		for (size_t i = 0; i < indeces.size(); i++)
		{
			if (indeces[i] < 0)
			{
				triangulated[t_size++] = ~indeces[i];
				i_count = 0;
				continue;
			}

			if (i_count >= 2)
			{
				triangulated[t_size++] = polyFirst;
				triangulated[t_size++] = polyRecent;
			}
			else if (i_count == 0)
			{
				polyFirst = indeces[i];
			}
			triangulated[t_size++] = indeces[i];
			polyRecent = indeces[i];
			i_count++;
		}
	}

	Fbx::Node * FbxLoader::ParseAsciiNode(std::istream & in)
	{
		eatWhitespaceAndComments(in);

		auto result = new Fbx::Node;
		while (in.peek() != nodeDelimRight && !in.eof())
		{
			auto prop = ParseAsciiProperty(in);
			if (prop != nullptr)
			{
				result->properties.push_back(*prop);
				delete prop;
			}
			eatWhitespaceAndComments(in);
		}
		in.get();
		return result;
	}

	Fbx::Property * FbxLoader::ParseAsciiProperty(std::istream & in)
	{
		auto result = new Fbx::Property;
	
		eatWhitespaceAndComments(in);

		std::stringstream name;
		char c;
		while ((c = (char)in.get()) != propertySeperator)
		{
			if (in.eof())
			{
				auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
				logger.Log(LogType::Warning, "EOF when scanning property name '%s' in resource '%s'", name.str(), currentFilename);
				return nullptr;
			}
			if (in.fail())
			{
				auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
				logger.Log(LogType::Warning, "Error when scanning property name '%s' in resource '%s'", name.str(), currentFilename);
				return result;
			}
			if (Util::isWhitespace(c))
			{
				auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
				logger.Log(LogType::Warning, "Invalid property encountered (cannot contain whitespace): '%s' in resource '%s'", name.str(), currentFilename);
				return nullptr;
			}
			name << c;
		}
		result->name = name.str();
		result->values = ParseAsciiValueArray(in);
		return result;
	}

	std::vector<Fbx::Value> FbxLoader::ParseAsciiValueArray(std::istream& in)
	{
		std::vector<Fbx::Value> result;
		
		eatWhitespaceAndComments(in);
		do
		{
			if (in.eof())
			{
				auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
				logger.Log(LogType::Warning, "EOF when scanning property value in resource '%s'" , currentFilename);
				return result;
			}
			if (in.fail())
			{
				auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
				logger.Log(LogType::Warning, "Error when scanning property value in resource '%s'" , currentFilename);
				return result;
			}

			auto nextValue = ParseAsciiValue(in);
			if (nextValue == nullptr)
				return result;

			result.push_back(*nextValue);
			delete nextValue;

			eatWhitespaceAndComments(in);
		} while ((char)in.peek() == nodeDelimLeft || ((char)in.peek() == propertyArraySeperator && in.get()));

		return result;
	}

	Fbx::Value * FbxLoader::ParseAsciiValue(std::istream& in)
	{
		eatWhitespaceAndComments(in);

		std::string str;
		char c = (char)in.peek();
		if (c == '"')
			return ParseAsciiValueString(in);
		else if (c == '*')
			return parseAsciiValueQuantifier(in);
		else if (Util::isNumeric(c))
			return ParseAsciiValueNumeric(in);
		else if (c == nodeDelimLeft)
		{
			in.get();
			auto node = ParseAsciiNode(in);
			auto result = new Fbx::Value;
			result->type = Fbx::Type::NODE;
			result->_value._node_v = node;
			return result;
		}
		return nullptr;
	}

	Fbx::Value * FbxLoader::ParseAsciiValueString(std::istream& in)
	{
		auto result = new Fbx::Value;
		result->type = Fbx::Type::STRING;

		in.get();
		char c;
		std::stringstream sstr;
		while ((c = (char)in.get()) != '"')
		{
			if (in.eof()) 
			{
				auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
				logger.Log(LogType::Warning, "EOF when scanning string '%s' in resource '%s'", sstr.str(), currentFilename);
				return nullptr;
			}
			if (in.fail())
			{
				auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
				logger.Log(LogType::Warning, "Error when scanning string '%s' in resource '%s'", sstr.str(), currentFilename);
				return nullptr;
			}

			if (c == '\\')
				sstr << (char)in.get();
			else
				sstr << c;
		}
		auto str_v = new std::string;
		*str_v = sstr.str();
		result->_value._string_v = str_v;
		return result;
	}

	Fbx::Value * FbxLoader::ParseAsciiValueNumeric(std::istream& in)
	{
		auto result = new Fbx::Value;
		int value_i;
		float value_f;
		if (Util::geti(in, value_i))
		{
			result->type = Fbx::Type::INT_32;
			result->_value._int32_v = value_i;
		}
		else if (Util::getf(in, value_f))
		{
			result->type = Fbx::Type::FLOAT_32;
			result->_value._float32_v = value_f;
		}
		else 
		{
			return nullptr;
		}
		return result;
	}

	Fbx::Value * FbxLoader::ParseAsciiValueQuantifier(std::istream& in)
	{
		return new Fbx::Value;
	}
}