#pragma once

class Rectangle;
class Circle;

class Point {
public:
    float X;
    float Y;
    inline Point () : X(0), Y(0) {}
    inline Point (float GivenX, float GivenY) : X(GivenX), Y(GivenY) {}
    Point operator + (const Point &OtherPoint) const;
    Point operator - (const Point &OtherPoint) const;
    bool operator == (const Point &OtherPoint) const;
};

class Vector : public Point {
public:
    inline Vector () : Point() {}
    inline Vector (float GivenX, float GivenY) : Point(GivenX, GivenY) {}
    Vector (const Point &GivenPoint) : Point(GivenPoint.X, GivenPoint.Y) {}
    Vector operator * (float Constant) const;
    float operator * (const Vector& OtherVector) const;
    float Magnitude ();
    float MagnitudeSquare ();
};

class Line {
public:
    Point Start;
    Point End;
    inline Line () = default;
    inline Line (const Point &GivenStart, const Point &GivenEnd) : Start(GivenStart), End(GivenEnd) {}
    float Length ();
    float LengthSquare ();
};

class Circle {
public:
    Point Center;
    float Radius;
    inline Circle () : Center(0.0f, 0.0f), Radius(1.0f) {}
    inline Circle (const Point &GivenCenter, float GivenRadius) : Center(GivenCenter), Radius(GivenRadius) {}
    bool operator == (const Circle &OtherCircle) const;
    bool IsIntersect (const Circle &Circle) const;
    bool IsIntersect (const Rectangle &Rectangle) const;
    bool IsIn (const Rectangle &Rectangle) const;
};

typedef Circle Particle;

class Rectangle {
public:
    Point Center;
    Vector HalfExtent;
    inline Rectangle () : Center(0.0f, 0.0f), HalfExtent(1.0f, 1.0f) {}
    inline Rectangle (const Point &GivenCenter, const Vector &GivenHalfExtent) : Center(GivenCenter), HalfExtent(GivenHalfExtent) {}
    Point GetMaxPosition () const;
    Point GetMinPosition () const;
};
