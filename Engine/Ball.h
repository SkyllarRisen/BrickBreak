#pragma once
#include "Entity.h"
#include "Colors.h"
#include "Board.h"
#include "Vectors.h"

class Ball : public Entity
{
public:

    Ball() = default;
    Ball(const Board& board, const double r, const Vec2D& pos, const Vec2D& vel, const Color c);
    void Draw() const;

private:

    const Board& m_board;
    double m_r;
    Color m_c;

};

