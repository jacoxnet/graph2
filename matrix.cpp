#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#include "matrix.h"

// Default constructor 
Matrix::Matrix(int size)
{
    graph.resize(size, vector<int> (size));

    // set length of all edges to INFINITE (no edge)
    // except for identity edges (eg 0 to 0) set to 0
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                graph[i][j] = INFINITE;
            }
        }
    }
}

Matrix::~Matrix()
{
}

void Matrix::setedge(int x, int y, int len)
{
    graph[x][y] = len;
    // if a nondirected graph, edges are symmetrical
    if (!DIRECTED)
    {
        graph[y][x] = len;
    }
}    

// following code populates a matrix with
// edges of probability based on density and lengths between 
// low_range and hi_range (inclusive)
void Matrix::r_populate(float density, int low_range, int hi_range)
{
    srand(time(NULL));
    // assign an edge based on probability density
    for (int i = 0; i < graph.size(); i++)
    {
        // put random edges in first half of matrix (all we need
        // to do for nondirected)
        for (int j = 0; j < i; j++)
        {
            if ((rand() % 1000) < (density * 1000))
            {
                int length = rand() % (hi_range - low_range) + low_range;
                setedge(i, j, length);
            }
        }
        // only do second half of matrix if directed and we need separate
        // numbers there
        if (DIRECTED)
        {
            for (int j = i + 1; j < graph.size(); j++)
            {
                if ((rand() % 1000) < (density * 1000))
                {
                    int length = rand() % (hi_range - low_range) + low_range;
                    setedge(i, j, length);
                }
            }
        }
    }
    cout << "Random graph created size:" << graph.size() << " density:" << density 
            << " range:" << low_range << "-" << hi_range << endl;
}

bool Matrix::isedge(int x, int y)
{
    if (graph[x][y] == INFINITE) 
    {
        return false;
    }
    else 
    {
        return true;
    }
}  

list<int> Matrix::neighbors(int x)
{
    list<int> n;
    n.clear();
    for (int i = 0; i < graph.size(); i++)
    {
        if ((i != x) && isedge(x, i))
        {
            n.push_back(i);
        }
    }
    return n;
}

void Matrix::displaygraph()
{
    for (int i = 0; i < graph.size(); i++)
    {
        cout << "node " << i << ", neighbors ";
        list<int> n = neighbors(i);
        for (list<int>::iterator pi = n.begin(); pi != n.end(); ++pi)
        {
            cout << *pi << " (len " << graph[i][*pi] << ") ";
        }
        cout << endl;
    }
}

void Matrix::displaypaths(int source)
{
    int sum = 0;
    int npaths = 0;
    for (int i = 0; i < graph.size(); i++)
    {
        if (i == source)
        {
            cout << "vertex " << i << " is the source" << endl;
        }
        else if (dist[i] == INFINITE)
        {
            cout << "no path from vertex " << i << " back to source" << endl;
        }
        else
        {
            cout << "path from vertex: " << i << " back to source, distance "<< dist[i] << endl;
            sum += dist[i];
            npaths++;
            int j = i;
            do 
            {
                cout << "   node " << j << " to node " << prev[j] << " length " << graph[j][prev[j]] << endl;
                j = prev[j];
            }
            while (j != source);
        }
    }
    if (npaths > 0)
    {
        cout << "Average distance for " << npaths << " paths is: " << float(sum)/npaths << endl;
    }
    else
    {
        cout << "No paths and no average" << endl;
    }
    
}

void Matrix::doDijkstra(int source)
{
    list<int> Q;    // holds vertices that haven't been visited

    // allocate memory for dist and prev
    dist.resize(graph.size());
    prev.resize(graph.size()); 

    // add all vertices to Q and initialize dist and prev
    for (int i = 0; i < graph.size(); i++)
    {
        Q.push_back(i);
        dist[i] = INFINITE;     // 
        prev[i] = INFINITE;
    }

    dist[source] = 0;
    while (!Q.empty())
    {
        // get element in Q with smallest dist[]
        int u = Q.front();
        for (list<int>::iterator it = next(Q.begin(), 1); it != Q.end(); ++it)
        {
            if (dist[*it] < dist[u])
            {
                u = *it;
            }
        }
        // remove the vertex with that index from Q
        Q.remove(u);
        // now iterate through neighbors of index
        list<int> n = neighbors(u);
        // pv iterates through neighbors
        for (list<int>::iterator pv = n.begin(); pv != n.end(); ++pv)
        {
            // only do this for nodes still in Q
            if (count(Q.begin(), Q.end(), *pv) != 0)
            {
                int alt = dist[u] + graph[u][*pv];
                if (alt < dist[*pv])
                {
                    dist[*pv] = alt;
                    prev[*pv] = u;
                }
            }
        }
    }
}