#include "struct.h"
#include "astar.h"

int main()
{
    Map map;


    Search search(393, 356, 89, 219);
    search.Astar(map);
}
