#include <iostream>
#include <list>
#include <unordered_map>
#include <math.h>
#include <limits.h>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

struct Node
{

    int i, j;
    double f, g, h;
    Node* parent;

    bool operator ==(const Node &comp) const
    {
        return (i == comp.i && j == comp.j);
    }
};


class Search
{
public:
    Search();
    ~Search();
    bool IsValid(int, int, int, int);
    bool IsObstacle(int, int, int**);
    double Hfunc(Node, Node);
    void Path(Node);
    list<Node> findSuccessors(Node, int**, int, int);
    void Astar(Node, Node, int**, int, int);

    list <Node> open;
    unordered_map <int, Node> close;
    list <Node> track;

    int rows, cols;
    int **p;
    Node start;
    Node fin;

};

Search::Search()
{

}

Search::~Search()
{

}

bool Search::IsValid(int i, int j, int rows, int cols)
{
    return ((i<rows) && (i>=0) && (j<cols) && (j>=0));
}

bool Search::IsObstacle(int i, int j, int *p[])
{
    return p[i][j] == 0;
}

double Search::Hfunc(Node curr, Node fin)
{
    return sqrt(pow(curr.i-fin.i,2) + pow(curr.j-fin.j,2));
}

void Search::Path(Node curr)
{
    while(curr.parent)
    {
        track.push_front(curr);
        curr = *curr.parent;
    }

    track.push_front(curr);
    cout<<"Trajectory: ";
    while(!track.empty())
    {
        Node temp = *track.begin();
        track.pop_front();
        cout << "->(" << temp.i << ", " << temp.j << ")";
    }
    cout<<endl;
    return;
}


list<Node> Search::findSuccessors(Node curr, int *p[], int rows, int cols)
{
    Node near;
    list<Node> successors;
    for (int k=-1; k<2; k++)
    {
        for (int l=-1; l<2; l++)
        {
            if (IsValid(curr.i + k, curr.j + l, rows, cols) && !IsObstacle(curr.i + k, curr.j + l, p) && (k!=0 || l!=0) && close.find((curr.i+k)*5 + curr.j+l)==close.end())
            {
                near.i = curr.i + k;
                near.j = curr.j + l;

                if(k==0 || l==0)
                {
                    near.g = curr.g + 0.5;
                }
                else
                {
                    near.g = curr.g + 0.71;
                }
                successors.push_front(near);
            }
        }
    }
    return successors;
}

void Search::Astar(Node start, Node fin, int *p[], int rows, int cols)
{
    Node curr;
    curr.i = start.i;
    curr.j = start.j;
    curr.g = 0.0;
    curr.h = Hfunc(curr, fin);
    curr.f = curr.g + curr.h;
    curr.parent = nullptr;

    open.push_back(curr);

    bool FoundPath = false;
    double gNew;


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
            FoundPath = true;
            Path(curr);
        }

        close.insert({curr.i*5 + curr.j, curr});

        list <Node> successors = findSuccessors(curr, p, rows, cols);
        list <Node> :: iterator it2 = successors.begin();

        while (it2!=successors.end())
        {
            if (it2->i == curr.i || it2->j == curr.j)
            {
                gNew = curr.g + 0.5;
            }
            else
            {
                gNew = curr.g + 0.71;
            }

            if (find(open.begin(), open.end(), curr)==open.end() || gNew <= it2->g)
            {
                it2->parent = &(close.find(curr.i*5 + curr.j)->second);
                it2->g = gNew;
                it2->h = Hfunc(*it2, fin);
                it2->f = it2->g + it2->h;
                open.push_back(*it2);
            }
            it2++;

        }

    }

    if(FoundPath == false)
    {
        cout<< "Meh" <<endl;
    }

}


int main()
{
    Node start, fin;
    start.i = 8;
    start.j = 0;
    fin.i = 0;
    fin.j = 0;
    int rows = 9, cols = 10;

    int map[rows][cols] = {{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                           { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                           { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                           { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                           { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                           { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }};

    int *p[rows];
    for (int i = 0; i < rows; i++)
    {
        p[i] = map[i];
    }

    Search search;
    search.Astar(start, fin, p, rows, cols);
}
