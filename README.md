# Binary Search Tree in C+

This repository contains C++ and Python implementations of a **Binary Search Tree** with the following core functions:

- **`btree_insert`** – insert a new key into the tree while maintaining the BST property.  
- **`btree_search`** – look up a key and return the node if present.  
- **`btree_delete`** – remove a node by key, handling the standard three deletion cases (leaf, one child, two children).  
- **`btree_min`** / **`btree_max`** – return the node with the smallest or largest key.  
- **`btree_successor`** / **`btree_predecessor`** – find the next larger or smaller node in in-order sequence.  
- **`btree_inorder`**, **`btree_preorder`**, **`btree_postorder`** – traversals producing the keys in different orders.  
- **Helper functions** – transplant subtrees, clear memory, and maintain parent/child links.

These functions together support efficient insertion, search, deletion, and traversal of keys.

## Usage

Compile and run with:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o bst src/btree.cc main.cpp
./bst
