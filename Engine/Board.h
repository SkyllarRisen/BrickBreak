#pragma once
#include "Entity.h"
#include "Graphics.h"
#include "Rect.h"


class Board : public Entity
{
public:

    
    Board(Graphics& gfx, const RectD& rect, const int borderWidth);
    void Draw() const;
    void DrawBall(const Vec2D& pos, const double r, const Color c) const;
    void DrawBrick(const RectD& brick, const Color c) const;
    const RectD& PlayZone() const;

private:

    Graphics& gfx;
    RectD playZone;
    RectD borderZone;

};

