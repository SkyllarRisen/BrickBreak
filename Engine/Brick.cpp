#include "Brick.h"
#include "Rect.h"
#include "Colors.h"
#include "Vectors.h"

Brick::Brick(const Board& board, const RectD& rect, const Color c)
    :
    Entity("Brick", Vec2D(rect.Left(), rect.Top())),
    m_board(board),
    m_brick(rect),
    m_c(c),
    m_broken(false)
{
}


void Brick::Draw() const
{
    if(!m_broken)
        m_board.DrawBrick(m_brick, m_c);
}

const RectD& Brick::GetRect() const
{
    return m_brick;
}

bool Brick::IsBroken() const
{
    return m_broken;
}

void Brick::Break()
{
    m_broken = true;
}

