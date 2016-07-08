#pragma once

#include <vector>

namespace GlEngine
{
	namespace Fbx
	{
		enum class Type
		{
			NODE,

			BOOL_8,
			INT_16,
			INT_32,
			INT_64,
			FLOAT_32,
			FLOAT_64,

			ARRAY_BOOL_8,
			ARRAY_INT_32,
			ARRAY_INT_64,
			ARRAY_FLOAT_32,
			ARRAY_FLOAT_64,

			STRING,
			BINARY,
		};

		class Node;

		class Value
		{
		public:
			Type type;

			union _Value {
				Node * _node_v;
				bool _bool_v;
				int16_t _int16_v;
				int32_t _int32_v;
				int64_t _int64_v;
				float _float32_v;
				double _float64_v;
				std::string * _string_v;
			} _value;

			Node * AsNode() const;
			bool AsBool() const;
			int16_t AsInt16() const;
			int32_t AsInt32() const;
			int64_t AsInt64() const;
			float AsFloat32() const;
			double AsFloat64() const;
			std::string * AsString() const;
		};

		class Property
		{
		public:
			std::string name;
			std::vector<Value> values;

			std::vector<Node*> NodeValues() const;
			std::vector<bool> BoolValues() const;
			std::vector<int16_t> Int16Values() const;
			std::vector<int32_t> Int32Values() const;
			std::vector<int64_t> Int64Values() const;
			std::vector<float> Float32Values() const;
			std::vector<double> Float64Values() const;
			std::vector<std::string*> StringValues() const;
		};

		class NodePropertyIterator;

		class Node
		{
		public:
			std::vector<Property> properties;
			NodePropertyIterator PropertiesWithName(std::string name);
			Property * PropertyWithName(std::string name);
		};

		class NodePropertyIterator : std::iterator<std::forward_iterator_tag, Property>
		{
		public:
			NodePropertyIterator(Node * node, std::string name);
			NodePropertyIterator(Node * node);

			Property& operator*() const;
			Property* operator->() const;
			NodePropertyIterator& operator++();
			NodePropertyIterator operator++(int);
			friend bool operator==(NodePropertyIterator & left, NodePropertyIterator & right);

			bool ended();

		private:
			bool MatchName(int i);
			std::string name;
			Node * node;
			unsigned index;
		};
	}
}