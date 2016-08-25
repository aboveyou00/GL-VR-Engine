#pragma once
#include "BoxBody.h"

namespace GlEngine
{
	class ENGINE_SHARED TileBoxBody : public BoxBody
	{
	public:
		TileBoxBody(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, int tileId);
		~TileBoxBody();

		virtual const char * name();
		virtual int id() override;
		virtual bool Collide(Body * other, Collision*& out, bool trySwitch = true) override;

		int tileId;
	};
}