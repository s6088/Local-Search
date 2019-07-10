#include <bits/stdc++.h>
using namespace std;
#define N 5000

///describe the current latin square
int latsq [N][N];
///frequency[i][j] tells how many j in column i
int frequency[N][N];
///columnViolation[i] represent violation of column i
int columnViolation[N];

int localMinimum, globalMinimum, iteration;
bool is[N];
int anik[N];

/*
calculating the violation
there can be many way to calculate the violation
my approach : counting the number of values having frequency 0 in a column
suppose for n=3 in ith column, frequency[i][1] = 1, frequency[i][2] = 0, frequency[i][3] = 2
only the value 2 has frequency 0, so the column frequency is 1
*/

///simple function to get a number between 1 to n inclusive randomly
int myRand (int n){
    return 1 + (rand()%n);
}

///display the grid
void printSquare(int n){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            printf("%d ", latsq[i][j]);
        }
        puts("");
    }
}
///calculate the violation difference if swap latsq[r][c1], latsq[r][c2]
int ifSwap (int r, int c1, int c2, int n){
    int u = latsq[r][c1], v = latsq[r][c2];
    return (!(frequency[c1][v]+1) + !(frequency[c2][u]+1) + !(frequency[c2][v]-1) + !(frequency[c1][u]-1)) - (!frequency[c1][u] + !frequency[c1][v] + !frequency[c2][v] + !frequency[c2][u]);
}

/*
swap latsq[row][clm1], latsq[row][clm2]
and also adjuct all columnViolation as well as totalViolation
its a restoring process, if we apply it even time in our latin square all the variables get no change
since we using incremental operation it will take no time or constant time
*/
void mySwap (int r, int c1, int c2, int n){
    int u = latsq[r][c1], v = latsq[r][c2];
    if(u==v)return;
    int cnt1 = -(!frequency[c1][u] + !frequency[c1][v]);
    int cnt2 = -(!frequency[c2][u] + !frequency[c2][v]);
    frequency[c1][u]--, frequency[c2][v]--,frequency[c1][v]++, frequency[c2][u]++;
    cnt1 += (!frequency[c1][u] + !frequency[c1][v]);
    cnt2 += (!frequency[c2][u] + !frequency[c2][v]);
    columnViolation[c1] += cnt1;
    columnViolation[c2] += cnt2;
    localMinimum += (cnt1+cnt2);
    swap(latsq[r][c1], latsq[r][c2]);
}


///choosing a column randomly among those where column violation is maximum
int getMaxViolatedClmNoRandomly (int n){
    int mx = 0, x = 0;
    for(int i=1; i<=n; i++)if(mx < columnViolation[i])mx = columnViolation[i];
    for(int i=1; i<=n; i++)if(mx == columnViolation[i])anik[x++] = i;
    return anik[ myRand(x) - 1 ];
}


///choosing a row for a specific column, where frequency of the cell value is maximum
int getMaxViolatedRowNoRandomly(int clm, int n){
    int mx = 0, x = 0;
    for(int i=1; i<=n; i++)if(mx <  frequency[clm][i])mx = frequency[clm][i];
    for(int i=1; i<=n; i++)if(frequency[clm][ latsq[i][clm]  ]==mx)anik[x++] = i;
    return anik[ myRand(x) - 1 ];
}



///find a good latsq[r][?] for latsq[r][c] to swap
int whomToSwap (int r, int c, int n){
    int mn = INT_MAX, x = 0;
    for(int i=1; i<=n; i++)if(i!=c)mn = min(mn, ifSwap(r, c, i, n));
    for(int i=1; i<=n; i++)if(i!=c && mn==ifSwap(r, c, i, n))anik[x++] = i;
    return anik[ myRand(x) - 1 ];
}


///clearing all variables
void init (){
    memset(frequency, 0, sizeof frequency);
    memset(columnViolation, 0, sizeof columnViolation);
    localMinimum = 0;
    iteration = 0;
}

/*
filling the grid
we will ensure a row gets n distinct value every time, such row violation always 0 [hard constraint]
so there exist only column violation [soft constraints]
*/
void generateGrid (int n){
    for(int i=1; i<=n; i++){
        memset(is, 0, sizeof is);
        for(int j=1; j<=n; j++){
            int x = myRand(n);
            while(is[x])x = myRand(n);
            is[x] = 1;
            latsq[i][j] = x;
        }
    }
}

///check the final latin square is ok or not
bool isLatinSquare (int n){
    for(int i=1; i<=n; i++){
        memset(is, 0, sizeof is);
        for(int j=1; j<=n; j++){
            int x = latsq[j][i];
            if(is[x])return false;
            is[x] = 1;
        }
    }
    return true;
}


void solve(int n){
    clock_t timeStart = clock();
    init();
    generateGrid(n);

    /// we do the o(n^2) calculation just one time..one time, then we app;y incremental approach
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            frequency[j][latsq[i][j]]++;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(!frequency[i][j])localMinimum++, columnViolation[i]++;

    globalMinimum = localMinimum;


    while(localMinimum){
        int c = getMaxViolatedClmNoRandomly(n);
        int r = getMaxViolatedRowNoRandomly(c, n);
        int x = whomToSwap(r, c, n);
        mySwap(r, c, x, n);
        globalMinimum = min(globalMinimum, localMinimum);
        iteration++;
    }
    printf("%d\t%.4lf\t\t%d\n", n, (double)(clock()-timeStart)/CLOCKS_PER_SEC, iteration);
    if(!isLatinSquare(n))puts("-------------Wrong Calculation---------------");
   
}

int main (){

    srand (time(0));

    int n;
    scanf("%d", &n);

    printf("n\ttime\t\titeration\n");
    solve(n);
   
    

}