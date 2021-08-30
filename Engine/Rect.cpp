#include "Rect.h"
#include "Vectors.h"
#include <algorithm>

RectD::RectD(const double left, const double right, const double top, const double bottom)
    :
    m_left(left),
    m_right(right),
    m_top(top),
    m_bottom(bottom)
{
    Organize();
}

RectD::RectD(const Vec2D& topLeft, const Vec2D& bottomRight)
    :
    RectD(topLeft[0], bottomRight[0], topLeft[1], bottomRight[1])
{
}

RectD::RectD(const Vec2D& topLeft, const double width, const double height)
    :
    RectD(topLeft, topLeft + Vec2D(width, height))
{
}

double RectD::Left() const
{
    return m_left;
}

double RectD::Right() const
{
    return m_right;
}

double RectD::Top() const
{
    return m_top;
}

double RectD::Bottom() const
{
    return m_bottom;
}

const Vec2D RectD::GetCenter() const
{
    return Vec2D((Left() + Right()) / 2, (Top() + Bottom()) / 2);
}

void RectD::Organize()
{
    if (m_left > m_right)
        std::swap(m_left, m_right);
    if (m_top > m_bottom)
        std::swap(m_top, m_bottom);
}

bool RectD::isOverlapping(const RectD& rect) const
{
    return m_right > rect.Left() && m_left < rect.Right()
        && m_bottom > rect.Top() && m_top < rect.Bottom();
}

bool RectD::isWithin(const Vec2D& pos) const
{
    return pos[0] >= Left() && pos[0] <= Right()
        && pos[1] >= Top() && pos[1] <= Bottom();
}
