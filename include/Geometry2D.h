#pragma once

class A2DRectangle;
class A2DCircle;
typedef A2DCircle A2DParticle;

class A2DPoint {
public:
    float X;
    float Y;
    inline A2DPoint () : X(0), Y(0) {}
    inline A2DPoint (float GivenX, float GivenY) : X(GivenX), Y(GivenY) {}
    A2DPoint operator + (const A2DPoint &OtherPoint) const;
    A2DPoint operator - (const A2DPoint &OtherPoint) const;
    bool operator == (const A2DPoint &OtherPoint) const;
};

class A2DVector : public A2DPoint {
public:
    inline A2DVector () : A2DPoint() {}
    inline A2DVector (float GivenX, float GivenY) : A2DPoint(GivenX, GivenY) {}
    explicit A2DVector (const A2DPoint &GivenPoint) : A2DPoint(GivenPoint.X, GivenPoint.Y) {}
    A2DVector operator * (float Constant) const;
    float operator * (const A2DVector& OtherVector) const;
    float Magnitude () const;
    float MagnitudeSquare () const;
};

class A2DLine {
public:
    A2DPoint Begin;
    A2DPoint End;
    inline A2DLine () : Begin(0.0f, 0.0f), End(0.0, 1.0f) {}
    inline A2DLine (const A2DPoint &GivenStart, const A2DPoint &GivenEnd) : Begin(GivenStart), End(GivenEnd) {}
    float Length () const;
    float LengthSquare () const;
};

class A2DCircle {
public:
    A2DPoint Center;
    float Radius;
    inline A2DCircle () : Center(0.0f, 0.0f), Radius(1.0f) {}
    inline A2DCircle (const A2DPoint &GivenCenter, float GivenRadius) : Center(GivenCenter), Radius(GivenRadius) {}
    bool operator == (const A2DCircle &OtherCircle) const;
    bool IsIntersect (const A2DCircle &A2DCircle) const;
    bool IsIntersect (const A2DRectangle &A2DRectangle) const;
    bool IsIn (const A2DRectangle &A2DRectangle) const;
};

class A2DRectangle {
public:
    A2DPoint Center;
    A2DVector HalfExtent;
    inline A2DRectangle () : Center(0.0f, 0.0f), HalfExtent(1.0f, 1.0f) {}
    inline A2DRectangle (const A2DPoint &GivenCenter, const A2DVector &GivenHalfExtent) : Center(GivenCenter), HalfExtent(GivenHalfExtent) {}
    A2DPoint GetMaxPosition () const;
    A2DPoint GetMinPosition () const;
};
