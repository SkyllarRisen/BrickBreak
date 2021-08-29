#include "Ball.h"
#include "Board.h"
#include "Vectors.h"
#include "Entity.h"
#include "Colors.h"

Ball::Ball(const Board& board, const double r, const Vec2D& pos, const Vec2D& vel, const Color c)
    :
    Entity("Ball", pos, vel),
    m_board(board),
    m_r(r),
    m_c(c)
{
}

void Ball::Draw() const
{
    m_board.Draw(Pos().Get2D(),m_r,m_c);
}
