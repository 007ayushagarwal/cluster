# README

## Clustering Algorithm Implementation in C++

### Overview

This repository contains a C++ implementation of various clustering algorithms based on Minimum Spanning Tree (MST). The code allows for different clustering methods such as clustering based on the number of clusters, a threshold value, or density. The user can choose the clustering method through a menu-driven interface.

### Features

1. **Minimum Spanning Tree (MST) Construction**: 
   - Implements Prim's algorithm to construct the MST of a complete graph generated from a set of 2D points.

2. **Clustering Methods**:
   - **Number-Based Clustering**: Generates a specified number of clusters by removing the edges with the maximum weights.
   - **Threshold-Based Clustering**: Clusters are created by removing edges with weights above a given threshold.
   - **Density-Based Clustering**: Divides clusters based on the density of points within the cluster.

3. **Menu-Driven Interface**: 
   - The program provides a menu-driven interface allowing the user to choose the clustering method and input relevant parameters (like the number of clusters or threshold).

### Code Structure

- **Global Variables**:
  - `n`: Number of vertices in the graph (set to 100).
  - `mat[n][n]`: Adjacency matrix to store the weights (distances) between the vertices.

- **Structures**:
  - `value`: Represents a point in 2D space with `x` and `y` coordinates.
  - `Graph`: Represents a vertex in the graph with fields `v` (vertex ID), `key` (weight), and `p` (parent pointer).
  - `Graph_Node`: Linked list node for storing `Graph` objects, used in the priority queue.
  - `cl_Node`: Linked list node for storing clusters of `Graph_Node` objects.

- **Functions**:
  - **Adjacency Matrix Construction**:
    - `weight(value a, value b)`: Calculates the Euclidean distance between two points.
    - `make_adj_mat(value* d)`: Fills the adjacency matrix with weights between all pairs of points.
  
  - **Minimum Spanning Tree (MST) Construction**:
    - `MST_prim(Graph* Gr, int r)`: Constructs the MST using Prim's algorithm starting from vertex `r`.
    - `print_graph(Graph* Gr)`: Prints the MST.
  
  - **Clustering Functions**:
    - `cluster_base_on_number(Graph* Gr, int no)`: Clusters the graph into `no` clusters by removing the heaviest edges.
    - `cluster_base_on_threshold(Graph* Gr, float th)`: Clusters the graph by removing edges with weights above `th`.
    - `cluster_based_on_density(Graph* Gr)`: Clusters the graph based on the density of points.
    - `menue_driven_clustring(Graph* Gr)`: Provides a menu-driven interface for the user to select the clustering method.
  
  - **Helper Functions**:
    - `Enqueue`, `Dequeue`, `Create_node`, `delete_node`, `search_node`, `in_queue`, etc.: Various utility functions for handling the linked lists and queues used in the MST and clustering processes.
    - `print_all_cluster(cl_Node* F)`: Prints all the clusters generated.

### How to Run

1. **Compile the Code**:
   - Use a C++ compiler to compile the code:
     ```
     g++ -o clustering clustering.cpp
     ```

2. **Run the Program**:
   - Execute the compiled binary:
     ```
     ./clustering
     ```

3. **Choose Clustering Method**:
   - Follow the prompts in the menu to choose the clustering method and provide necessary parameters.

### Example

- **Number-Based Clustering**:
  - Input the number of clusters (e.g., 3), and the program will divide the graph into 3 clusters.

- **Threshold-Based Clustering**:
  - Input a threshold value (e.g., 10.0), and the program will remove all edges with weights above this value, creating clusters.

- **Density-Based Clustering**:
  - The program will automatically divide the graph based on the density of points in the clusters.

