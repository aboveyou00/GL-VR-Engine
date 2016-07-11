#include "stdafx.h"
#include "FbxParser.h"

namespace GlEngine
{
	namespace Fbx
	{
		Node * Value::AsNode() const
		{
			assert(type == Type::NODE);
			return _value._node_v;
		}
		bool Value::AsBool() const
		{
			assert(type == Type::BOOL_8);
			return _value._bool_v;
		}
		int16_t Value::AsInt16() const
		{
			assert(type == Type::INT_16);
			return _value._int16_v;
		}
		int32_t Value::AsInt32() const
		{
			assert(type == Type::INT_32);
			return _value._int32_v;
		}
		int64_t Value::AsInt64() const
		{
			assert(type == Type::INT_64);
			return _value._int64_v;
		}
		float Value::AsFloat32() const
		{
			assert(type == Type::FLOAT_32);
			return _value._float32_v;
		}
		double Value::AsFloat64() const
		{
			assert(type == Type::FLOAT_64);
			return _value._float64_v;
		}
		int32_t Value::AsQuantifier() const
		{
			assert(type == Type::QUANTIFIER);
			return _value._int32_v;
		}
		std::string * Value::AsString() const
		{
			assert(type == Type::STRING);
			return _value._string_v;
		}

		NodePropertyIterator Node::PropertiesWithName(std::string name)
		{
			return NodePropertyIterator(this, name);
		}

		Property * Node::PropertyWithName(std::string name)
		{
			return &*PropertiesWithName(name);
		}

		NodePropertyIterator::NodePropertyIterator(Node * node, std::string name)
			: node(node), name(name)
		{
			index = 0;
			while (!MatchName(index) && index < node->properties.size())
				index++;
		}

		NodePropertyIterator::NodePropertyIterator(Node * node)
			: NodePropertyIterator(node, "")
		{
		}

		bool NodePropertyIterator::MatchName(int i)
		{
			return name == "" || node->properties[i].name == name;
		}

		Property& NodePropertyIterator::operator*() const
		{
			return node->properties[index];
		}

		Property* NodePropertyIterator::operator->() const
		{
			return &node->properties[index];
		}

		NodePropertyIterator& NodePropertyIterator::operator++()
		{
			if (index == node->properties.size())
				return *this;
			index++;
			while (!MatchName(index) && index < node->properties.size())
				index++;
			return *this;
		}

		NodePropertyIterator NodePropertyIterator::operator++(int n)
		{
			if (n == 0)
				n = 1;

			auto result = NodePropertyIterator(node, name);
			result.index = index;

			for (int i = 0; i < n; i++)
				++(*this);
			return result;
		}

		bool operator==(NodePropertyIterator & left, NodePropertyIterator & right)
		{
			return (left.node == right.node) && (left.name == right.name) && (left.index == right.index);
		}

		bool NodePropertyIterator::ended()
		{
			return index == node->properties.size();
		}

		std::vector<Node*> Property::NodeValues() const
		{
			std::vector<Node*> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsNode());
			return result;
		}
		std::vector<bool> Property::BoolValues() const
		{
			std::vector<bool> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsBool());
			return result;
		}
		std::vector<int16_t> Property::Int16Values() const
		{
			std::vector<int16_t> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsInt16());
			return result;
		}
		std::vector<int32_t> Property::Int32Values() const
		{
			std::vector<int32_t> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsInt32());
			return result;
		}
		std::vector<int64_t> Property::Int64Values() const
		{
			std::vector<int64_t> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsInt64());
			return result;
		}
		std::vector<float> Property::Float32Values() const
		{
			std::vector<float> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsFloat32());
			return result;
		}
		std::vector<double> Property::Float64Values() const
		{
			std::vector<double> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsFloat64());
			return result;
		}
		std::vector<int32_t> Property::QuantifierValues() const
		{
			std::vector<int32_t> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsQuantifier());
			return result;
		}
		std::vector<std::string*> Property::StringValues() const
		{
			std::vector<std::string*> result;
			for (unsigned i = 0; i < values.size(); i++)
				result.push_back(values[i].AsString());
			return result;
		}

		Node * Property::AsNode() const
		{
			assert(values.size() == 1);
			return values[0].AsNode();
		}
		bool Property::AsBool() const
		{
			assert(values.size() == 1);
			return values[0].AsBool();
		}
		int16_t Property::AsInt16() const
		{
			assert(values.size() == 1);
			return values[0].AsInt16();
		}
		int32_t Property::AsInt32() const
		{
			assert(values.size() == 1);
			return values[0].AsInt32();
		}
		int64_t Property::AsInt64() const
		{
			assert(values.size() == 1);
			return values[0].AsInt64();
		}
		float Property::AsFloat32() const
		{
			assert(values.size() == 1);
			return values[0].AsFloat32();
		}
		double Property::AsFloat64() const
		{
			assert(values.size() == 1);
			return values[0].AsFloat64();
		}
		int32_t Property::AsQuantifier() const
		{
			assert(values.size() == 1);
			return values[0].AsQuantifier();
		}
		std::string * Property::AsString() const
		{
			assert(values.size() == 1);
			return values[0].AsString();
		}
	}
}