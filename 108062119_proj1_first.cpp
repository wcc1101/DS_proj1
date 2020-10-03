#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int m, n;
int **ground;

int main()
{
    ifstream fin;
    fin.open("testcase.txt");
    if (!fin)
        cout << "fail to input" << endl;

    fin.get(m); //rows
    fin.get(n); //cols
    ground = new int *[m];
    for (int i = 0; i < m; i++)
        ground[i] = new int[n]; //make m*n ground
}
