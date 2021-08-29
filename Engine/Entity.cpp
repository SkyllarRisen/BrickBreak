#include "Entity.h"
#include "Vectors.h"



unsigned int Entity::numberOfEntities = 0u;


Entity::Entity(std::string type, Vec2D pos, Vec2D vel)
    :
    m_type(type),
    m_id(numberOfEntities++),
    m_pos(pos),
    m_vel(vel)
{
}

Entity::Entity(std::string type, Vec3D pos, Vec3D vel)
    :
    m_type(type),
    m_id(numberOfEntities++),
    m_pos(pos),
    m_vel(vel)
{
}

std::string Entity::Type() const
{
    return m_type;
}

unsigned int Entity::ID() const
{
    return m_id;
}

const Vec3D& Entity::Pos() const
{

    return m_pos;   
}

const Vec3D& Entity::Vel() const
{
    return m_vel;
}



void Entity::Move(const double x, const double y, const double z)
{
    m_pos += Vec3D(x, y, z);
}

void Entity::Move(const Vec2D& xy, const double z)
{
    m_pos += Vec3D(xy, z);
}

void Entity::Move(const Vec3D& xyz)
{
    m_pos += xyz;
}

void Entity::ChangeVel(const double x, const double y, const double z)
{
    m_vel += Vec3D(x, y, z);
}

void Entity::ChangeVel(const Vec2D& xy, const double z)
{
    m_vel += Vec3D(xy, z);
}

void Entity::ChangeVel(const Vec3D& xyz)
{
    m_vel += xyz;
}

bool Entity::operator==(const Entity& e) const
{
    return (*this).ID() == e.ID();
}




