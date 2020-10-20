#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;
int **ground, width, height;
int nowblock[4][4];
ifstream fin;
ofstream fout;
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
    for (int i = 4; i < height; i++)
    {
        fout << ground[i][0];
        for (int j = 1; j < width; j++)
            fout << " " << ground[i][j];
        fout << endl;
    }
}
bool collision(int r, int c)
{
    if (r == height)
        return 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (nowblock[i][j] && ground[r - 3 + i][c + j])
                return 1;
    return 0;
}
int drop(int r, int c)
{
    while (!collision(r + 1, c))
    {
        r++;
    }
    return r;
}
void erase(int r, int c)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (nowblock[i][j])
                ground[r - 3 + i][c + j] = 1;
    int x = 0;
    for (int i = 3; i >= 0; i--)
    {
        int flag = 1;
        for (int j = 0; j < width; j++)
            if (!ground[r - 3 + i + x][j])
                flag = 0;
        if (flag)
        {
            for (int j = 0; j < width; j++)
                ground[r - 3 + i + x][j] = 0;
            for (int o = r - 3 + i + x; o > 0; o--)
                for (int p = 0; p < width; p++)
                    ground[o][p] = ground[o - 1][p];
            x++;
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
            int row = 4;
            int col = sp - 1;
            row = drop(row, col);
            col += st;
            row = drop(row, col);
            erase(row, col);
        }
        display();
        fout << endl;
    }
}
int main(int argc, char *argv[])
{
    fin.open(argv[1]);
    if (!fin)
        cout << "fail reading testcase" << endl;
    fout.open("108062119_proj1.final");
    ground = set();
    start();
    display();
}