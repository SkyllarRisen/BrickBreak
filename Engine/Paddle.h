#pragma once
#include "Entity.h"
#include "Rect.h"
#include "Board.h"
#include "Colors.h"
#include "Keyboard.h"


class Paddle : public Entity
{
public:

    Paddle(const Board& board, const RectD& rect, const double speed, const Color c);
    void Draw() const;
    void Update(const Keyboard& kbd, const double dt);
    const RectD& GetRect() const;
    const Vec2D& GetCenter() const;

private:

    Board m_board;
    RectD m_rect;
    Color m_c;
    double m_speed;

};

