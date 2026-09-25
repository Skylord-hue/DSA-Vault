# ⚡ DSA Vault — High-Performance Algorithmic Solutions in Modern C++20
[![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![LeetCode](https://img.shields.io/badge/LeetCode-ShadowDebugger-orange.svg)](https://leetcode.com/u/ShadowDebugger)
[![Institution](https://img.shields.io/badge/Institution-NIT%20Kurukshetra-green.svg)](http://www.nitkkr.ac.in)
[![Problems Solved](https://img.shields.io/badge/Verified%20Solutions-30%2B-purple.svg)](#-problem-index)

Curated repository of algorithmic solutions, graph traversals, tree architectures, and dynamic programming patterns implemented in **modern C++20** with strict adherence to asymptotic bounds and space-time optimality.

Engineered by **Narendra Chaudhary (Shadow)** · B.Tech CSE @ **NIT Kurukshetra** (`125102018`).

---

## 🏗️ Repository Architecture

```text
DSA/Code/
├── DP/                 # Dynamic Programming (Linear, Grids, Knapsack, Optimization)
├── Graphs/             # Graph Theory (BFS, DFS, Dijkstra, Bellman-Ford, DSU, Topo Sort)
├── Trees/              # Binary Trees, BSTs, Traversals, Views, Construction
└── Class_work/         # Core Sorting, Searching, and Foundational Algorithms
```

---

## 📑 Verified Problem Index

### ⚡ Dynamic Programming (`DP/`)
| Problem | File | Time Complexity | Space Complexity | Key Pattern / Invariant |
| :--- | :--- | :---: | :---: | :--- |
| **Fibonacci Numbers** | [`fibonacci.cpp`](DP/fibonacci.cpp) | `O(N)` | `O(1)` | Scalar rolling registers (`prev1`, `prev2`) |
| **Climbing Stairs** | [`climbing_stairs.cpp`](DP/climbing_stairs.cpp) | `O(N)` | `O(1)` | Combinatorial state reduction |
| **House Robber II (LeetCode 213)** | [`house_robber_ii.cpp`](DP/house_robber_ii.cpp) | `O(N)` | `O(1)` | Circular adjacency split into two linear subproblems |
| **Frog Jump & K-Distance** | [`frog_jump.cpp`](DP/frog_jump.cpp) | `O(N)` | `O(1)` | Optimal substructure minimization over predecessor DAG |
| **Coin Change** | [`coin_change.cpp`](DP/coin_change.cpp) | `O(N*Target)` | `O(Target)` | Unbounded Knapsack (Min elements) |
| **Coin Change II** | [`coin_change_ii.cpp`](DP/coin_change_ii.cpp) | `O(N*Target)` | `O(Target)` | Unbounded Knapsack (Combinations outer loop) |
| **Perfect Squares** | [`perfect_squares.cpp`](DP/perfect_squares.cpp) | `O(N*sqrt(N))` | `O(N)` | Unbounded Knapsack with perfect squares |
| **Last Stone Weight II** | [`last_stone_weight_ii.cpp`](DP/last_stone_weight_ii.cpp) | `O(N*Sum/2)` | `O(Sum/2)` | 0/1 Knapsack subset-sum reduction |
| **Partition Equal Subset Sum** | [`partition_equal_subset_sum.cpp`](DP/partition_equal_subset_sum.cpp) | `O(N*Sum/2)` | `O(Sum/2)` | 0/1 Knapsack Target = Sum / 2 |
| **Target Sum** | [`target_sum.cpp`](DP/target_sum.cpp) | `O(N*Target)` | `O(Target)` | Math reduction to Subset Sum `(total+target)/2` |

### 🕸️ Graphs (`Graphs/`)
| Problem / Algorithm | File | Time Complexity | Space Complexity | Key Pattern |
| :--- | :--- | :---: | :---: | :--- |
| **Disjoint Set Union (DSU)** | [`DSU.cpp`](Graphs/DSU.cpp) | `O(α(N))` | `O(N)` | Path compression + Union by rank/size |
| **Dijkstra's Algorithm** | [`dijkstra_problem.cpp`](Graphs/dijkstra_problem.cpp) | `O((V + E) log V)` | `O(V)` | Min-priority queue shortest path relaxation |
| **Bellman-Ford Algorithm** | [`bellford.cpp`](Graphs/bellford.cpp) | `O(V · E)` | `O(V)` | Negative cycle detection & relaxation |
| **Topological Sort** | [`topology_sort.cpp`](Graphs/topology_sort.cpp) | `O(V + E)` | `O(V)` | Kahn's in-degree BFS algorithm |
| **Custom Topological Sort** | [`custom_topological_sort.cpp`](Graphs/custom_topological_sort.cpp) | `O(V + E)` | `O(V)` | DFS post-order stack ordering |
| **Breadth-First Search (BFS)** | [`graph_bfs.cpp`](Graphs/graph_bfs.cpp) | `O(V + E)` | `O(V)` | Level-order queue traversal |

### 🌲 Binary Trees & BSTs (`Trees/`)
| Problem | File | Time | Space | Key Pattern |
| :--- | :--- | :---: | :---: | :--- |
| **Binary Tree Basics** | [`binary_tree.cpp`](Trees/binary_tree.cpp) | `O(N)` | `O(H)` | Recursive node structure & depth traversal |
| **Binary Search Tree** | [`binary_search_tree.cpp`](Trees/binary_search_tree.cpp) | `O(H)` | `O(H)` | BST search, insertion, and validation |
| **Tree by Inorder & Preorder** | [`tree_by_inorder_and_preorder.cpp`](Trees/tree_by_inorder_and_preorder.cpp) | `O(N)` | `O(N)` | Hash map lookup & index-bounded partition |
| **Largest BST in Binary Tree** | [`largest_bst_tree.cpp`](Trees/largest_bst_tree.cpp) | `O(N)` | `O(H)` | Bottom-up post-order 4-tuple validation |
| **Top View of Binary Tree** | [`top_view_tree_01.cpp`](Trees/top_view_tree_01.cpp) | `O(N log N)` | `O(N)` | Vertical coordinate mapping with map |
| **Top View (Optimized)** | [`top_view_tree_02.cpp`](Trees/top_view_tree_02.cpp) | `O(N)` | `O(N)` | Min/max horizontal coordinate bounds |
| **K-th Level of Binary Tree** | [`kth_level_tree.cpp`](Trees/kth_level_tree.cpp) | `O(N)` | `O(H)` | Depth-bounded recursive extraction |

### 🔍 Sorting & Searching (`Class_work/`)
| Algorithm | File | Time Complexity | Space Complexity |
| :--- | :--- | :---: | :---: |
| **Merge Sort** | [`mergeSort.cpp`](Class_work/mergeSort.cpp) | `O(N log N)` | `O(N)` |
| **Insertion Sort** | [`01_insertion_sort.cpp`](Class_work/01_insertion_sort.cpp) | `O(N²)` | `O(1)` |

---

## ⚡ Compilation & Execution

All solutions are compiled using Apple Clang C++20 with optimization flags:

```zsh
clang++ -std=c++20 -O2 -Wall -Wextra solution.cpp -o solution
./solution
```
