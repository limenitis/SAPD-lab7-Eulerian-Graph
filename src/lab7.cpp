#include ".\..\include\lab7.h"
using namespace std;

int Graph::get_count_node() { return count_node; }
int Graph::get_count_edge() { return count_edge; }
int Graph::get_count_odd_vertex() { return count_odd_vertex; }
int Graph::get_count_components() { return count_components; }
int Graph::get_odd_vertex()       { return odd_vertex; }

Graph::Graph()
{
    cout << "Введите количество вершин : ";
    wcin >> count_node;
    cout << "Введите количество ребер  : ";
    wcin >> count_edge;

    count_odd_vertex = 0; 
    odd_vertex = 0; 
    count_components = 0;

    // init
	matrix = new int* [col];
	for (int i = 0; i < col; i++)
	{
		matrix[i] = new int[row];
	}

    // fill
    cout << '\n';
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < col; i++)
		{
			cout << "[" << j + 1 << "][" << i + 1 << "] = ";
			cin >> matrix[i][j]; 
		}
	}
}

Graph::~Graph()
{
	// устранение утечек памяти
	for (int i = 0; i < col; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

bool Graph::check_for_euler_path()
{
    int pow_vertex;
    for (int i = 0; i < row; i++)
    {
        pow_vertex = 0;
        for (int j = 0; j < col; j++)
        {
            if (matrix[j][i] > 0) { pow_vertex++; }
        }
        if (pow_vertex % 2 == 1) { count_odd_vertex++; odd_vertex = i; }
    }

    if (count_odd_vertex > 2)        { return false; }
    if (find_count_components() > 1) { return false; }

    return true;
}

vector <int> Graph::find_euler_path()
{
    vector<int> result;

    int **matrix_old = matrix_backup(); 

    if(check_for_euler_path() == false)
    {
        return result;
    }

    int start;
    if(count_odd_vertex != 0)
    {
        start = odd_vertex;
    }
    else
    {
        start = 0;
    }

    //++ start DFS 
    stack<int> s;
	vector<int> neigh; // neighbors
    s.push(start);
    int v, u;  // 2 vertex - current and neighbor
    while (!s.empty())
    {
        v = s.top();
        neigh = find_neighbors(v);

        if(!neigh.empty())
        {
            u = neigh[neigh.size()-1];
            neigh.pop_back();
            s.push(u);
            delete_edge(find_edge_between_vertex(v, u));
        }

        else
        {
            s.pop();
            result.push_back(v);
        }

    }
    //++ end DFS

    remove_matrix(matrix);  // delete empty matrix
    matrix = matrix_old;    // and restore input matrix
    return result;
}

void Graph::delete_edge(int edge_id)
{
    int i = edge_id;
    for (int k = 0; k < row; k++)                   // пройти этот слолбец  | walk column
    {
        if (matrix[i][k] == 1){ matrix[i][k] = 0; } // и удалить связи      | and delete edge
    }
}

int Graph::find_edge_between_vertex(int v, int u) 
{
    for (int i = 0; i < col; i++) 
    {
        if (matrix[i][v] == 1 && matrix[i][u] == 1) { return i; }
    }
    return 0;
}

int Graph::find_count_components()
{
    vector<bool> vizited;     // visited vertex
    vector<int> components;   // array components ( components[4] => number component for vertex 4 )
    for (int i = 0; i < row; i++)
    {
        components.push_back(0);
        vizited.push_back(0);
    }
    
    //++ BFS
    int tmp;
    int start;
    int component_count = 0;
    queue <int> q;
	vector <int> neigh;
    
    while (find_zero_value(components) != row)
    {
        start = find_zero_value(components);
        component_count += 1;

        q.push(start);       // push start vertex
    	while (!q.empty())
    	{
    		tmp = q.front();                   // get vertex
            components[tmp] = component_count; // processing vertex         | обработка вершины
            neigh = find_neighbors(tmp);       // find neighbors for vertex | найти соседей
            vizited[tmp] = 1; // mark as visited        | пометить как посещенную
            q.pop();          // delete current vertex  | удалить обработанную вершину
    		
        	for (int i : neigh) 
        	{
                if (vizited[i] != 1)
                {
                    q.push(i); // add neighbors to queue | добавить соседей в очередь
                }
            }
            neigh.clear();
        }
    }

    count_components = component_count;
    return component_count;
}

vector <int> Graph::find_neighbors(int vertex_id)
{
    vector<int> neigh;
    int i = vertex_id;
    for (int j = 0; j < col; j++)                                       // пройти по строке     | walk row
    {
        if (matrix[j][i] == 1)                                          // если найдена 1       | if find 1
        {
            for (int k = 0; k < row; k++)                               // пройти этот слолбец  | walk this column
            {
                if (matrix[j][k] == 1 && k!=i){ neigh.push_back(k); }   // и добавить соседей   | and add neighbors
            }
        }
    }
    return neigh;
}

int Graph::find_zero_value(vector<int> arr)
{
    int i = 0;
    while (i < arr.size())
    {
        if (arr[i] == 0) { return i; }
        i++;
    }
    return i;
}

void Graph::print()
{
    cout << endl << "Матрица : " << endl << endl;

    //++ start print horizontal coordinates range ++
    cout << "   | ";
    for (int i = 0; i < col; i++)
	{
        cout << setw(2) << i+1 << " | ";
    }
	cout << "\n";

    cout << "-  ";
    for (int i = 0; i < col; i++)
	{
        cout << "|----";
    }
	cout << "| \n";
    //++ end print horizontal coordinates range ++

    for (int j = 0; j < row; j++)
    {
        cout << j+1 << "  | "; // vertical coordinates range
        for (int i = 0; i < col; i++)
		{
            cout << setw(2) << matrix[i][j] << " | ";
		}
		cout << "\n";
	}

    //++ start print horizontal line ++
    cout << "-  ";
    for (int i = 0; i < col; i++)
	{
        cout << "|----";
    }
	cout << "| \n";
    //++ end print horizontal line ++

    cout << "\n";
}


// сохранить матрицу потому что функция удаляет ребра (чтобы не проходить ребро 2 раза)
// save the matrix because the function removes the edges (so as not to walk edge 2 times)
int** Graph::matrix_backup()
{
    // init
    int **new_matrix = nullptr;
    new_matrix = new int* [col];
	for (int i = 0; i < col; i++)
	{
		new_matrix[i] = new int[row];
	}

    // fill
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < col; i++)
		{
			new_matrix[i][j] = matrix[i][j]; 
		}
	}

    return new_matrix;
}

void Graph::remove_matrix(int **matrix)
{
	// устранение утечек памяти
	for (int i = 0; i < col; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

}