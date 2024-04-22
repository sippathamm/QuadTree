#pragma once

#include <vector>

#include "Geometry2D.h"

/**
 * @brief Macro to get the size of a container.
 * @param A The container.
 * @return The size of the container.
 */
#define SIZE(A)     (int)A.size()

/**
 * @brief A class representing a quadtree in 2D space.
 */
class AQuadTree
{
public:
    /**
     * @brief Construct a quadtree with the specified boundary.
     * @param Boundary The boundary of the quadtree.
     */
    explicit AQuadTree (const A2DRectangle &Boundary) :
                        Boundary_(Boundary),
                        CurrentDepth_(0)
    {

    }

    /**
     * @brief Insert a particle into the quadtree.
     * @param Particle The particle to insert.
     */
    void Insert (A2DParticle &Particle)
    {
        // Check if the particle is within the quadtree boundary
        if (!Particle.IsIn(this->Boundary_))
        {
            return;
        }

        // Check if the current node is a leaf and needs to be subdivided
        if (this->IsLeaf() && SIZE(this->Contain_) + 1 > this->MaxCapacity_)
        {
            Subdivide();
        }

        // If the node is a leaf, add the particle to the containment list,
        // otherwise, insert the particle into the appropriate child node
        if (this->IsLeaf())
        {
            this->Contain_.push_back(&Particle);
        }
        else
        {
            for (auto &Child : this->Children_)
            {
                Child.Insert(Particle);
            }
        }
    }

    /**
     * @brief Query particles within a specified range.
     * @param Range The range within which to query particles.
     * @return A vector of particles within the specified range.
     */
    std::vector<A2DParticle*> Query (const A2DCircle &Range)
    {
        std::vector<A2DParticle*> ParticleInRange;
        this->Search(Range, ParticleInRange);
        return ParticleInRange;
    }

private:
    int CurrentDepth_; /**< The current depth of the quadtree node. */
    int MaxDepth_ = 5; /**< The maximum depth allowed for the quadtree. */
    int MaxCapacity_ = 15; /**< The maximum capacity of particles in a leaf node. */
    A2DRectangle Boundary_; /**< The boundary of the quadtree node. */
    std::vector<A2DParticle*> Contain_; /**< The list of particles contained in the quadtree node. */
    std::vector<AQuadTree> Children_; /**< The children nodes of the quadtree node. */

    /**
     * @brief Check if the quadtree node is a leaf.
     * @return True if the node is a leaf, false otherwise.
     */
    bool IsLeaf ()
    {
        return this->Children_.empty();
    }

    /**
     * @brief Subdivide the quadtree node.
     */
    void Subdivide ()
    {
        // Check if the current depth has reached the maximum depth allowed
        if (this->CurrentDepth_ + 1 >= this->MaxDepth_)
        {
            return;
        }

        // Calculate the center and half extent of the subdivision regions
        A2DPoint Center = this->Boundary_.Center;
        A2DVector HalfHalfExtent = this->Boundary_.HalfExtent * 0.5f;

        // Define the subdivision regions
        A2DRectangle SubdivideRegion[] =
        {
                // SubdivideRegion[0]: North-East
                A2DRectangle({ Center.X + HalfHalfExtent.X, Center.Y + HalfHalfExtent.Y }, HalfHalfExtent),
                // SubdivideRegion[1]: North-West
                A2DRectangle({ Center.X - HalfHalfExtent.X, Center.Y + HalfHalfExtent.Y }, HalfHalfExtent),
                // SubdivideRegion[2]: South-East
                A2DRectangle({ Center.X + HalfHalfExtent.X, Center.Y - HalfHalfExtent.Y }, HalfHalfExtent),
                // SubdivideRegion[3]: South-West
                A2DRectangle({ Center.X - HalfHalfExtent.X, Center.Y - HalfHalfExtent.Y }, HalfHalfExtent),
        };

        // Create child nodes for each subdivision region
        for (int Index = 0; Index < 4; Index++)
        {
            this->Children_.emplace_back(SubdivideRegion[Index]);
            this->Children_[Index].CurrentDepth_++;
        }

        // Distribute particles from the current node to its child nodes
        for (const auto &Each : this->Contain_)
        {
            this->Children_[0].Insert(*Each);
            this->Children_[1].Insert(*Each);
            this->Children_[2].Insert(*Each);
            this->Children_[3].Insert(*Each);
        }

        // Clear the containment list of the current node
        Contain_.clear();
    };

    /**
     * @brief Search for particles within a specified range recursively.
     * @param Range The range within which to search for particles.
     * @param ParticleInRange A vector to store particles found within the range.
     */
    void Search (const A2DCircle &Range, std::vector<A2DParticle*> &ParticleInRange)
    {
        // Check if the range intersects with the boundary of the current node
        if (!Range.IsBeingIntersect(this->Boundary_))
        {
            return;
        }

        // If the current node is a leaf, check containment list for particles within the range
        // Otherwise, recursively search in child nodes
        if (this->IsLeaf())
        {
            for (const auto &Each : this->Contain_)
            {
                if (Each->IsBeingIntersect(Range))
                {
                    ParticleInRange.push_back(Each);
                }
            }
        }
        else
        {
            for (auto &Child : this->Children_)
            {
                Child.Search(Range, ParticleInRange);
            }
        }
    }
};
