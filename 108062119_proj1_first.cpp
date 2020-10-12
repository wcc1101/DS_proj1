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
    //cout << "m: " << m << endl << "n: " << n << endl;
    height = m + 4;
    width = n;
    int **g = new int *[height];
    for (int i = 0; i < height; i++)
        g[i] = new int[width]{};
    return g;
}

void display(void)
{
    for (int i = 4; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << ground[i][j] << " ";
        cout << endl;
    }
}

bool collision(int r, int c)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if ((nowblock[i][j] && ground[r - 3 + i][c + j]) || r == height)
                return 1;
    return 0;
}

int drop(int r, int c)
{
    while (!collision(r + 1, c))
    {
        //cout << "now row: " << r + 1 << endl;
        r++;
    }
    return r;
}

void erase(int r, int c)
{
    //cout << r << endl;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (nowblock[i][j])
                ground[r - 3 + i][c + j] = 1;
    //display();
    int x = 0;
    for (int i = 3; i >= 0; i--)
    {
        //cout << "x: " << x << endl;
        int flag = 1;
        for (int j = 0; j < width; j++)
            if (!ground[r - 3 + i + x][j])
                flag = 0;
        if (flag)
        {
            //cout << "erase: " << r - 3 + i + x << endl;
            for (int j = 0; j < width; j++)
                ground[r - 3 + i + x][j] = 0;
            for (int o = r - 3 + i + x; o > 3; o--)
                for (int p = 0; p < width; p++)
                    ground[o][p] = ground[o - 1][p];
            //display();
            x++;
        }
    }
}

void start(void)
{
    string str;
    while (fin >> str)
    {
        //cout << str << endl;
        if (str == "End")
            break;
        else
        {
            int sp, st;
            fin >> sp >> st;
            //cout << sp << ' ' << st << endl;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    nowblock[i][j] = sets_pos[sets[str]][i][j];
                    //cout << nowblock[i][j];
                }
                //cout << endl;
            }
            int row = 4;
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
    //display();
    start();
    display();
}
