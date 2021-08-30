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
    for (int x = int(borderZone.Left()); x <= int(borderZone.Right()); ++x)
    {
        for (int y = int(borderZone.Top()); y <= int(borderZone.Bottom()); ++y)
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
    for (int x = int(boardPos[0] - r); x <= int(boardPos[0] + r); ++x)
    {
        for (int y = int(boardPos[1] - r); y <= int(boardPos[1] + r); ++y)
        {
            if ((boardPos - Vec2D(x, y)).NormSq() <= (r-2) * (r-2))
                gfx.PutPixel(x, y, c);
            else if ((boardPos - Vec2D(x, y)).NormSq() <= r * r)
                gfx.PutPixel(x, y, Colors::Black);
        }
    }
}

void Board::DrawBrick(const RectD& brick, const Color c) const
{
    RectD tmp = RectD(Vec2D(PlayZone().Left(), PlayZone().Top()) + Vec2D(brick.Left(), brick.Top()), brick.Right()-brick.Left(), brick.Bottom()-brick.Top());
    for (int x = int(tmp.Left()); x <= int(tmp.Right()); ++x)
    {
        for (int y = int(tmp.Top()); y <= int(tmp.Bottom()); ++y)
        {
            if (x > tmp.Left()+1 && x < tmp.Right()-1 && y > tmp.Top()+1 && y < tmp.Bottom()-1)
                gfx.PutPixel(x, y, c);
            else
                gfx.PutPixel(x, y, Colors::Gray);
        }
    }
}

const RectD& Board::PlayZone() const
{
    return playZone;
}
