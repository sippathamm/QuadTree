#include <cmath>
#include "../include/Geometry2D.h"

#define CLAMP(A, MIN, MAX) A = (A < MIN) ? MIN : (A > MAX) ? MAX : A
#define IS_OVERLAP(MIN_A, MAX_A, MIN_B, MAX_B) (MIN_B <= MAX_A) && (MIN_A <= MAX_B)

Point Point::operator + (const Point &OtherPoint) const {
    return {X + OtherPoint.X, Y + OtherPoint.Y};
}
Point Point::operator - (const Point &OtherPoint) const {
    return {X - OtherPoint.X, Y - OtherPoint.Y};
}

bool Point::operator == (const Point &OtherPoint) const {
    return this->X == OtherPoint.X && this->Y == OtherPoint.Y;
}

Vector Vector::operator * (float Constant) const {
    return {X * Constant, Y * Constant};
}

float Vector::operator * (const Vector &OtherVector) const {
    return this->X * OtherVector.X + this->Y * OtherVector.Y;
}

float Vector::Magnitude () {
    return sqrtf((*this) * (*this));
}

float Vector::MagnitudeSquare() {
    return (*this) * (*this);
}

float Line::Length() {
    Point Distance = this->End - this->Start;
    return Vector(Distance).Magnitude();
}

float Line::LengthSquare() {
    Point Distance = this->End - this->Start;
    return Vector(Distance.X, Distance.Y).MagnitudeSquare();
}

bool Circle::operator == (const Circle &OtherCircle) const {
    return this->Center == OtherCircle.Center && this->Radius == OtherCircle.Radius;
}

bool Circle::IsIntersect (const Circle &Circle) const {
    Line Distance = {this->Center, Circle.Center};
    float RadiiSum = this->Radius + Circle.Radius;
    return Distance.LengthSquare() <= RadiiSum * RadiiSum;
}

bool Circle::IsIntersect (const Rectangle &Rectangle) const {
    Point ClosestPoint = this->Center;
    Point MaxPosition = Rectangle.GetMaxPosition();
    Point MinPosition = Rectangle.GetMinPosition();
    CLAMP(ClosestPoint.X, MinPosition.X, MaxPosition.X);
    CLAMP(ClosestPoint.Y, MinPosition.Y, MaxPosition.Y);
    Line Distance = {this->Center, ClosestPoint};
    return Distance.LengthSquare() <= this->Radius * this->Radius;
}

bool Circle::IsIn (const Rectangle &Rectangle) const {
    Point Center = this->Center;
    Point MaxPosition = Rectangle.GetMaxPosition();
    Point MinPosition = Rectangle.GetMinPosition();
    return Center.X >= MinPosition.X && Center.X <= MaxPosition.X && Center.Y >= MinPosition.Y && Center.Y <= MaxPosition.Y;
}

Point Rectangle::GetMaxPosition () const {
    Point PositionA = this->Center;
    Point PositionB = PositionA + this->HalfExtent;
    return {fmaxf(PositionA.X, PositionB.X), fmaxf(PositionA.Y, PositionB.Y)};
}

Point Rectangle::GetMinPosition () const {
    Point PositionA = this->Center;
    Point PositionB = PositionA - this->HalfExtent;
    return {fminf(PositionA.X, PositionB.X), fminf(PositionA.Y, PositionB.Y)};
}

