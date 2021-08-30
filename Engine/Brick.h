#pragma once
#include "Entity.h"
#include "Rect.h"
#include "Colors.h"
#include "Vectors.h"
#include "Board.h"


class Brick : public Entity
{
public:
    Brick() = default;
    Brick(const Board& board,  const RectD& rect, const Color c);

    void Draw() const;
    const RectD& GetRect() const;
    bool IsBroken() const;
    void Break();

private:

    const Board& m_board;
    RectD m_brick;
    Color m_c;
    bool m_broken;

};

