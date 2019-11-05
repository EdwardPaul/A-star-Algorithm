#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "struct.h"
#include "tinyxml2.h"
#include "const.h"

using namespace std;

class Map
{
private:
    int **Grid;
public:
    Map();
    ~Map();
    bool IsValid(int, int);
    bool IsObstacle(int, int);
    void getMap(const char*);
    int getValue(int, int) const;

    int width;
    int height;
    int start_i, start_j, goal_i, goal_j;
    double cellSize;
    const char* filename;


};

#endif // MAP_H
