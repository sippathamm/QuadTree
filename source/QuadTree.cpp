#include <queue>

#include "QuadTree.h"

#define SIZE(a) (int)a.size()

int AQuadTree::MaxDepth = 5;
int AQuadTree::MaxCapacity = 15;

bool AQuadTree::IsLeaf ()
{
    return Children.empty();
}

void AQuadTree::Insert (A2DParticle &A2DParticle)
{
    if (!A2DParticle.IsIn(Boundary))
    {
        return;
    }

    if (this->IsLeaf() && SIZE(this->Contain) + 1 > MaxCapacity)
    {
        Subdivide();
    }

    if (this->IsLeaf())
    {
        Contain.push_back(&A2DParticle);
    }
    else
    {
        for (auto & Child : this->Children)
        {
            Child.Insert(A2DParticle);
        }
    }
}

void AQuadTree::Subdivide()
{
    if (CurrentDepth + 1 >= MaxDepth)
    {
        return;
    }

    A2DPoint Center = Boundary.Center;
    A2DVector HalfExtent = Boundary.HalfExtent * 0.5f;

    A2DRectangle SubdivideRegion [] =
    {
        A2DRectangle({Center.X + HalfExtent.X, Center.Y + HalfExtent.Y}, HalfExtent),
        A2DRectangle({Center.X - HalfExtent.X, Center.Y + HalfExtent.Y}, HalfExtent),
        A2DRectangle({Center.X + HalfExtent.X, Center.Y - HalfExtent.Y}, HalfExtent),
        A2DRectangle({Center.X - HalfExtent.X, Center.Y - HalfExtent.Y}, HalfExtent),
    };

    for (int Index = 0; Index < 4; Index++)
    {
        this->Children.emplace_back(SubdivideRegion[Index]);
        this->Children[Index].CurrentDepth++;
    }

    for (const auto & Each : this->Contain)
    {
        this->Children[0].Insert(*Each);
        this->Children[1].Insert(*Each);
        this->Children[2].Insert(*Each);
        this->Children[3].Insert(*Each);
    }

    Contain.clear();
}

void AQuadTree::Search (const A2DCircle &Range, std::vector<A2DParticle*> &ParticleInRange)
{
    if (!Range.IsBeingIntersect(this->Boundary))
    {
        return;
    }

    if (this->IsLeaf())
    {
        for (const auto & Each : this->Contain)
        {
            if (Each->IsBeingIntersect(Range))
            {
                ParticleInRange.push_back(Each);
            }
        }
    }
    else
    {
        for (auto & Each : this->Children)
        {
            Each.Search(Range, ParticleInRange);
        }
    }
}

std::vector<A2DParticle*> AQuadTree::Query (const A2DCircle &Range)
{
    std::vector<A2DParticle*> ParticleInRange;
    this->Search(Range, ParticleInRange);

    return ParticleInRange;
}
