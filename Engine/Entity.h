#pragma once
#include "Vectors.h"
#include <string>


class Entity
{
public:

    Entity() = delete;
    Entity(std::string type, Vec2D pos = Vec2D(0, 0), Vec2D vel = Vec2D(0,0));
    Entity(std::string type, Vec3D pos, Vec3D vel = Vec3D(0,0,0));
    


    std::string Type() const;
    const Vec3D& Pos() const;
    const Vec3D& Vel() const;
    unsigned int ID() const;

    bool operator==(const Entity& e) const;
protected:

    void Move(const double x, const double y, const double z);
    void Move(const Vec2D& xy, const double z = 0);
    void Move(const Vec3D& xyz);
    void changeVel(const double x, const double y, const double z);
    void changeVel(const Vec2D& xy, const double z = 0);
    void changeVel(const Vec3D& xyz);

    static unsigned int numberOfEntities;

private:

    const std::string m_type;
    const unsigned int m_id;
    Vec3D m_pos, m_vel;
    
};

