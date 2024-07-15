#include <iostream>
#include <random>
#include <chrono>
#include "QuadTree2D.h"

// Define macros for measuring time
#define TIME_BEGIN  TimeBegin = std::chrono::steady_clock::now();
#define TIME_END    TimeEnd = std::chrono::steady_clock::now();
#define GET_TIME    std::chrono::duration_cast<std::chrono::microseconds>(TimeEnd - TimeBegin).count()

// Define time measurement variables
std::chrono::steady_clock::time_point TimeBegin;
std::chrono::steady_clock::time_point TimeEnd;

int main() {
    // Constants for particle generation
    const int N = 5000;
    const float Radius = 1.0f;

    // Create an array to hold particles
    std::vector<A2DParticle> ParticleArray(N);

    // Define the bounds of the 2D space
    A2DPoint LowerBound = A2DPoint(-1000.0f, -1000.0f);
    A2DPoint UpperBound = A2DPoint(1000.0f, 1000.0f);

    std::random_device Engine;
    std::uniform_real_distribution<float> RandomDistribution(0.0f, 1.0f);

    // Generate random particles within the bounds
    for (int i = 0; i < N; i++)
    {
        float X = LowerBound.X + RandomDistribution(Engine) * (UpperBound.X - LowerBound.X);
        float Y = LowerBound.Y + RandomDistribution(Engine) * (UpperBound.Y - LowerBound.Y);

        A2DPoint Center = A2DPoint(X, Y);
        ParticleArray[i] = A2DParticle(Center, Radius);
    }

    // Define the boundary of the quadtree
    A2DPoint Center = A2DPoint(0.0f, 0.0f);
    A2DVector HalfExtent = A2DVector(1000.0f, 1000.0f);
    A2DRectangle Boundary(Center, HalfExtent);

    // Create a quadtree with the defined boundary
    AQuadTree AQuadTree(Boundary);

    // Insert particles into the quadtree
    for (auto & Particle : ParticleArray)
    {
        AQuadTree.Insert(Particle);
    }

    int CollisionCount = 0;

    // Brute force collision detection
    TIME_BEGIN
    for (const auto &CurrentParticle : ParticleArray)
    {
        for (const auto &AnotherParticle : ParticleArray)
        {
            if (CurrentParticle == AnotherParticle)
            {
                continue;
            }

            if (CurrentParticle.IsBeingIntersect(AnotherParticle))
            {
                CollisionCount++;
            }
        }
    }
    TIME_END

    std::cout << "------------ Brute force ------------" << std::endl;
    std::cout << "Count: " << CollisionCount << std::endl;
    std::cout << "Time taken: " << GET_TIME << "[µs]" << std::endl;

    CollisionCount = 0;

    // Quadtree collision detection
    TIME_BEGIN
    for (const auto &CurrentParticle : ParticleArray)
    {
        A2DCircle Range = A2DCircle(CurrentParticle.Center, CurrentParticle.Radius * 2.0f);

        auto ParticleInRange = AQuadTree.Query(Range);

        for (const auto &AnotherParticle : ParticleInRange)
        {
            if (CurrentParticle == *AnotherParticle)
            {
                continue;
            }

            if (CurrentParticle.IsBeingIntersect(*AnotherParticle))
            {
                CollisionCount++;
            }
        }
    }
    TIME_END

    std::cout << "------------ Quad tree ------------" << std::endl;
    std::cout << "Count: " << CollisionCount << std::endl;
    std::cout << "Time taken: " << GET_TIME << "[µs]" << std::endl;

    return 0;
}
