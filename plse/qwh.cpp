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

int tabu[N][N];

void solve(int n)
{
    input(n);
    generateGrid(n);
    resetVeriables(n);

    globalMinimum = localMinimum;

    while (globalMinimum && iteration <= 1e7)
    {
        iteration++;
        int c1 = getViolatedClmRandomly(n);
        int r = getMaxViolatedRowGreedily(c1);
        int c2 = whomToSwapGreedily(r, c1);
        cellSwap(r, c1, c2);
        if (globalMinimum > localMinimum)
            globalMinimum = localMinimum, mxplateauLength = max(mxplateauLength, plateauLength), plateauLength = 0;
        else{
            tabu[r][c1] = iteration + 10;
            tabu[r][c1] = iteration + 10;
            plateauLength++;
        }
    }

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
    isLatinSquare(n);
}
