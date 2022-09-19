#include <iostream>
#include <cmath>
#include <queue>
#include "../include/QuadTree.h"

#define SIZE(a) (int)a.size()

int QuadTree::MaxDepth = 5;
int QuadTree::MaxCapacity = 15;

bool QuadTree::IsLeaf() {
    return Children.empty();
}

void QuadTree::Insert(Particle &Particle) {
    if (!Particle.IsIn(Boundary)) {
        return;
    }
    if (this->IsLeaf() && SIZE(this->Contain) + 1 > MaxCapacity) {
        Subdivide();
    }
    if (this->IsLeaf()) {
        Contain.push_back(&Particle);
    } else {
        for (auto & Each : this->Children) {
            Each.Insert(Particle);
        }
    }
}

void QuadTree::Subdivide() {
    if (CurrentDepth + 1 >= MaxDepth) {
        return;
    }
    Point Center = Boundary.Center;
    Vector HalfExtent = Boundary.HalfExtent * 0.5f;
    Rectangle SubdivideRegion [] = {
        Rectangle({Center.X + HalfExtent.X, Center.Y + HalfExtent.Y}, HalfExtent),
        Rectangle({Center.X - HalfExtent.X, Center.Y + HalfExtent.Y}, HalfExtent),
        Rectangle({Center.X + HalfExtent.X, Center.Y - HalfExtent.Y}, HalfExtent),
        Rectangle({Center.X - HalfExtent.X, Center.Y - HalfExtent.Y}, HalfExtent),
    };
    for (int Index = 0; Index < 4; ++Index) {
        this->Children.emplace_back(SubdivideRegion[Index]);
        this->Children[Index].CurrentDepth++;
    }
    for (auto & Each : this->Contain) {
        this->Children[0].Insert(*Each);
        this->Children[1].Insert(*Each);
        this->Children[2].Insert(*Each);
        this->Children[3].Insert(*Each);
    }
    Contain.clear();
}

void QuadTree::Search (const Circle &Range, std::vector<Particle*> &ParticleInRange) {
    if (!Range.IsIntersect(this->Boundary)) {
        return;
    }
    if (this->IsLeaf()) {
        for (auto & Each : this->Contain) {
            if (Each->IsIntersect(Range)) {
                ParticleInRange.push_back(Each);
            }
        }
    } else {
        for (auto & Each : this->Children) {
            Each.Search(Range, ParticleInRange);
        }
    }
}

std::vector<Particle*> QuadTree::Query (const Circle &Range) {
    std::vector<Particle*> ParticleInRange;
    this->Search(Range, ParticleInRange);
    return ParticleInRange;
}
