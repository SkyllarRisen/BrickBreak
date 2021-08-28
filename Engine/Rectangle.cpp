#include "Rectangle.h"
#include "Vectors.h"
#include <algorithm>

Rectangle::Rectangle(const double left, const double right, const double top, const double bottom)
    :
    m_left(left),
    m_right(right),
    m_top(top),
    m_bottom(bottom)
{
    Organize();
}

Rectangle::Rectangle(const Vec2D& topLeft, const Vec2D& bottomRight)
    :
    Rectangle(topLeft[0], bottomRight[0], topLeft[1], bottomRight[1])
{
}

Rectangle::Rectangle(const Vec2D& topLeft, const double width, const double height)
    :
    Rectangle(topLeft, topLeft + Vec2D(width, height))
{
}

double Rectangle::Left() const
{
    return m_left;
}

double Rectangle::Right() const
{
    return m_right;
}

double Rectangle::Top() const
{
    return m_top;
}

double Rectangle::Bottom() const
{
    return m_bottom;
}

void Rectangle::Organize()
{
    if (m_left > m_right)
        std::swap(m_left, m_right);
    if (m_top > m_bottom)
        std::swap(m_top, m_bottom);
}

bool Rectangle::isOverlapping(const Rectangle& rect) const
{
    return m_right > rect.Left() && m_left < rect.Right()
        && m_bottom > rect.Top() && m_top < rect.Bottom();
}
