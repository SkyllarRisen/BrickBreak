#pragma once



class Vec2D
{
public:

    Vec2D();
    Vec2D(const double x, const double y);

    double& operator[](const int index);
    const double& operator[](const int index) const;

    Vec2D operator+(const Vec2D& v) const;
    Vec2D& operator+=(const Vec2D& v) ;
    Vec2D operator-(const Vec2D& v) const;
    Vec2D& operator-=(const Vec2D& v) ;

    Vec2D operator*(const double n) const;
    friend Vec2D operator*(const double n, const Vec2D& v);
    Vec2D& operator*=(const double n) ;
    Vec2D operator/(const double n) const;
    friend Vec2D operator/(const double n, const Vec2D& v);
    Vec2D& operator/=(const double n) ;

    Vec2D operator-() const;
    double operator*(const Vec2D& v) const;

    double NormSq() const;
    double Norm() const;
    Vec2D Direction() const;
    Vec2D& Normalize();

private:
    double m_x, m_y;
};


class Vec3D
{
public:

    Vec3D(const Vec2D xy = Vec2D(), const double z = 0);
    Vec3D(const double x, const double y, const double z);
    

    double& operator[](const int index);
    const double& operator[](const int index) const;

    Vec3D operator+(const Vec3D& v) const;
    Vec3D& operator+=(const Vec3D& v);
    Vec3D operator-(const Vec3D& v) const;
    Vec3D& operator-=(const Vec3D& v);

    Vec3D operator*(const double n) const;
    friend Vec3D operator*(const double n, const Vec3D& v);
    Vec3D& operator*=(const double n);
    Vec3D operator/(const double n) const;
    friend Vec3D operator/(const double n, const Vec3D& v);
    Vec3D& operator/=(const double n);

    Vec3D operator-() const;
    double operator*(const Vec3D& v) const;
    Vec3D operator%(const Vec3D& v) const;
    Vec3D& operator%=(const Vec3D& v);

    double NormSq() const;
    double Norm() const;
    Vec3D Direction() const;
    Vec3D& Normalize();

    const Vec2D& Get2D() const;

private:
    Vec2D m_xy;
    double m_z;
};

