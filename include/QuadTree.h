#pragma once

#include <vector>

#include "Geometry2D.h"

class AQuadTree {
protected:
    int CurrentDepth;
    static int MaxDepth;
    static int MaxCapacity;
    A2DRectangle Boundary;
    std::vector<A2DParticle*> Contain;
    std::vector<AQuadTree> Children;
public:
    inline explicit AQuadTree (const A2DRectangle &GivenBoundary) : Boundary(GivenBoundary), CurrentDepth(0) {}
    bool IsLeaf ();
    void Insert (A2DParticle &Particle);
    void Subdivide ();
    void Search (const A2DCircle &Range, std::vector<A2DParticle*> &ParticleInRange);
    std::vector<A2DParticle*> Query (const A2DCircle &Range);
};
