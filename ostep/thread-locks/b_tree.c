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
- https://github.com/msambol/dsa/blob/master/trees/b_tree.py#L13
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_CHILDREN 4 // Example value; typically 2t-1 for a B-tree of degree t
#define MAX_KEYS 3     //

typedef struct __node_t
{
    // lower bound: t-1 keys; t children
    // upper bound: 2t-1 keys; at most 2t children
    int num_keys;
    bool is_leaf;
    int keys[MAX_CHILDREN - 1];             // Array of keys
    struct _node_t *children[MAX_CHILDREN]; // Each node can have up to max_keys + 1 children
    pthread_mutex_t m;
} node_t;

typedef struct __node_t *btree;

node_t *btree_create_node(bool is_leaf)
{
    btree b = (btree)malloc(sizeof(node_t));
    if (b == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    b->is_leaf = is_leaf;
    b->num_keys = 0;
    for (int i = 0; i < MAX_CHILDREN; i++)
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
    if (i < MAX_CHILDREN && key == root->keys[i])
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
    if (root->num_keys == MAX_KEYS)
    {
        node_t *new_node = btree_create_node(false);
        new_node->children[0] = root;    // Set the new node as the root
        _split_child(root, 0);           // Splits the old root into two nodes
        _insert_non_full(root, key);     // Insert the key to the root
        return NULL;
    }
    else
    {
        _insert_non_full(root, key);
    }
    return NULL;
}

void _insert_non_full(btree node, int key)
{
    int i = node->num_keys - 1;
    if (node->is_leaf)
    {
        // Iterate through the keys until we find the correct part
        while (i >= 0 && key < node->keys[i])
        {
            // shifts the keys right as we iterate through the list
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    }
    else
    {
        // We need to find the subtree where the key belongs
        while (i >= 0 && key < node->keys[i])
        {
            i--;
        }
        // If that child is full we split it.
        if (node->children[i].num_keys == MAX_KEYS)
        {
            _split_child(node, i);
            if (key > node->keys[i])
            {
                i++;
            }
        }
        // We then keep calling non_full until we hit a leaf
        _insert_non_full(node->children[i], key);
    }
    return NULL;
}

void _split_child(btree x, int i)
{
    // Step 1: Set up the nodes
    btree y = x->children[i];
    btree z = btree_create_node(y->is_leaf);

    // Add to x's list of children
    x->children[i+1] = z;    

    // Step 2: Move the middle key to the parent
    int middle_key = y->keys[MAX_KEYS / 2];
    x->keys[x->num_keys] = middle_key;
    x->num_keys++;

    // Step 3: Move the right half of the child (y) to the new child (z)
    int j = 0;
    for (int i = (MAX_KEYS / 2) + 1; i < MAX_KEYS; i++)
    {
        z->keys[j] = y->keys[i];
        z->num_keys++;
        j++;
    }

    // Step 4: If not a leaf, move the corresponding children as well
    if (!y->is_leaf)
    {
        j = 0;
        for (int i = (MAX_KEYS / 2) + 1; i <= MAX_KEYS; i++)
        {
            z->children[j] = y->children[i];
            j++;
        }
    }

    // Step 5: Update the child's key count
    y->num_keys = MAX_KEYS / 2;
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

Case 1: Simply remove from a leaf node
Case 2a: Internal node, left child has t keys
Case 2b: Internal node, right child has t keys
Case 2c: Internal node, both children have t-1 keys
Case 3a: node has only t-1 keys but sibling has t keys
Case 3b: node in recursion path has only t-1 keys
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