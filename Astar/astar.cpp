#include "astar.h"


Search::Search(int s_x, int s_y, int g_x, int g_y)
{
    result.length = 0;
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
    //ofstream file("track");
    AgentConfiguration path;
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
        //AgentConfiguration temp = *result.track.begin();
        result.track.pop_front();
        //map.p[temp.x][temp.y] = 8;
        //cout << "->(" << temp.i << ", " << temp.j << ")";
        result.length++;
    }
    cout<<endl;
//    for (int i=0; i<map.rows; i++)
//    {
//        for (int k=0; k<map.cols; k++)
//        {
//            file << map.p[i][k];
//        }
//        file << endl;
//    }
    cout << "OpenSize: " << open.size() << endl;
    cout << "Total number of steрs: " << result.TotalSteps << endl;
    cout << "Total number of nodes: " << result.NodesNum << endl;
    cout << "length: " << result.length << endl;
    cout << "Time: " << result.Time << endl;
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
            if (map.IsValid(curr.i + k, curr.j + l) && !map.IsObstacle(curr.i + k, curr.j + l) && (k!=0 || l!=0))
            {
                near.i = curr.i + k;
                near.j = curr.j + l;

                successors.push_front(near);
            }
        }
    }
    return successors;
}

SearchResult Search::Astar(Map &map)
{
    result.Time = time(NULL);
    Node curr;
    Node fin;
    fin.i = goal.y;
    fin.j = goal.x;
    curr.i = start.y;
    curr.j = start.x;
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
            result.TotalSteps = close.size();
            result.NodesNum = open.size() + close.size();
            result.Time = time(NULL) - result.Time;
            Path(curr, map);
            break;
        }

        close.insert({curr.i*map.rows + curr.j, curr});

        list <Node> successors = findSuccessors(curr, map);
        list <Node> :: iterator it2 = successors.begin();

        while (it2!=successors.end())
        {
            float buf;
            Node temp = *it2;

            if((it2->i - curr.i) == 0 || (it2->j - curr.j)==0)
            {
                buf = curr.g + MOVE_COST_STR;
            }
            else
            {
                buf = curr.g + MOVE_COST_DIAG;
            }

            temp.h = Hfunc(temp, fin, EUCLID);

            if (close.find(temp.i * map.rows + temp.j)==close.end() && find(open.begin(), open.end(), temp)==open.end())
            {
                temp.g = buf;
                temp.f = temp.g + temp.h;
                temp.parent = &(close.find(curr.i*map.rows + curr.j)->second);
                open.push_back(temp);
            }
            else if (close.find(temp.i * map.rows + temp.j)!=close.end() && find(open.begin(), open.end(), temp)!=open.end())
            {

                list<Node>::iterator f = find(open.begin(), open.end(), temp);
                Node b = *f;

                Node *c = &(close.find(temp.i * map.rows + temp.j))->second;


                if (find(open.begin(), open.end(), temp)!=open.end() && buf <= b.g)
                {
                    b.g = buf;
                    b.f = b.g + b.h;
                    b.parent = &curr;
                }
                else if (close.find(temp.i * map.rows + temp.j)!=close.end() && buf <= c->g)
                {
                    close.erase(temp.i * map.rows + temp.j);
                    c->g = buf;
                    c->f = c->g + c->h;
                    c->parent = &curr;
                    open.push_back(*c);
                }
            }
            it2++;
        }

    }

    if(result.FoundPath == false)
    {
        cout<< "Not found" <<endl;
    }


    return result;

}


