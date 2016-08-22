#include "stdafx.h"
#include "Property.h"

#include "StringUtils.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		Property::Property(std::string name, std::string datatype, int arraylength)
			: name(name), datatype(datatype), arraylength(arraylength)
		{
		}
		Property::~Property()
		{
		}

		std::string Property::DeclerationString(std::string prefix)
		{
			return datatype + " " + prefix + name + (arraylength == -1 ? "" : Util::formatted("[%i]", arraylength));
		}
	}
}