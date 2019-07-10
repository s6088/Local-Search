#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
#define N 500
#define M 32

bool isLatinSquare (int n);
void input (int n);
int myRand (int n);
int cellNo (int r, int c, int n);
ii cellsToPair (int r, int c1, int c2, int n);
int ifSwap (int r, int c1, int c2, int n);
void init ();
void generateGrid (int n);
void resetVeriables (int n);
bool isPowerOfTwo(int n);
void preserveLatinSquare (int k, int n);
void copyLatinSquare (int k, int n);
void stepBack (int n);


int latinSquare [N][N];
int frequency[N][N];
int columnViolation[N];
int localMinimum, globalMinimum, iteration, myPlateauLength;
bool is[N], swaped[N][N];
int anik[N], test[N][N], tmp[N], swappable[N][N];
int dp [M][N][N];
map <ii, bool> tabu[M];

int  PLATEAU_LENGTH = 1500;


void mySwap (int r, int c1, int c2, int n){
    if(!swaped[r][c1] || !swaped[r][c2])return;
    int u = latinSquare[r][c1], v = latinSquare[r][c2];
    int cnt1 = -(!frequency[c1][u] + !frequency[c1][v]);
    int cnt2 = -(!frequency[c2][u] + !frequency[c2][v]);
    frequency[c1][u]--, frequency[c2][v]--,frequency[c1][v]++, frequency[c2][u]++;
    cnt1 += (!frequency[c1][u] + !frequency[c1][v]);
    cnt2 += (!frequency[c2][u] + !frequency[c2][v]);
    columnViolation[c1] += cnt1;
    columnViolation[c2] += cnt2;
    localMinimum += (cnt1+cnt2);
    if(isPowerOfTwo(iteration-1)){
        int k = log2(iteration-1);
        preserveLatinSquare(k, n);
        tabu[k][cellsToPair(r, c1, c2, n) ] = true;
    }
    swap(latinSquare[r][c1], latinSquare[r][c2]);
}


int getMaxViolatedClmNoRandomly (int n){
    int mx = 0, x = 0;
    if(myPlateauLength > PLATEAU_LENGTH){
        for(int i=1; i<=n; i++)if(columnViolation[i])anik[x++] = i;
        return anik[ myRand(x) - 1 ];
    }
    for(int i=1; i<=n; i++)if(mx < columnViolation[i])mx = columnViolation[i];
    for(int i=1; i<=n; i++)if(mx == columnViolation[i])anik[x++] = i;
    if(!x){
        stepBack(n);
        return -1;
    }
    return anik[ myRand(x) - 1 ];
}


int getMaxViolatedRowNoRandomly(int clm, int n){
    int mx = 0, x = 0;
    for(int i=1; i<=n; i++)if(swaped[i][clm] && mx <  frequency[clm][ latinSquare[i][clm] ])mx = frequency[clm][ latinSquare[i][clm] ];
    for(int i=1; i<=n; i++)if(swaped[i][clm] && frequency[clm][ latinSquare[i][clm] ]==mx)anik[x++] = i;
    if(!x){
        stepBack(n);
        return -1;
    }
    return anik[ myRand(x) - 1 ];
}



int whomToSwap (int r, int c, int n){
    int mn = INT_MAX, x = 0;
    for(int i=1; i<=n; i++)if(i!=c && swaped[r][i]  ){
        if(isPowerOfTwo(iteration) && tabu[(int)log2(iteration)].count( cellsToPair(r, c, n, n) ))continue;
        mn = min(mn, ifSwap(r, c, i, n));
    }
    for(int i=1; i<=n; i++)if(i!=c && swaped[r][i]  && mn==ifSwap(r, c, i, n)){
        if(isPowerOfTwo(iteration) && tabu[(int)log2(iteration)].count( cellsToPair(r, c, n, n) ))continue;
        anik[x++] = i;
    }
    if(!x){
        stepBack(n);
        return -1;
    }
    int c2 = anik[ myRand(x) - 1 ];
    return c2;
}


void stepBack (int n){
    
    int k = ceil(log2(iteration));
    k = max(k-6, 0);
    for(int i=k+1; i<M; i++)tabu[i].clear();
         copyLatinSquare(k, n);
         resetVeriables(n);
         iteration = 1<<(k);
         globalMinimum = localMinimum;
}




void solve(int n){

    input(n);

    clock_t timeStart = clock();
    generateGrid(n);
    resetVeriables(n);
    globalMinimum = localMinimum;
    int globalIteration = 0;

    int mn = INT_MAX;

    while(globalMinimum && globalIteration<1e5){
        globalIteration++;
        iteration++;
        if(PLATEAU_LENGTH>300 && iteration%100==0)PLATEAU_LENGTH--;

        int c = getMaxViolatedClmNoRandomly(n);
        int r = getMaxViolatedRowNoRandomly(c, n);
        int x = whomToSwap(r, c, n);
        
        mySwap(r, c, x, n);
        
        mn = min(globalMinimum, mn);
        
        
        if(globalMinimum > localMinimum)myPlateauLength = 0, globalMinimum = localMinimum;
        else myPlateauLength++;

        
        if(myPlateauLength > PLATEAU_LENGTH)stepBack(n), myPlateauLength = 0;

       // cout << mn << ' ' << globalMinimum << ":" << localMinimum << " - " <<  r << ' ' << c << " swap " << r << ' ' << x <<  endl;
        
    }





    printf("%d\t%.4lf\t\t%d\n", n, (double)(clock()-timeStart)/CLOCKS_PER_SEC, globalMinimum);
    if(!isLatinSquare(n))puts("-------------Not A Latin Square---------------");
    
   
}







int main (){

    freopen("i.txt", "r", stdin);
    //freopen("o.txt", "w", stdout);

    srand (time(0));

    int n;
    cin >> n;

    printf("n\ttime\t\tbest\n");
    solve(n);

    

}



bool isPowerOfTwo(int n) 
{ 
   return (ceil(log2(n)) == floor(log2(n))); 
}


void preserveLatinSquare (int k, int n){
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
    dp[k][i][j] = latinSquare[i][j];
}

void copyLatinSquare (int k, int n){
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
    latinSquare[i][j] = dp[k][i][j];
}

void resetVeriables (int n){
    init();
    for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                frequency[j][latinSquare[i][j]]++;

        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(!frequency[i][j])localMinimum++, columnViolation[i]++;
}

void init (){
    memset(frequency, 0, sizeof frequency);
    memset(columnViolation, 0, sizeof columnViolation);
    localMinimum = 0;
}



void generateGrid (int n){
    for(int i=1; i<=n; i++){
        memset(is, 0, sizeof is);
        for(int j=1; j<=n; j++)if(latinSquare[i][j])is[latinSquare[i][j]] = 1;
        for(int j=1; j<=n; j++){
            if(latinSquare[i][j])continue;
            int x = myRand(n);
            while(is[x])x = myRand(n);
            is[x] = 1;
            latinSquare[i][j] = x;
        }
    }
}




bool isLatinSquare (int n){
    set <int> r, c;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            c.insert(latinSquare[j][i]);
            r.insert(latinSquare[i][j]);
            if(swappable[i][j]>0 && swappable[i][j]!=latinSquare[i][j])return false;
        }
        if(r.size()!=n || c.size()!=n)return false;
        r.clear(), c.clear();
    }
    return true;
}


void input (int n){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            string temp;
            cin >> temp;
            stringstream ss(temp);
            if(temp != "-")ss >> latinSquare[i][j], swappable[i][j] = latinSquare[i][j];
            else swaped[i][j] = true;
        }
    }
}


int myRand (int n){
    return 1 + (rand()%n);
}

int cellNo (int r, int c, int n){
    return (n-1)*r + c;
}

ii cellsToPair (int r, int c1, int c2, int n){
    int x = cellNo(r, c1, n), y = cellNo(r, c2, n);
    if(x > y)swap(x, y);
    return ii(x, y);
}


int ifSwap (int r, int c1, int c2, int n){
    int u = latinSquare[r][c1], v = latinSquare[r][c2];
    return (!(frequency[c1][v]+1) + !(frequency[c2][u]+1) + !(frequency[c2][v]-1) + !(frequency[c1][u]-1)) - (!frequency[c1][u] + !frequency[c1][v] + !frequency[c2][v] + !frequency[c2][u]);
}
