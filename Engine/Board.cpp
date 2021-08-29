#include "Board.h"
#include "Vectors.h"
#include "Rect.h"
#include "Colors.h"



Board::Board(Graphics& gfx, const RectD& rect, const int borderWidth)
    :
    Entity("Board", Vec2D(rect.Left(), rect.Top())),
    gfx(gfx),
    borderZone(rect),
    playZone(RectD(Vec2D(rect.Left(), rect.Top())+Vec2D(borderWidth, borderWidth), Vec2D(rect.Right(), rect.Bottom())-Vec2D(borderWidth, borderWidth)))
{
}

void Board::Draw() const
{
    for (int x = borderZone.Left(); x <= borderZone.Right(); ++x)
    {
        for (int y = borderZone.Top(); y <= borderZone.Bottom(); ++y)
        {
            if (!PlayZone().isWithin(Vec2D(x, y)))
                gfx.PutPixel(x, y, Colors::White);
            else if (y >= playZone.Bottom() - 30)
                gfx.PutPixel(x, y, Colors::Red);
            else
                gfx.PutPixel(x, y, Colors::Gray);
        }
    }
}

void Board::DrawBall(const Vec2D& pos, const double r, const Color c) const
{
    Vec2D boardPos = pos + Vec2D(PlayZone().Left(), PlayZone().Top());
    for (int x = boardPos[0] - r; x <= boardPos[0] + r; ++x)
    {
        for (int y = boardPos[1] - r; y <= boardPos[1] + r; ++y)
        {
            if ((boardPos - Vec2D(x, y)).NormSq() <= r * r)
                gfx.PutPixel(x, y, c);
        }
    }
}

void Board::DrawBrick(const RectD& brick, const Color c) const
{
    RectD tmp = RectD(Vec2D(PlayZone().Left(), PlayZone().Top()) + Vec2D(brick.Left(), brick.Top()), brick.Right()-brick.Left(), brick.Bottom()-brick.Top());
    for (int x = tmp.Left(); x <= tmp.Right(); ++x)
    {
        for (int y = tmp.Top(); y <= tmp.Bottom(); ++y)
        {
            if (x > tmp.Left()+1 && x < tmp.Right()-1 && y > tmp.Top()+1 && y < tmp.Bottom()-1)
                gfx.PutPixel(x, y, c);
            else
                gfx.PutPixel(x, y, Colors::Black);
        }
    }
}

const RectD& Board::PlayZone() const
{
    return playZone;
}
