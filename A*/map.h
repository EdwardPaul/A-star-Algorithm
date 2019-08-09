#ifndef MAP_H
#define MAP_H

#include <fstream>

#include "struct.h"

using namespace std;

class Map
{
public:
    Map();
    ~Map();
    bool IsValid(int, int);
    bool IsObstacle(int, int);

    int rows, cols;
    char **p;
    Node start, fin;
};

#endif // MAP_H
