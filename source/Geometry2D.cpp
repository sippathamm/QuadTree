#include <cmath>

#include "Geometry2D.h"

#define CLAMP(A, MIN, MAX) A = (A < MIN) ? MIN : (A > MAX) ? MAX : A
#define IS_OVERLAP(MIN_A, MAX_A, MIN_B, MAX_B) (MIN_B <= MAX_A) && (MIN_A <= MAX_B)

A2DPoint A2DPoint::operator + (const A2DPoint &OtherPoint) const {
    return {X + OtherPoint.X, Y + OtherPoint.Y};
}
A2DPoint A2DPoint::operator - (const A2DPoint &OtherPoint) const {
    return {X - OtherPoint.X, Y - OtherPoint.Y};
}

bool A2DPoint::operator == (const A2DPoint &OtherPoint) const {
    return this->X == OtherPoint.X && this->Y == OtherPoint.Y;
}

A2DVector A2DVector::operator * (float Constant) const {
    return {X * Constant, Y * Constant};
}

float A2DVector::operator * (const A2DVector &OtherVector) const {
    return this->X * OtherVector.X + this->Y * OtherVector.Y;
}

float A2DVector::Magnitude () const {
    return sqrtf((*this) * (*this));
}

float A2DVector::MagnitudeSquare() const {
    return (*this) * (*this);
}

float A2DLine::Length() const {
    A2DPoint Distance = this->End - this->Begin;
    return A2DVector(Distance).Magnitude();
}

float A2DLine::LengthSquare() const {
    A2DPoint Distance = this->End - this->Begin;
    return A2DVector(Distance.X, Distance.Y).MagnitudeSquare();
}

bool A2DCircle::operator == (const A2DCircle &OtherCircle) const {
    return this->Center == OtherCircle.Center && this->Radius == OtherCircle.Radius;
}

bool A2DCircle::IsIntersect (const A2DCircle &A2DCircle) const {
    A2DLine Distance = {this->Center, A2DCircle.Center};
    float RadiiSum = this->Radius + A2DCircle.Radius;
    return Distance.LengthSquare() <= RadiiSum * RadiiSum;
}

bool A2DCircle::IsIntersect (const A2DRectangle &A2DRectangle) const {
    A2DPoint ClosestPoint = this->Center;
    A2DPoint MaxPosition = A2DRectangle.GetMaxPosition();
    A2DPoint MinPosition = A2DRectangle.GetMinPosition();
    CLAMP(ClosestPoint.X, MinPosition.X, MaxPosition.X);
    CLAMP(ClosestPoint.Y, MinPosition.Y, MaxPosition.Y);
    A2DLine Distance = {this->Center, ClosestPoint};
    return Distance.LengthSquare() <= this->Radius * this->Radius;
}

bool A2DCircle::IsIn (const A2DRectangle &A2DRectangle) const {
    A2DPoint Center = this->Center;
    A2DPoint MaxPosition = A2DRectangle.GetMaxPosition();
    A2DPoint MinPosition = A2DRectangle.GetMinPosition();
    return Center.X >= MinPosition.X && Center.X <= MaxPosition.X && Center.Y >= MinPosition.Y && Center.Y <= MaxPosition.Y;
}

A2DPoint A2DRectangle::GetMaxPosition () const {
    A2DPoint PositionA = this->Center;
    A2DPoint PositionB = PositionA + this->HalfExtent;
    return {fmaxf(PositionA.X, PositionB.X), fmaxf(PositionA.Y, PositionB.Y)};
}

A2DPoint A2DRectangle::GetMinPosition () const {
    A2DPoint PositionA = this->Center;
    A2DPoint PositionB = PositionA - this->HalfExtent;
    return {fminf(PositionA.X, PositionB.X), fminf(PositionA.Y, PositionB.Y)};
}

