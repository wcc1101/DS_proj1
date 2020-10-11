#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

int **ground, width, height;
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
    height = m + 4;
    width = n;
    int **g = new int *[height];
    for (int i = 0; i < height; i++)
        g[i] = new int[width]{};
    return g;
}

void display(void)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << ground[i][j] << " ";
        cout << endl;
    }
}

int drop(int r, int c)
{
    while (!collision(r + 1, c))
    {
        r++;
    }
    return r;
}

bool collision(int r, int c)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (nowblock[i][j] && ground[r - 3 + i][c + j])
                return 1;
    return 0;
}

void erase(int r, int c)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (nowblock[i][j])
                ground[r - 3 + i][c + j] = 1;
    int flag = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < width; j++)
            if (!ground[r - 3 + i][j])
                flag = 0;
        if (flag)
        {
            for (int j = 0; j < width; j++)
                ground[r - 3 + i][j] = 0;
            for (int o = r - 3 + i; o > 3; o--)
                for (int p = 0; p < c; p++)
                    ground[o][p] = ground[o - 1][p];
        }
    }
}

void start(void)
{
    string str;
    while (fin >> str)
    {
        if (str == "End")
            break;
        else
        {
            int sp, st;
            fin >> sp >> st;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    nowblock[i][j] = sets_pos[sets[str]][i][j];
            int row = 0;
            int col = sp - 1;
            row = drop(row, col);
            col += st;
            row = drop(row, col);
            erase(row, col);
        }
    }
}

int main()
{
    ground = set();
    display();
    start();
}
