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

void Board::Draw(const Vec2D& pos, double r, Color c) const
{
}

const RectD& Board::PlayZone() const
{
    return playZone;
}
