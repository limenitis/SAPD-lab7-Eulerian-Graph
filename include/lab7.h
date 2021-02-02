#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define col count_edge
#define row count_node

class Graph
{
private:
    int **matrix = nullptr; // init in constructor
    int count_node;         // col
    int count_edge;         // row
    int count_odd_vertex;   // init in constructor
    int count_components;   // init in constructor
    int odd_vertex;         // init in constructor
    int **matrix_backup();
    void remove_matrix(int **matrix);

public:
    int get_count_node();
    int get_count_edge();
    int get_odd_vertex();
    int get_count_odd_vertex();
    int get_count_components();

    Graph();
    ~Graph();
    bool          check_for_euler_path();
    vector<int>   find_euler_path();

    int           find_edge_between_vertex(int v, int u);
    int           find_zero_value(vector<int> arr);
    vector<int>   find_neighbors(int vertex_id);
    void          delete_edge(int edge_id);
    int           find_count_components();

    void          print();
};

