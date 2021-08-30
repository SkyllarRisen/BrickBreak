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
    m_c(c),
    m_paddleCooldown(false)
{
}

void Ball::Draw() const
{
    m_board.DrawBall(Pos().Get2D(),m_r,m_c);
}

bool Ball::Update(const double dt)
{
    Vec2D tmpPos = Pos().Get2D() + Vel().Get2D() * dt;
    if (tmpPos[0] - m_r < 0 || tmpPos[0] + m_r > m_board.PlayZone().Right() - m_board.PlayZone().Left())
    {
        Move(Vec2D(Vel()[0] * dt,0));
        ChangeVel(Vec2D(-2 * Vel()[0], 0));
        m_paddleCooldown = false;
    }
    if (tmpPos[1] - m_r < 0)
    {
        Move(Vec2D(0, Vel()[1] * dt));
        ChangeVel(Vec2D(0, -2 * Vel()[1]));
        m_paddleCooldown = false;
    }
    if (tmpPos[1] + m_r > m_board.PlayZone().Bottom() - m_board.PlayZone().Top())
    {
        return false;
    }
    Move(Vel() * dt);
    return true;
}

void Ball::Collision(Brick& brick, const double dt)
{
    const Vec2D tmpPos = Pos().Get2D() + Vel().Get2D() * dt;
    const Vec2D tmpRad = Vec2D(m_r, m_r);
    const RectD rect = RectD(tmpPos - tmpRad, tmpPos + tmpRad);
    brick.Break();
    if (Pos().Get2D()[0] > brick.GetRect().Left() && Pos().Get2D()[0] < brick.GetRect().Right())
    {
        Move(Vec2D(0, Vel()[1] * dt));
        ChangeVel(Vec2D(0, -2 * Vel()[1]));
    }
    else if (tmpPos[0] < brick.GetRect().Left() && Vel()[0] > 0 || tmpPos[0] > brick.GetRect().Right() && Vel()[0] < 0)
    {
        Move(Vec2D(Vel()[0] * dt, 0));
        ChangeVel(Vec2D(-2 * Vel()[0], 0));
    }
    else
    {
        Move(Vec2D(0, Vel()[1] * dt));
        ChangeVel(Vec2D(0, -2 * Vel()[1]));
    }
    m_paddleCooldown = false;
}

bool Ball::IsColliding(const Brick& brick, const double dt) const
{
    if (!brick.IsBroken())
    {
        const Vec2D tmpPos = Pos().Get2D() + Vel().Get2D() * dt;
        const Vec2D tmpRad = Vec2D(m_r, m_r);
        const RectD rect = RectD(tmpPos-tmpRad, tmpPos+tmpRad);
        if (rect.isOverlapping(brick.GetRect()))
        {
            return true;
        }
    }
    return false;
}

void Ball::Collision(const Paddle& paddle, const double dt)
{
    if (!m_paddleCooldown)
    {
        const Vec2D tmpPos = Pos().Get2D() + Vel().Get2D() * dt;
        const Vec2D tmpRad = Vec2D(m_r, m_r);
        const RectD rect = RectD(tmpPos - tmpRad, tmpPos + tmpRad);
        if (rect.isOverlapping(paddle.GetRect()))
        {
            if (Pos().Get2D()[0] > paddle.GetRect().Left() - m_r / 2 && Pos().Get2D()[0] < paddle.GetRect().Right() + m_r / 2)
            {
                Move(Vec2D(0, Vel()[1] * dt));
                const double tmpSpeed = Vel().Norm();
                ChangeVel(-Vel());
                ChangeVel((Pos().Get2D() - paddle.GetCenter()).Normalize() * tmpSpeed);
            }
            else if (tmpPos[0] < paddle.GetRect().Left() && Vel()[0] > 0 || tmpPos[0] > paddle.GetRect().Right() && Vel()[0] < 0)
            {
                Move(Vec2D(Vel()[0] * dt, 0));
                ChangeVel(Vec2D(-2 * Vel()[0], 0));
            }
            else
            {
                Move(Vec2D(0, Vel()[1] * dt));
                ChangeVel(Vec2D(0, -2 * Vel()[1]));
            }
            m_paddleCooldown = true;
        }

    }
}

