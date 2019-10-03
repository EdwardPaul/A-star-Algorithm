#include "struct.h"
#include "astar.h"

int main()
{
    Map map;
//    start_x = 147;
//    map.start.j = 213;
//    map.fin.i = 273;
//    map.fin.j = 487;


    Search search(147, 213, 273, 487);
    search.Astar(map);
}
