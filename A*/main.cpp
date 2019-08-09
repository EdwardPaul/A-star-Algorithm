#include "struct.h"
#include "astar.h"

int main()
{
    Map map;
    map.start.i = 503;
    map.start.j = 239;
    map.fin.i = 42;
    map.fin.j = 93;


    Search search;
    search.Astar(map);
}
