# QuadTree2D &ndash; A collision detection algorithm

A simple collision detection method, brute force algorithm, 
that checks every pair of objects in a scene, can be highly computationally 
expensive, especially when dealing with a large number of objects. 
This can lead to significant processing overheads, 
resulting in decreased application performance and responsiveness. 
As a consequence, there is a critical need for more efficient and 
optimized collision detection algorithm in 2D environments.

This repository focuses on implementing a quad tree algorithm 
for 2D collision detection. A quad tree is a tree data structure in which 
each internal node has exactly four children: northwest, northeast, southwest, and southeast. 
It's particularly well-suited for spatial partitioning tasks, as it recursively
divides space into quadrants, allowing for efficient querying of objects 
within specific regions. The algorithm reduces the number of pairwise
collision checks required, making it highly efficient for scenarios 
involving a large number of objects.
