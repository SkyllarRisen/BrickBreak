#include "Paddle.h"

Paddle::Paddle(const Board& board, const RectD& rect, const double speed, const Color c)
    :
    Entity("Paddle", Vec2D(rect.Left(), rect.Top())),
    m_board(board),
    m_rect(rect),
    m_speed(speed),
    m_c(c)
{
}

void Paddle::Draw() const
{
    m_board.DrawPaddle(m_rect, m_c);
}

void Paddle::Update(const Keyboard& kbd, const double dt)
{

    if (kbd.KeyIsPressed('A'))
    {
        if (!(Vel()[0] < 0 && Vel().NormSq() > m_speed * m_speed))
        {
            ChangeVel(Vec2D(-1, 0) * m_speed);
        }
    }
    if (kbd.KeyIsPressed('D'))
    {
        if (!(Vel()[0] > 0 && Vel().NormSq() > m_speed * m_speed))
        {
            ChangeVel(Vec2D(1, 0) * m_speed);
        }
    }
    if (!(kbd.KeyIsPressed('A') || kbd.KeyIsPressed('D')))
    {
        ChangeVel(Vec2D(-Vel()[0], 0));
    }

    Vec2D tmpPos = Pos().Get2D() + Vel().Get2D() * dt;
    if (tmpPos[0] < 0 || tmpPos[0] + m_rect.Right()-m_rect.Left()  > m_board.PlayZone().Right() - m_board.PlayZone().Left())
    {
        ChangeVel(Vec2D(-Vel()[0], 0));
    }

    Move(Vel() * dt);
    m_rect = RectD(Pos().Get2D(), m_rect.Right() - m_rect.Left(), m_rect.Bottom() - m_rect.Top());
}

const RectD& Paddle::GetRect() const
{
    return m_rect;
}

const Vec2D& Paddle::GetCenter() const
{
    return m_rect.GetCenter();
}
