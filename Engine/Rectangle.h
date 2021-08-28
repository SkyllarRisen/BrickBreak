#pragma once
#include "Vectors.h"

class Rectangle
{
public:

    Rectangle() = default;
    Rectangle(const double left, const double right, const double top, const double bottom);
    Rectangle(const Vec2D& topLeft, const Vec2D& bottomRight);
    Rectangle(const Vec2D& topLeft, const double width, const double height);
    
    double Left() const;
    double Right() const;
    double Top() const;
    double Bottom() const;

    bool isOverlapping(const Rectangle& rect) const;

private:

    void Organize();

    double m_left;
    double m_right;
    double m_top;
    double m_bottom;
 
};

