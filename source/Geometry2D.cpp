#include <cmath>

#include "Geometry2D.h"

#define CLAMP(A, MIN, MAX) A = (A < MIN) ? MIN : (A > MAX) ? MAX : A

A2DPoint A2DPoint::operator + (const A2DPoint &Point) const
{
    return {this->X + Point.X, this->Y + Point.Y};
}

A2DPoint A2DPoint::operator - (const A2DPoint &Point) const
{
    return {this->X - Point.X, this->Y - Point.Y};
}

A2DPoint A2DPoint::operator * (float Constant) const
{
    return {this->X * Constant, this->Y * Constant};
}

float A2DPoint::operator * (const A2DPoint &Point) const
{
    return this->X * Point.X + this->Y * Point.Y;
}

bool A2DPoint::operator == (const A2DPoint &Point) const
{
    return this->X == Point.X && this->Y == Point.Y;
}

bool A2DPoint::operator != (const A2DPoint &Point) const
{
    return !(*this == Point);
}

A2DVector A2DVector::operator * (float Constant) const
{
    return {this->X * Constant, this->Y * Constant};
}

float A2DVector::operator * (const A2DVector &Vector) const
{
    return this->X * Vector.X + this->Y * Vector.Y;
}

float A2DVector::Magnitude () const
{
    return sqrtf((*this) * (*this));
}

float A2DVector::MagnitudeSquared () const
{
    return (*this) * (*this);
}

float A2DLine::Length () const
{
    A2DPoint Distance = this->End - this->Begin;
    auto DistanceVector = A2DVector (Distance);
    
    return DistanceVector.Magnitude();
}

float A2DLine::LengthSquared () const
{
    A2DPoint Distance = this->End - this->Begin;
    auto DistanceVector = A2DVector (Distance);
    
    return DistanceVector.MagnitudeSquared();
}

bool A2DCircle::operator == (const A2DCircle &Circle) const
{
    return this->Center == Circle.Center && this->Radius == Circle.Radius;
}

bool A2DCircle::IsBeingIntersect (const A2DCircle &Circle) const
{
    A2DLine Distance = A2DLine (this->Center, Circle.Center);
    float RadiiSum = this->Radius + Circle.Radius;
    
    return Distance.LengthSquared() <= RadiiSum * RadiiSum;
}

bool A2DCircle::IsBeingIntersect (const A2DRectangle &Rectangle) const
{
    A2DPoint ClosestPoint = this->Center;
    A2DPoint UpperBound = Rectangle.GetUpperBound();
    A2DPoint LowerBound = Rectangle.GetLowerBound();

    CLAMP(ClosestPoint.X, LowerBound.X, UpperBound.X);
    CLAMP(ClosestPoint.Y, LowerBound.Y, UpperBound.Y);

    A2DLine Distance = {this->Center, ClosestPoint};

    return Distance.LengthSquared() <= this->Radius * this->Radius;
}

bool A2DCircle::IsIn (const A2DRectangle &Rectangle) const
{
    A2DPoint UpperBound = Rectangle.GetUpperBound();
    A2DPoint LowerBound = Rectangle.GetLowerBound();

    return this->Center.X >= LowerBound.X && this->Center.X <= UpperBound.X &&
           this->Center.Y >= LowerBound.Y && this->Center.Y <= UpperBound.Y;
}

A2DPoint A2DRectangle::GetUpperBound () const
{
    A2DPoint PositionA = this->Center;
    A2DPoint PositionB = PositionA + this->HalfExtent;

    return {fmaxf(PositionA.X, PositionB.X), fmaxf(PositionA.Y, PositionB.Y)};
}

A2DPoint A2DRectangle::GetLowerBound () const
{
    A2DPoint PositionA = this->Center;
    A2DPoint PositionB = PositionA - this->HalfExtent;

    return {fminf(PositionA.X, PositionB.X), fminf(PositionA.Y, PositionB.Y)};
}
