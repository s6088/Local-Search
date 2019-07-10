#include <bits/stdc++.h>
using namespace std;
#include "header/global.h"
#include "header/util.h"
#include "header/step1.h"
#include "header/step2.h"
#include "header/step3.h"

#define PLATEAU_LENGTH 100

int latinSquare[N][N], frequency[N][N], rows[N][N], clms[N][N];
int columnViolation[N], temp[N], swappable[N][N], rowViolation[N];
int localMinimum, globalMinimum, iteration, plateauLength, mxplateauLength;

void solve(int n)
{
    input(n);
    generateGrid(n);
    resetVeriables(n);

    globalMinimum = localMinimum;

    for (int i = 1; i <= n; i++)
        cout << i << ' ' << rowViolation[i] << endl;

    while (globalMinimum && iteration <= 1e8)
    {
        iteration++;
        int c1 = getViolatedClmRandomly(n);
        int r = getMaxViolatedRowGreedily(c1);
        int c2 = whomToSwapGreedily(r, c1);
        cellSwap(r, c1, c2);
        if (globalMinimum > localMinimum)
            globalMinimum = localMinimum, mxplateauLength = max(mxplateauLength, plateauLength), plateauLength = 0;
        else
            plateauLength++;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            rowViolation[i] += (frequency[j][latinSquare[i][j]] > 1);
        }
    for (int i = 1; i <= n; i++)
        cout << i << ' ' << rowViolation[i] << endl;
}

int main(int argc, char *argv[])
{
    freopen(argv[1], "r", stdin);
    clock_t timeStart = clock();
    srand(time(0));
    int n;
    cin >> n;
    n = atoi(argv[2]);
    solve(n);
    cout << fixed << setprecision(5) << globalMinimum << "\t" << (double)(clock() - timeStart) / CLOCKS_PER_SEC << "\t" << argv[1] << endl;
    cout << mxplateauLength << endl;
    isLatinSquare(n);
}
