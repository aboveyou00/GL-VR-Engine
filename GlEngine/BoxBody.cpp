#include "stdafx.h"
#include "BoxBody.h"
#include "BoxCollision.h"

namespace GlEngine
{
    BoxBody::BoxBody(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
        : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ)
    {
    }
    BoxBody::~BoxBody()
    {
    }

    float BoxBody::MinX()
    {
        return minX + position[0];
    }
    float BoxBody::MaxX()
    {
        return maxX + position[0];
    }
    float BoxBody::MinY()
    {
        return minY + position[1];
    }
    float BoxBody::MaxY()
    {
        return maxY + position[1];
    }
    float BoxBody::MinZ()
    {
        return minZ + position[2];
    }
    float BoxBody::MaxZ()
    {
        return maxZ + position[2];
    }

    std::string BoxBody::name()
    {
        return "BoxBody";
    }

    int BoxBody::id()
    {
        return 1;
    }

    bool BoxBody::Collide(Body * other, Collision*& out, bool trySwitch)
    {
        if (!movable && !other->movable)
            return false;

        if (other->id() == 1)
        {
            auto boxOther = (BoxBody*)other;

            if (MinX() < boxOther->MaxX() && MaxX() > boxOther->MinX() &&
                MinY() < boxOther->MaxY() && MaxY() > boxOther->MinY() &&
                MinZ() < boxOther->MaxZ() && MaxZ() > boxOther->MinZ())
            {
                  if (movable)
                {
                    if (other->movable)
                        Backtrack(this, other, out);
                    else
                        BacktrackSingle(other, this, out);
                }
                else
                    BacktrackSingle(this, other, out);
                return true;
            }
            return false;
        }

        if (trySwitch)
            return other->Collide(this, out, false);
        return false;
    }

    void BoxBody::BacktrackSingle(Body * first, Body * second, Collision*& out)
    {
        float dx, dy, dz;
        if ((first->MaxX() + first->MinX()) / 2 > (second->MaxX() + second->MinX()) / 2)
            dx = first->MinX() - second->MaxX();
        else
            dx = first->MaxX() - second->MinX();

        if ((first->MaxY() + first->MinY()) / 2 > (second->MaxY() + second->MinY()) / 2)
            dy = first->MinY() - second->MaxY(); 
        else
            dy = first->MaxY() - second->MinY();

        if ((first->MaxZ() + first->MinZ()) / 2 > (second->MaxZ() + second->MinZ()) / 2)
            dz = first->MinZ() - second->MaxZ();
        else
            dz = first->MaxZ() - second->MinZ();

        unsigned side;
        if (abs(dx) < abs(dy) && abs(dx) < abs(dz))
        {
            second->velocity = { signbit(second->velocity[0]) == signbit(dx) ? second->velocity[0] : 0, second->velocity[1], second->velocity[2] };
            second->position += { dx, 0, 0 };
            side = dx < 0 ? 0 : 1;
        }
        else if (abs(dy) < abs(dz))
        {
            second->velocity = { second->velocity[0], signbit(second->velocity[1]) == signbit(dy) ? second->velocity[1] : 0, second->velocity[2] };
            second->position += { 0, dy, 0 };
            side = dy < 0 ? 2 : 3;
        }
        else
        {
            second->velocity = { second->velocity[0], second->velocity[1], signbit(second->velocity[2]) == signbit(dz) ? second->velocity[2] : 0 };
            second->position += { 0, 0, dz };
            side = dz < 0 ? 4 : 5;
        }

        out = new BoxCollision(first, second, side);
    }

    void BoxBody::Backtrack(Body * first, Body * second, Collision *& out)
    {
        out;
        // TODO: set out

        float dx, dy, dz;

        if ((first->MaxX() + first->MinX()) / 2 > (second->MaxX() + second->MinX()) / 2)
            dx = first->MinX() - second->MaxX();
        else
            dx = first->MaxX() - second->MinX();

        if ((first->MaxY() + first->MinY()) / 2 > (second->MaxY() + second->MinY()) / 2)
            dy = first->MinY() - second->MaxY();
        else
            dy = first->MaxY() - second->MinY();

        if ((first->MaxZ() + first->MinZ()) / 2 > (second->MaxZ() + second->MinZ()) / 2)
            dz = first->MinZ() - second->MaxZ();
        else
            dz = first->MaxZ() - second->MinZ();

        float mag;
        if (dx > dy && dx > dz)
        {
            mag = abs(dx);
            first->velocity = { first->velocity[0], first->velocity[1], 0 };
            second->velocity = { second->velocity[0], second->velocity[1], 0 };
        }
        else if (dy > dz)
        {
            mag = abs(dy);
            first->velocity = { first->velocity[0], 0, first->velocity[2] };
            second->velocity = { second->velocity[0], 0, second->velocity[2] };
        }
        else
        {
            mag = abs(dz);
            first->velocity = { 0, first->velocity[1], first->velocity[2] };
            second->velocity = { 0, second->velocity[1], second->velocity[2] };
        }

        Vector<3> diff = { dx > 0 ? mag : -mag, dy > 0 ? mag : -mag, dz > 0 ? mag : -mag };
        second->position += diff / 2;
        first->position -= diff / 2;
    }
}