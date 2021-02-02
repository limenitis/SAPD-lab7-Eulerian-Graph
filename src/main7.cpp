#include ".\..\include\lab7.h"
#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <queue>
#include <string>
using namespace std;

//----
// Для обнаружения утечек памяти
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#define DumpMemoryLeaks                                 \
_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);        \
_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);      \
_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);       \
_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);     \
_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);      \
_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);    \
_CrtDumpMemoryLeaks();
//----

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

    Graph g;
    g.print();

    cout << "\n" << endl;
    for (int k = 0; k < g.get_count_node(); k++)
    {
        // neighbors of a vertex
        cout << "Соседи вершины " << k+1 << " : " << endl;
        for (auto i : g.find_neighbors(k))
        {
            cout << "|" << i+1;
        }
        cout << "| \n" << endl;
    }

    vector <int> path = g.find_euler_path();
    if(path.size() == 0)
    {
        // Eulerian path not found
        cout << endl << "Эйлеров путь не найден" << endl << endl;
    }
    else
    {   
        // Eulerian path :
        cout << endl << "Эйлеров путь : ";
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] + 1;
            if(i != path.size()-1)
            cout << "->";
        }
        cout << '\b' << endl;
    }

    // print info
    // Number of connectivity components
    cout << endl << "Количество компонент связности : " << g.get_count_components() << endl; 
    // Number of odd vertices
    cout << endl << "Количество нечетных вершин     : " << g.get_count_odd_vertex() << endl;
    cout << endl;

    return 0;
}

