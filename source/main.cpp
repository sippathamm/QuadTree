#include <iostream>
#include <random>

#include "QuadTree.h"

#define TIME_BEGIN  TimeBegin = std::chrono::steady_clock::now();
#define TIME_END    TimeEnd = std::chrono::steady_clock::now();
#define GET_TIME    std::chrono::duration_cast<std::chrono::microseconds>(TimeEnd - TimeBegin).count()

std::chrono::steady_clock::time_point TimeBegin;
std::chrono::steady_clock::time_point TimeEnd;

int main() {
    // Initialize an array of 2D particles
    const int N = 5000;
    const float Radius = 1.0f;
    std::vector<A2DParticle> ParticleArray(N);

    // Define lower bound and upper bound
    A2DPoint LowerBound = A2DPoint (-1000.0f, -1000.0f);
    A2DPoint UpperBound = A2DPoint (1000.0f, 1000.0f);

    std::random_device Engine;
    std::uniform_real_distribution<float> RandomDistribution(0.0f, 1.0f);

    // Generate particle position
    for (int i = 0; i < N; i++)
    {
        float X = LowerBound.X + RandomDistribution(Engine) * (UpperBound.X - LowerBound.X);
        float Y = LowerBound.Y + RandomDistribution(Engine) * (UpperBound.Y - LowerBound.Y);

        A2DPoint Center = A2DPoint (X, Y);
        ParticleArray[i] = A2DParticle (Center, Radius);
    }
    
    // Initialize QuadTree
    A2DPoint Center = A2DPoint (0.0f, 0.0f);
    A2DVector HalfExtent = A2DVector (1000.0f, 1000.0f);

    A2DRectangle Boundary(Center, HalfExtent);
    AQuadTree AQuadTree(Boundary);
    
    // Insert particles in QuadTree
    for (auto & Particle : ParticleArray)
    {
        AQuadTree.Insert(Particle);
    }
    
    int CollisionCount = 0;
    
    TIME_BEGIN
    for (const auto &CurrentParticle : ParticleArray)
    {
        // Define a range to query
        A2DCircle Range = A2DCircle (CurrentParticle.Center, CurrentParticle.Radius * 2.0f);

        // Query the given range in QuadTree
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

    std::cout << "QuadTree collision count: " << CollisionCount << std::endl;
    std::cout << "QuadTree time taken: " << GET_TIME << "[µs]" << std::endl;

    CollisionCount = 0;

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

    std::cout << "Bruteforce collision count: " << CollisionCount << std::endl;
    std::cout << "Bruteforce time taken: " << GET_TIME << "[µs]" << std::endl;

    return 0;
}
