/*
B-trees:
- A way to get better locality by putting multiple elements into each tree node
- Binary search trees are not good for locality because a given node of the binary tree 
probably occupies only a fraction of any cache line

Characteristics:
- High branching factor (>2)
- Few disk reads needed to navigate to the data
- Useful for in-memory data structures

A B-tree of order m is a search tree in which each non leaf node has up to m children
1. Every path from the root to a leaf has the same length
2. If a node has n children, it contains n−1 keys.
3. Every node (except the root) is at least half full
4. The elements stored in a given subtree all have keys that are between 
the keys in the parent node on either side of the subtree pointer. (This generalizes the BST invariant.)
5. The root has at least two children if it is not a leaf.
*/