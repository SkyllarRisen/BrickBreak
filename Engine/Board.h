#pragma once
#include "Entity.h"
#include "Graphics.h"
#include "Rect.h"


class Board : public Entity
{
public:

    Board(Graphics& gfx, const RectD& rect, const int borderWidth);
    void Draw() const;
    void Draw(const Vec2D& pos, double r, Color c) const;
    //void Draw(const Brick& brick) const;
    const RectD& PlayZone() const;

private:

    Graphics& gfx;
    RectD playZone;
    RectD borderZone;

};

