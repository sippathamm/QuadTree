#pragma once

#include <vector>
#include "Geometry2D.h"

class QuadTree {
protected:
    int CurrentDepth;
    static int MaxDepth;
    static int MaxCapacity;
    Rectangle Boundary;
    std::vector<Particle*> Contain;
    std::vector<QuadTree> Children;
public:
    inline explicit QuadTree (const Rectangle &GivenBoundary) : Boundary(GivenBoundary), CurrentDepth(0) {}
    bool IsLeaf ();
    void Insert (Particle &Particle);
    void Subdivide ();
    void Search (const Circle &Range, std::vector<Particle*> &ParticleInRange);
    std::vector<Particle*> Query (const Circle &Range);
};
