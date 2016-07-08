#pragma once

#include "EngineShared.h"
#include "FbxGraphicsObject.h"
#include "FbxParser.h"
#include <fstream>
#include <vector>
#include <string>

namespace GlEngine
{
	class ENGINE_SHARED FbxLoader
	{
	public:
		static bool Load(const char * const filename, FbxGraphicsObject * out);
		static bool Load(std::istream & in, FbxGraphicsObject * out);

		static char * currentFilename;

		static const char nodeDelimLeft = '{';
		static const char nodeDelimRight = '}';
		static const char propertySeperator = ':';
		static const char propertyArraySeperator = ',';

	private:
		
		static bool Convert(Fbx::Node * node, FbxGraphicsObject * out);
		static void ConvertIndeces(std::vector<int32_t> indeces, int& triangulatedSize, int32_t * triangulated);

		static Fbx::Node * ParseAsciiNode(std::istream & in);
		static Fbx::Property * ParseAsciiProperty(std::istream & in);
		static std::vector<Fbx::Value> ParseAsciiValueArray(std::istream & in);
		static Fbx::Value * ParseAsciiValue(std::istream & in);
		static Fbx::Value * ParseAsciiValueString(std::istream & in);
		static Fbx::Value * ParseAsciiValueNumeric(std::istream & in);

	};
}