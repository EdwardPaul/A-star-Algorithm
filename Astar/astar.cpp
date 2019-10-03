#include "astar.h"


Search::Search(int s_x, int s_y, int g_x, int g_y)
{
    result.lenght = 0;
    result.FoundPath = false;

    start.x = s_x;
    start.y = s_y;
    goal.x = g_x;
    goal.y = g_y;
}

Search::~Search()
{}

double Search::Hfunc(Node curr, Node fin, Heuristics eur)
{
    switch (eur)
    {
    case EUCLID:
        return sqrt(pow(curr.i-fin.i,2) + pow(curr.j-fin.j,2));
    case MANHATTAN:
        return (abs(curr.i-fin.i) + abs(curr.j - fin.j));
    case DIAGONAL:
        return (abs(abs(curr.i - fin.i) - abs(curr.j - fin.j)) + sqrt(2) * min(abs(curr.i - fin.i), abs(curr.j - fin.j)));
    case CHEBYSHEV:
        return max(abs(curr.i - fin.i), abs(curr.j - fin.j));
    default:
        return 0;
    }
}

void Search::Path(Node curr, Map &map)
{
    Config path;
    while(curr.parent)
    {
        path.x = curr.i;
        path.y = curr.j;
        result.track.push_front(path);
        curr = *curr.parent;
    }

    result.track.push_front(path);
    cout<<"Trajectory: ";
    while(!result.track.empty())
    {
        //Config temp = *result.track.begin();
        result.track.pop_front();
        //map.p[temp.i][temp.j] = 8;
        //cout << "->(" << temp.i << ", " << temp.j << ")";
        result.lenght++;
    }
    cout<<endl;
//    for (int i=0; i<map.rows; i++)
//    {
//        for (int k=0; k<map.cols; k++)
//        {
//            cout << map.p[i][k];
//        }
//        cout << endl;
//    }
    cout << "OpenSize: " << open.size() << endl;
    cout << "CloseSize: " << close.size() << endl;
    cout << "Total number of steрs: " << result.TotalSteps << endl;
    cout << "Lenght: " << result.lenght << endl;
    return;
}


list<Node> Search::findSuccessors(Node curr, Map &map)
{
    Node near;
    list<Node> successors;
    for (int k=-1; k<2; k++)
    {
        for (int l=-1; l<2; l++)
        {
            if (map.IsValid(curr.i + k, curr.j + l) && !map.IsObstacle(curr.i + k, curr.j + l) && (k!=0 || l!=0) && close.find((curr.i+k)*map.rows + curr.j+l)==close.end())
            {
                near.i = curr.i + k;
                near.j = curr.j + l;

                if(k==0 || l==0)
                {
                    near.g = curr.g + MOVE_COST_STR;
                }
                else
                {
                    near.g = curr.g + MOVE_COST_DIAG;
                }

                list<Node>::iterator f = find(open.begin(), open.end(), near);
                Node b = *f;

                if (find(open.begin(), open.end(), near)==open.end() || b.g <=near.g)
                {
                    successors.push_front(near);
                }
            }
        }
    }
    return successors;
}

SearchResult Search::Astar(Map &map)
{
    Node curr;
    Node fin;
    fin.i = goal.x;
    fin.j = goal.y;
    curr.i = start.x;
    curr.j = start.y;
    curr.g = 0.0;
    curr.h = Hfunc(curr, fin, EUCLID);
    curr.f = curr.g + curr.h;
    curr.parent = nullptr;

    open.push_back(curr);

    while(!open.empty())
    {
        Node min;
        min.f = LONG_MAX;


        list<Node>::iterator it = open.begin();
        while (it != open.end())
        {
            if (it->f <= min.f)
                min = *it;
            it++;
        }
        curr = min;
        open.remove(curr);

        if (curr.i == fin.i && curr.j == fin.j)
        {
            result.FoundPath = true;
            result.TotalSteps = close.size() + open.size();
            Path(curr, map);
        }

        close.insert({curr.i*map.rows + curr.j, curr});

        list <Node> successors = findSuccessors(curr, map);
        list <Node> :: iterator it2 = successors.begin();

        while (it2!=successors.end())
        {
            it2->parent = &(close.find(curr.i*map.rows + curr.j)->second);
            it2->h = Hfunc(*it2, fin, EUCLID);
            it2->f = it2->g + it2->h;
            open.push_back(*it2);
            it2++;
        }

    }

    if(result.FoundPath == false)
    {
        cout<< "Meh" <<endl;
    }

    return result;

}


