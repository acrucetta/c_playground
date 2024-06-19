/*
B-trees:
- A way to get better locality by putting multiple elements into each tree node
- Binary search trees are not good for locality because a given node of the binary tree
probably occupies only a fraction of any cache line

Characteristics:
- High branching factor (>2)
- Few disk reads needed to navigate to the data
- Useful for in-memory data structures
- Used by database systems
- Runtime of O(logn)

A B-tree of order m is a search tree in which each non leaf node has up to m children
1. Every path from the root to a leaf has the same length
2. If a node has n children, it contains n−1 keys.
3. Every node (except the root) is at least half full
4. The elements stored in a given subtree all have keys that are between
the keys in the parent node on either side of the subtree pointer. (This generalizes the BST invariant.)
5. The root has at least two children if it is not a leaf.
6. The B-Tree grows and shrinks from the root
7. The Insertion of a Node in the B Tree happens only at the Leaf Node.

Implementations:
- https://github.com/tidwall/btree.c
- https://www.math.umd.edu/~immortal/CMSC420/notes/btrees.pdf
- https://eatonphil.com/btrees.html
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_KEYS 10 // Example value; typically 2t-1 for a B-tree of degree t

typedef struct __node_t
{
    // degree of tree called t, each node (except root) must have a min of t-1 key
    int degree;
    // lower bound: t-1 keys; t children
    // upper bound: 2t-1 keys; at most 2t children
    int num_keys;
    bool is_leaf;
    int *keys;                 // Values in each node
    struct _node_t **children; // Each node can have up to max_keys + 1 children
} node_t;

typedef struct __node_t *btree;

node_t *btree_init(int min_degree)
{
    btree b = (btree)malloc(sizeof(node_t));
    if (b == NULL)
    {
        perror("malloc");
        exit(1);
    }
    b->is_leaf = true;
    b->degree = min_degree;
    b->num_keys = 0;

    int max_keys = 2 * min_degree - 1;
    b->keys = (int *)malloc(max_keys * sizeof(int));
    b->children = (node_t **)malloc((max_keys + 1) * sizeof(node_t *));
    if (b->keys == NULL || b->children == NULL)
    {
        perror("malloc");
        free(b->keys); // Free any allocated memory if allocation fails
        free(b->children);
        free(b);
        exit(1);
    }
    for (int i = 0; i < max_keys + 1; i++)
    {
        b->children[i] = NULL; 
    }
    return b; 
}

/*
Find a key
1. If the key is found in the current node, you're done.
2. If the key is not found and the node is a leaf,
the key is not in the tree.
3. If the key is not found and the node is not a leaf,
you move to the appropriate child node and repeat the process.
*/
node_t *btree_search(btree root, int key)
{
    int i = 0;
    while (i < root->num_keys && key > root->keys[i])
    {
        i++;
    }
    if (i < MAX_KEYS && key == root->keys[i])
    {
        return root;
    }
    if (root->is_leaf)
    {
        return NULL;
    }
    return btree_search(root->children[i], key);
}

/*
Insert a new key

- Finding the correct leaf node where the key should be added.
- If the node has room for the new key, you simply insert it in the correct position.
- If the node is full (i.e., it has 2t - 1 keys), you split the node into two nodes:
    - The middle key of the full node moves up to the parent node.
    - The keys to the left of the middle key form a new left child node.
    - The keys to the right of the middle key form a new right child node.
- If the parent node is also full, you may need to split the parent node as well,
and this process can propagate up to the root, potentially increasing the height of the tree.

*/
void btree_insert(btree root, int key)
{
    // Check if the keys are full keys = (2*t) - 1
    if (root->num_keys == (2*root->degree)-1) {
        // Create new node
        // Insert to its children
        // Split the child at new node 
        // Insert non-full
        return NULL;
    } else 
    {
        _insert_non_full(root,key);
    }
    return NULL;
}

void _insert_non_full(btree root, int key)
{
    return NULL;
}

void _split_child(btree root, int key)
{
    return NULL;
}

/*
Remove a key

- If the key is in a leaf node, simply remove it.
- If the key is in an internal node, you need to replace it with a suitable
  key from a leaf node to maintain the B-tree properties:
    - You can use the predecessor (largest key in the left subtree) or successor
    (smallest key in the right subtree) of the key.
    - After replacing the key, you then delete the predecessor or successor key from the leaf node.
- If a node has fewer than t keys after deletion, you need to rebalance
the tree by borrowing keys from sibling nodes or merging nodes.

*/
void btree_delete(int min_degree)
{
    // Init the tree
}

/*
Visit all keys in sorted order

*/
void btree_traverse(int min_degree)
{
    // Init the tree
}