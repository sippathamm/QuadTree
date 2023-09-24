#include <iostream>
#include <cmath>

#include "QuadTree.h"

#define TIME_BEGIN  TimeBegin = std::chrono::steady_clock::now();
#define TIME_END    TimeEnd = std::chrono::steady_clock::now();

std::chrono::steady_clock::time_point TimeBegin;
std::chrono::steady_clock::time_point TimeEnd;

int main() {
    const int N = 5000;
    const float Radius = 1.0f;
    std::vector<A2DParticle> ParticleArray(N);
    srand(static_cast<unsigned>(time(0)));
    
    for (int i = 0; i < N; i++) {
        float X = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1000.0f)) * pow(-1, rand());
        float Y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1000.0f)) * pow(-1, rand());
        A2DPoint Center = {X, Y};
        ParticleArray[i] = {Center, Radius};
    }
    
    A2DRectangle Boundary({0.0f, 0.0f}, {1000.0f, 1000.0f});
    AQuadTree AQuadTree(Boundary);
    
    for (auto & Each : ParticleArray) {
        AQuadTree.Insert(Each);
    }
    
    int CollisionCount = 0;
    
    TIME_BEGIN
    for (int i = 0; i < N; i++) {
        A2DParticle CurrentParticle = ParticleArray[i];
        A2DCircle Range = {CurrentParticle.Center, CurrentParticle.Radius * 2};
        std::vector<A2DParticle*> ParticleInRange = AQuadTree.Query(Range);
        for (int j = 0; j < (int)ParticleInRange.size(); j++) {
            A2DParticle *OtherParticle = ParticleInRange[j];
            if (CurrentParticle == *OtherParticle) {
                continue;
            }
            if (CurrentParticle.IsIntersect(*OtherParticle)) {
                CollisionCount++;
            }
        }
    }
    TIME_END

    std::cout << "QuadTree collision count: " << CollisionCount << std::endl;
    std::cout << "QuadTree time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(TimeEnd - TimeBegin).count() << "[µs]" << std::endl;

    CollisionCount = 0;

    TIME_BEGIN
    for (int i = 0; i < N; i++)
    {
        A2DParticle CurrentParticle = ParticleArray[i];
        for (int j = 0; j < N; j++)
        {
            A2DParticle OtherParticle = ParticleArray[j];
            if (CurrentParticle == OtherParticle)
            {
                continue;
            }
            if (CurrentParticle.IsIntersect(OtherParticle))
            {
                CollisionCount++;
            }
        }
    }
    TIME_END

    std::cout << "Bruteforce collision count: " << CollisionCount << std::endl;
    std::cout << "Bruteforce time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(TimeEnd - TimeBegin).count() << "[µs]" << std::endl;

    return 0;
}
