#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

#include "matrix.h"

const int SIZE = 50;
const float DENSITY = 0.7;
const int LOW_RANGE = 1;
const int HI_RANGE = 10;
const int SOURCE = 0;

int main()
{
    Matrix m(SIZE);

    /*
    // for testing create static graph from    
    // https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/ 


    m.setedge(0, 1, 4); 
    m.setedge(0, 7, 8); 
    m.setedge(1, 2, 8); 
    m.setedge(1, 7, 11); 
    m.setedge(2, 3, 7); 
    m.setedge(2, 8, 2); 
    m.setedge(2, 5, 4); 
    m.setedge(3, 4, 9); 
    m.setedge(3, 5, 14); 
    m.setedge(4, 5, 10); 
    m.setedge(5, 6, 2); 
    m.setedge(6, 7, 1); 
    m.setedge(6, 8, 6); 
    m.setedge(7, 8, 7); 
    */

    m.r_populate(DENSITY, LOW_RANGE, HI_RANGE);
    // m.displaygraph();
    m.doDijkstra(SOURCE);
    m.displaypaths(SOURCE);

    return 0;
}
