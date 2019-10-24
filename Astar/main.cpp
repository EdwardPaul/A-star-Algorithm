#include "struct.h"
#include "astar.h"

int main(int argc, char* argv[])
{
    Map map1(argv[1]);


    Search search(map1, argv[1]);
    search.Astar(map1, argv[1]);
}
