#pragma once

class A2DRectangle;
class A2DCircle;
typedef A2DCircle A2DParticle;

class A2DPoint
{
public:
    inline A2DPoint () : X(0), Y(0) {}
    inline A2DPoint (float X, float Y) : X(X), Y(Y) {}
    
    A2DPoint operator + (const A2DPoint &Point) const;
    A2DPoint operator - (const A2DPoint &Point) const;
    A2DPoint operator * (float Constant) const;
    float operator * (const A2DPoint &Point) const;
    bool operator == (const A2DPoint &Point) const;
    bool operator != (const A2DPoint &Point) const;
    
    float X;
    float Y;
};

class A2DVector : public A2DPoint
{
public:
    inline A2DVector () : A2DPoint() {}
    inline A2DVector (float X, float Y) : A2DPoint(X, Y) {}
    explicit A2DVector (const A2DPoint &Point) : A2DPoint(Point.X, Point.Y) {}

    A2DVector operator * (float Constant) const;
    float operator * (const A2DVector &Vector) const;

    float Magnitude () const;
    float MagnitudeSquared () const;
};

class A2DLine
{
public:
    inline A2DLine () : Begin(0.0f, 0.0f), End(0.0, 1.0f) {}
    inline A2DLine (const A2DPoint &Begin, const A2DPoint &End) : Begin(Begin), End(End) {}
    
    float Length () const;
    float LengthSquared () const;
    
    A2DPoint Begin;
    A2DPoint End;
};

class A2DCircle
{
public:
    inline A2DCircle () : Center(0.0f, 0.0f), Radius(1.0f) {}
    inline A2DCircle (const A2DPoint &Center, float Radius) : Center(Center), Radius(Radius) {}
    
    bool operator == (const A2DCircle &Circle) const;
    
    bool IsBeingIntersect (const A2DCircle &Circle) const;
    bool IsBeingIntersect (const A2DRectangle &Rectangle) const;
    bool IsIn (const A2DRectangle &Rectangle) const;
    
    A2DPoint Center;
    float Radius;
};

class A2DRectangle
{
public:
    inline A2DRectangle () : Center(0.0f, 0.0f), HalfExtent(1.0f, 1.0f) {}
    inline A2DRectangle (const A2DPoint &Center, const A2DVector &HalfExtent) : Center(Center), HalfExtent(HalfExtent) {}

    A2DPoint GetUpperBound () const;
    A2DPoint GetLowerBound () const;

    A2DPoint Center;
    A2DVector HalfExtent;
};
