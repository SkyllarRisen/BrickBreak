#pragma once
#include "Vectors.h"

class RectD
{
public:

    RectD() = default;
    RectD(const double left, const double right, const double top, const double bottom);
    RectD(const Vec2D& topLeft, const Vec2D& bottomRight);
    RectD(const Vec2D& topLeft, const double width, const double height);
    
    double Left() const;
    double Right() const;
    double Top() const;
    double Bottom() const;

    bool isOverlapping(const RectD& rect) const;
    bool isWithin(const Vec2D& pos) const;

private:

    void Organize();

    double m_left;
    double m_right;
    double m_top;
    double m_bottom;
 
};

