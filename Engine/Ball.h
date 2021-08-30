#pragma once
#include "Entity.h"
#include "Colors.h"
#include "Board.h"
#include "Vectors.h"
#include "Brick.h"
#include "Paddle.h"


class Ball : public Entity
{
public:

    Ball() = default;
    Ball(const Board& board, const double r, const Vec2D& pos, const Vec2D& vel, const Color c);
    void Draw() const;
    bool Update(const double dt);
    bool IsColliding(const Brick& brick, const double dt) const;
    void Collision(const Paddle& paddle, const double dt);
    void Collision(Brick& brick, const double dt);

private:

    const Board& m_board;
    double m_r;
    Color m_c;
    bool m_paddleCooldown;

};

