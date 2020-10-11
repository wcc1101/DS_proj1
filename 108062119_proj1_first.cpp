#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

int **ground, width, length;
int nowblock[4][4];
ifstream fin;

int sets_pos[19][4][4] =
    {
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}},
        {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}},
        {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}},
        {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}},
        {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}},
        {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}},
        {{0, 0, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}},
        {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}},
        {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}},
        {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}}};

map<string, int> sets{
    {"T1", 0},
    {"T2", 1},
    {"T3", 2},
    {"T4", 3},
    {"L1", 4},
    {"L2", 5},
    {"L3", 6},
    {"L4", 7},
    {"J1", 8},
    {"J2", 9},
    {"J3", 10},
    {"J4", 11},
    {"S1", 12},
    {"S2", 13},
    {"Z1", 14},
    {"Z2", 15},
    {"I1", 16},
    {"I2", 17},
    {"O", 18}};

int **set(void)
{
    fin.open("testcase.txt");
    if (!fin)
        cout << "fail reading testcase" << endl;

    int m, n;
    fin >> m >> n;
    length = m;
    width = n;
    int **g = new int *[m];
    for (int i = 0; i < m; i++)
        g[i] = new int[n]{};
    return g;
}

void display(void)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
            cout << ground[i][j] << " ";
        cout << endl;
    }
}

class point
{
public:
    point(int x = 0, int y = 0) : x(x), y(y) {}
    ~point() {}
    int x, y;
};

class blocks
{
public:
    blocks(int x = 0, int y = 0, string k = 0) : kind(k)
    {
        refpoint.x = x;
        refpoint.y = y;
    }
    point refpoint;
    string kind;
    point *array;
};

void start(void)
{
    string str;
    while (fin >> str)
    {
        if (str == "End")
            break;
        else
        {
            int px, py;
            fin >> px >> py;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    nowblock[i][j] = sets_pos[sets[str]][i][j];
        }
    }
}

int main()
{
    ground = set();
    display();
    start();
}
