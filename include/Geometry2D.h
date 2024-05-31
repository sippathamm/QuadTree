#pragma once

/**
 * @brief Macro to clamp a value between a minimum and maximum value.
 * @param A The value to clamp.
 * @param MIN The minimum value.
 * @param MAX The maximum value.
 */
#define CLAMP(A, MIN, MAX) A = (A < MIN) ? MIN : (A > MAX) ? MAX : A

/**
 * @brief A class representing a point in 2D space with floating-point coordinates.
 */
class A2DPoint
{
public:
    float X; /**< The X-coordinate of the point. */
    float Y; /**< The Y-coordinate of the point. */

    /**
     * @brief Default constructor. Initializes point to origin (0, 0).
     */
    inline A2DPoint () : X(0.0f), Y(0.0f) {}

    /**
     * @brief Parameterized constructor.
     * @param X The X-coordinate of the point.
     * @param Y The Y-coordinate of the point.
     */
    inline A2DPoint (float X, float Y) : X(X), Y(Y) {}

    /**
     * @brief Default destructor.
     */
    ~A2DPoint () = default;

    /**
     * @brief Overloaded addition operator for adding two points.
     * @param Point The point to add.
     * @return The result of the addition.
     */
    A2DPoint operator + (const A2DPoint &Point) const
    {
        return {this->X + Point.X, this->Y + Point.Y};
    }

    /**
     * @brief Overloaded addition operator for adding a scalar value to the point.
     * @param Scalar The scalar value to add.
     * @return The result of the addition.
     */
    A2DPoint operator + (float Scalar) const
    {
        return {this->X + Scalar, this->Y + Scalar};
    }

    /**
     * @brief Overloaded subtraction operator for subtracting two points.
     * @param Point The point to subtract.
     * @return The result of the subtraction.
     */
    A2DPoint operator - (const A2DPoint &Point) const
    {
        return {this->X - Point.X, this->Y - Point.Y};
    }

    /**
     * @brief Overloaded subtraction operator for subtracting a scalar value from the point.
     * @param Scalar The scalar value to subtract.
     * @return The result of the subtraction.
     */
    A2DPoint operator - (float Scalar) const
    {
        return {this->X - Scalar, this->Y - Scalar};
    }

    /**
     * @brief Overloaded multiplication operator for multiplying two points.
     * @param Point The point to multiply.
     * @return The result of the multiplication.
     */
    A2DPoint operator * (const A2DPoint &Point) const
    {
        return {this->X * Point.X, this->Y * Point.Y};
    }

    /**
     * @brief Overloaded multiplication operator for multiplying the point by a scalar value.
     * @param Scalar The scalar value to multiply.
     * @return The result of the multiplication.
     */
    A2DPoint operator * (float Scalar) const
    {
        return {this->X * Scalar, this->Y * Scalar};
    }

    /**
     * @brief Overloaded division operator for dividing two points.
     * @param Point The point to divide.
     * @return The result of the division.
     */
    A2DPoint operator / (const A2DPoint &Point) const
    {
        return {this->X / Point.X, this->Y / Point.Y};
    }

    /**
     * @brief Overloaded division operator for dividing the point by a scalar value.
     * @param Scalar The scalar value to divide by.
     * @return The result of the division.
     */
    A2DPoint operator / (float Scalar) const
    {
        return {this->X / Scalar, this->Y / Scalar};
    }

    /**
     * @brief Overloaded less than operator to compare if the point is less than another point.
     * @param Point The point to compare.
     * @return True if both X and Y coordinates of this point are less than the corresponding coordinates of the other point, false otherwise.
     */
    bool operator < (const A2DPoint &Point) const
    {
        return this->X < Point.X && this->Y < Point.Y;
    }

    /**
     * @brief Overloaded greater than operator to compare if the point is greater than another point.
     * @param Point The point to compare.
     * @return True if both X and Y coordinates of this point are greater than the corresponding coordinates of the other point, false otherwise.
     */
    bool operator > (const A2DPoint &Point) const
    {
        return this->X > Point.X && this->Y > Point.Y;
    }

    /**
     * @brief Overloaded equality operator to compare if two points are equal.
     * @param Point The point to compare.
     * @return True if both X and Y coordinates of this point are equal to the corresponding coordinates of the other point, false otherwise.
     */
    bool operator == (const A2DPoint &Point) const
    {
        return this->X == Point.X && this-> Y == Point.Y;
    }

    /**
     * @brief Overloaded inequality operator to compare if two points are not equal.
     * @param Point The point to compare.
     * @return True if the points are not equal, false otherwise.
     */
    bool operator != (const A2DPoint &Point) const
    {
        return !(*this == Point);
    }
};

/**
 * @brief A class representing a 2D vector with floating-point coordinates.
 *
 * Inherits functionality from A2DPoint.
 */
class A2DVector : public A2DPoint
{
public:
    /**
     * @brief Default constructor. Initializes vector to zero vector.
     */
    inline A2DVector () : A2DPoint() {}

    /**
     * @brief Parameterized constructor.
     * @param X The X-component of the vector.
     * @param Y The Y-component of the vector.
     */
    inline A2DVector (float X, float Y) : A2DPoint(X, Y) {}

    /**
     * @brief Constructor from A2DPoint.
     * @param Point The A2DPoint to convert to a vector.
     */
    inline A2DVector (const A2DPoint &Point) : A2DPoint(Point.X, Point.Y) {}

    /**
     * @brief Default destructor.
     */
    ~A2DVector () = default;

    /**
     * @brief Calculate the dot product of this vector with another vector.
     * @param Vector The other vector.
     * @return The dot product of the two vectors.
     */
    float Dot (const A2DVector &Vector) const
    {
        return this->X * Vector.X + this->Y * Vector.Y;
    }

    /**
     * @brief Calculate the magnitude of the vector.
     * @return The magnitude of the vector.
     */
    float GetMagnitude () const
    {
        return sqrtf(this->Dot(*this));
    }

    /**
     * @brief Calculate the squared magnitude of the vector.
     * @return The squared magnitude of the vector.
     */
    float GetMagnitudeSquared () const
    {
        return this->Dot(*this);
    }
};

/**
 * @brief A class representing a line segment in 2D space.
 */
class A2DLine
{
public:
    A2DPoint Begin; /**< The starting point of the line segment. */
    A2DPoint End; /**< The ending point of the line segment. */

    /**
     * @brief Default constructor. Initializes the line segment from (0, 0) to (0, 1).
     */
    inline A2DLine () : Begin(0.0f, 0.0f), End(0.0f, 1.0f) {}

    /**
     * @brief Parameterized constructor.
     * @param Begin The starting point of the line segment.
     * @param End The ending point of the line segment.
     */
    inline A2DLine (const A2DPoint &Begin, const A2DPoint &End) : Begin(Begin), End(End) {}

    /**
     * @brief Default destructor.
     */
    ~A2DLine () = default;

    /**
     * @brief Overloaded less than operator to compare line segments based on their lengths.
     * @param Line The line segment to compare.
     * @return True if the length of this line segment is less than the length of the other line segment, false otherwise.
     */
    bool operator < (const A2DLine &Line) const
    {
        return this->GetLength() < Line.GetLength();
    }

    /**
     * @brief Overloaded greater than operator to compare line segments based on their lengths.
     * @param Line The line segment to compare.
     * @return True if the length of this line segment is greater than the length of the other line segment, false otherwise.
     */
    bool operator > (const A2DLine &Line) const
    {
        return this->GetLength() > Line.GetLength();
    }

    /**
     * @brief Overloaded equality operator to compare line segments based on their lengths.
     * @param Line The line segment to compare.
     * @return True if the length of this line segment is equal to the length of the other line segment, false otherwise.
     */
    bool operator == (const A2DLine &Line) const
    {
        return this->GetLength() == Line.GetLength();
    }

    /**
     * @brief Overloaded inequality operator to compare line segments based on their lengths.
     * @param Line The line segment to compare.
     * @return True if the length of this line segment is not equal to the length of the other line segment, false otherwise.
     */
    bool operator != (const A2DLine &Line) const
    {
        return !(*this == Line);
    }

    /**
     * @brief Calculate the length of the line segment.
     * @return The length of the line segment.
     */
    float GetLength () const
    {
        A2DPoint Distance = this->End - this->Begin;
        return A2DVector(Distance).GetMagnitude();
    }

    /**
     * @brief Calculate the squared length of the line segment.
     * @return The squared length of the line segment.
     */
    float GetLengthSquared () const
    {
        A2DPoint Distance = this->End - this->Begin;
        return A2DVector(Distance).GetMagnitudeSquared();
    }
};

/**
 * @brief A class representing a rectangle in 2D space.
 *
 */
 /*
  * ---------------------------------------- ^
  * | top-left                   top-right | |
  * |                                      | | Half extent along y-axis
  * |                                      | |
  * |                Center                | v
  * |                                      |
  * |                                      |
  * | bottom-left             bottom-right |
  * ----------------------------------------
  *                     <------------------>
  *                     Half extent along x-axis.
  */
class A2DRectangle
{
public:
    A2DPoint Center; /**< The center point of the rectangle. */
    A2DVector HalfExtent; /**< The half extent of the rectangle along each axis. */

    /**
     * @brief Default constructor. Initializes the rectangle with center at (0,0) and half extent (1,1).
     */
    inline A2DRectangle () : Center(0.0f, 0.0f), HalfExtent(1.0f, 1.0f) {}

    /**
     * @brief Parameterized constructor.
     * @param Center The center point of the rectangle.
     * @param HalfExtent The half extent of the rectangle along each axis.
     */
    inline A2DRectangle (const A2DPoint &Center, const A2DVector &HalfExtent) : Center(Center), HalfExtent(HalfExtent) {}

    /**
     * @brief Default destructor.
     */
    ~A2DRectangle () = default;

    /**
     * @brief Calculate the upper bound (top-right corner) of the rectangle.
     * @return The upper bound of the rectangle.
     */
    A2DPoint GetUpperBound () const
    {
        A2DPoint Center = this->Center;
        A2DPoint TopRight = Center + this->HalfExtent;

        return {fmaxf(Center.X, TopRight.X), fmaxf(Center.Y, TopRight.Y)};
    }

    /**
     * @brief Calculate the lower bound (bottom-left corner) of the rectangle.
     * @return The lower bound of the rectangle.
     */
    A2DPoint GetLowerBound () const
    {
        A2DPoint Center = this->Center;
        A2DPoint BottomLeft = Center - this->HalfExtent;

        return {fminf(Center.X, BottomLeft.X), fminf(Center.Y, BottomLeft.Y)};
    }
};

/**
 * @brief A class representing a circle in 2D space.
 */
class A2DCircle
{
public:
    A2DPoint Center; /**< The center point of the circle. */
    float Radius; /**< The radius of the circle. */

    /**
     * @brief Default constructor. Initializes the circle with center at (0,0) and radius 1.
     */
    inline A2DCircle () : Center(0.0f, 0.0f), Radius(1.0f) {}

    /**
     * @brief Parameterized constructor.
     * @param Center The center point of the circle.
     * @param Radius The radius of the circle.
     */
    inline A2DCircle (const A2DPoint &Center, float Radius) : Center(Center), Radius(Radius) {}

    /**
     * @brief Default destructor.
     */
    ~A2DCircle () = default;

    /**
     * @brief Overloaded equality operator to check if two circles are equal.
     * @param Circle The circle to compare.
     * @return True if both circles have the same center and radius, false otherwise.
     */
    bool operator == (const A2DCircle &Circle) const
    {
        return this->Center == Circle.Center && this->Radius == Circle.Radius;
    }

    /**
     * @brief Overloaded inequality operator to check if two circles are not equal.
     * @param Circle The circle to compare.
     * @return True if the circles have different centers or radii, false otherwise.
     */
    bool operator != (const A2DCircle &Circle) const
    {
        return !(*this == Circle);
    }

    /**
     * @brief Checks if this circle is intersecting with another circle.
     * @param Circle The circle to check intersection with.
     * @return True if the circles intersect, false otherwise.
     */
    bool IsBeingIntersect (const A2DCircle &Circle) const
    {
        A2DLine Radius = A2DLine(this->Center, Circle.Center);
        float RadiiSum = this->Radius + Circle.Radius;

        return Radius.GetLengthSquared() <= RadiiSum * RadiiSum;
    }

    /**
     * @brief Checks if this circle is intersecting with a rectangle.
     * @param Rectangle The rectangle to check intersection with.
     * @return True if the circle intersects with the rectangle, false otherwise.
     */
    bool IsBeingIntersect (const A2DRectangle &Rectangle) const
    {
        A2DPoint ClosestPoint = this->Center;
        A2DPoint UpperBound = Rectangle.GetUpperBound();
        A2DPoint LowerBound = Rectangle.GetLowerBound();

        CLAMP(ClosestPoint.X, LowerBound.X, UpperBound.X);
        CLAMP(ClosestPoint.Y, LowerBound.Y, UpperBound.Y);

        A2DLine Distance = {this->Center, ClosestPoint};

        return Distance.GetLengthSquared() <= this->Radius * this->Radius;
    }

    /**
     * @brief Checks if this circle is completely contained within a rectangle.
     * @param Rectangle The rectangle to check containment within.
     * @return True if the circle is completely contained within the rectangle, false otherwise.
     */
    bool IsIn (const A2DRectangle &Rectangle) const
    {
        A2DPoint UpperBound = Rectangle.GetUpperBound();
        A2DPoint LowerBound = Rectangle.GetLowerBound();

        return this->Center.X >= LowerBound.X && this->Center.X <= UpperBound.X &&
               this->Center.Y >= LowerBound.Y && this->Center.Y <= UpperBound.Y;
    }
};

/**
 * @brief Typedef A2DCircle as A2DParticle
 */
typedef A2DCircle A2DParticle;
