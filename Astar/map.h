#ifndef MAP_H
#define MAP_H

#include <fstream>

#include "struct.h"

using namespace std;

class Map
{
private:
    int cols;
    char **p;

public:
    Map();
    ~Map();
    bool IsValid(int, int);
    bool IsObstacle(int, int);

    int rows;

};

#endif // MAP_H
