#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Matrix
{
    private:
        vector<vector<int>> graph;
        const int INFINITE = 0x3F3F3F3F;
        const bool DIRECTED = false;
        vector<int> dist;  // holds distances from source to node
        vector<int> prev;  // parent of node on shortest path
        bool isedge(int x, int y);
        list<int> neighbors(int x);
        
    public:
        Matrix(int size);
        ~Matrix();
        void setedge(int x, int y, int len);
        void displaygraph();
        void r_populate(float density, int low_range, int hi_range);
        void doDijkstra(int source);
        void displaypaths(int source);
};