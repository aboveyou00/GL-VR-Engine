#pragma once

#include "EngineShared.h"
#include "GraphicsObject.h"
#include <fstream>

namespace GlEngine
{
	namespace Fbx
	{
		enum class Type
		{
			NODE,
			INT32,
			//...
		};

		class Value
		{
		public:
			Type type;
			void * _value; // Figure out the best way to store this on the stack
		};

		class ValueArray
		{
		public:
			static const int maxValues = 64;
			Value values[maxValues];
			int numValues = 0;
		};

		class Property
		{
		public:
			static const int maxNameLength = 64;
			char name[maxNameLength];
			ValueArray values;
		};

		class Node
		{
		public:
			static const int maxProperties = 1024;
			Property properties[maxProperties];
			int numProperties = 0;
		};
	}

	class ENGINE_SHARED FbxLoader
	{
	public:
		static GraphicsObject Load(const char * const filename);
		static GraphicsObject Load(std::istream & in);

		static const char NodeDelimLeft = '{';
		static const char NodeDelimRight = '}';
		static const char PropertySeperator = ':';
		static const char PropertyArraySeperator = ',';

	private:
		
		static Fbx::Node Parse(std::istream & in);
		static Fbx::Node ParseNode(std::istream & in);
		static Fbx::Property ParseProperty(std::istream & in);
		static Fbx::ValueArray ParseValueArray(std::istream & in);
		static Fbx::Value ParseValue(std::istream & in);

	};
}