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
void mySwap (int r, int c1, int c2, int n);
void jumpBack (int k, int n);
double similarity (int k, int n);


int latinSquare [N][N];
int frequency[N][N];
int columnViolation[N];
int localMinimum, globalMinimum, psudoGlobalMinimum, psudoIteration, iteration, simi;
int tmp[N], swappable[N][N];
int save [M][N][N], savedGlobal[M];
map <ii, bool> tabu[M];




int getMaxViolatedClmNoRandomly (int n){
    int mx = 0, x = 0;
    for(int i=1; i<=n; i++)if(mx < columnViolation[i])mx = columnViolation[i];
    for(int i=1; i<=n; i++)if(mx == columnViolation[i])tmp[x++] = i;
    if(!x)return -1;
    return tmp[ myRand(x) - 1 ];
}


int getMaxViolatedRowNoRandomly(int clm, int n){
    int mx = 0, x = 0;
    for(int i=1; i<=n; i++)if(swappable[i][clm]==0 && mx <  frequency[clm][ latinSquare[i][clm] ])mx = frequency[clm][ latinSquare[i][clm] ];
    for(int i=1; i<=n; i++)if(swappable[i][clm]==0 && frequency[clm][ latinSquare[i][clm] ]==mx)tmp[x++] = i;
    if(!x)return -1;
    return tmp[ myRand(x) - 1 ];
}



int whomToSwap (int r, int c, int n){
    int mn = INT_MAX, x = 0;
    for(int i=1; i<=n; i++)if(i!=c && swappable[r][i]==0){
        if(isPowerOfTwo(psudoIteration) && tabu[(int)log2(psudoIteration)].count( cellsToPair(r, c, n, n) ))continue;
        mn = min(mn, ifSwap(r, c, i, n));
    }
    for(int i=1; i<=n; i++)if(i!=c && swappable[r][i]==0  && mn==ifSwap(r, c, i, n)){
        if(isPowerOfTwo(psudoIteration) && tabu[(int)log2(psudoIteration)].count( cellsToPair(r, c, n, n) ))continue;
        tmp[x++] = i;
    }
    if(!x) return -1;
    return tmp[ myRand(x) - 1 ];
}





void solve(int n){

    input(n);

    clock_t timeStart = clock();
    generateGrid(n);
    resetVeriables(n);
    globalMinimum = psudoGlobalMinimum = localMinimum;

    

    while(globalMinimum && iteration<1e6){

        psudoIteration++, iteration++;
        cout << iteration << ' ' << globalMinimum << endl;
        int c = getMaxViolatedClmNoRandomly(n);
        if(c==-1)cout << "--------------------------------------------------------------------------------------------" << endl;
        int r = getMaxViolatedRowNoRandomly(c, n);
        if(r==-1)cout << "--------------------------------------------------------------------------------------------" << endl;
        int x = whomToSwap(r, c, n);
        if(x==-1)cout << "--------------------------------------------------------------------------------------------" << endl;
        
        mySwap(r, c, x, n);
        psudoGlobalMinimum = min(psudoGlobalMinimum, localMinimum);
        globalMinimum = min(globalMinimum, psudoGlobalMinimum);

/*
        if(psudoIteration>64 && isPowerOfTwo(psudoIteration) && similarity(log2(psudoIteration)-1, n)>99.9){
           jumpBack(log2(psudoIteration)-4, n);
        }
*/
        
    }





    printf("%d\t%.4lf\t\t%d\n", n, (double)(clock()-timeStart)/CLOCKS_PER_SEC, globalMinimum);
    if(!isLatinSquare(n))puts("-------------No Solution Found---------------");
    
   
}







int main (){

    freopen("i.txt", "r", stdin);

    srand (time(0));

    int n;
    cin >> n;

    printf("n\ttime\t\tbest\n");
    solve(n);


}



void jumpBack (int k, int n){
    for(int i=k+1; i<M; i++)tabu[i].clear();
    copyLatinSquare(k, n);
    resetVeriables(n);
    psudoIteration = 1<<(k);
    globalMinimum = savedGlobal[k];
}

double similarity (int k, int n){
    int cnt = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cnt += (latinSquare[i][j] == save[k][i][j]);
        }
    }
    double x = cnt, y = n*n;
    return (x*100.0)/y;
}




void mySwap (int r, int c1, int c2, int n){
    if(swappable[r][c1]>0 || swappable[r][c2]>0)return;
    int u = latinSquare[r][c1], v = latinSquare[r][c2];
    int cnt1 = -(!frequency[c1][u] + !frequency[c1][v]);
    int cnt2 = -(!frequency[c2][u] + !frequency[c2][v]);
    frequency[c1][u]--, frequency[c2][v]--,frequency[c1][v]++, frequency[c2][u]++;
    cnt1 += (!frequency[c1][u] + !frequency[c1][v]);
    cnt2 += (!frequency[c2][u] + !frequency[c2][v]);
    columnViolation[c1] += cnt1;
    columnViolation[c2] += cnt2;
    localMinimum += (cnt1+cnt2);
    if(isPowerOfTwo(psudoIteration-1)){
        int k = log2(psudoIteration-1);
        preserveLatinSquare(k, n);
        savedGlobal[k] = globalMinimum;
        tabu[k][ cellsToPair(r, c1, c2, n) ] = true;
    }
    swap(latinSquare[r][c1], latinSquare[r][c2]);
}



bool isPowerOfTwo(int n) 
{ 
   return (ceil(log2(n)) == floor(log2(n))); 
}


void preserveLatinSquare (int k, int n){
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
    save[k][i][j] = latinSquare[i][j];
}

void copyLatinSquare (int k, int n){
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
    latinSquare[i][j] = save[k][i][j];
}

void resetVeriables (int n){
    init();
    for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                frequency[j][latinSquare[i][j]]++;

        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(!frequency[i][j])localMinimum++, columnViolation[i]++;
                
    psudoIteration = 0;
}



void init (){
    memset(frequency, 0, sizeof frequency);
    memset(columnViolation, 0, sizeof columnViolation);
    localMinimum = 0;
}



void generateGrid (int n){
    for(int i=1; i<=n; i++){
        memset(tmp, 0, sizeof tmp);
        for(int j=1; j<=n; j++)if(latinSquare[i][j])tmp[latinSquare[i][j]] = 1;
        for(int j=1; j<=n; j++){
            if(latinSquare[i][j])continue;
            int x = myRand(n);
            while(tmp[x])x = myRand(n);
            tmp[x] = 1;
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
            if(swappable[i][j]>0 && swappable[i][j]!=latinSquare[i][j]){
                cout << "fix position has been distrubed" << endl;
                return false;
            }
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


//if i swap (r,c1) with (r,c2) then it returns (postSwapVio - preSwapVio) 
int ifSwap (int r, int c1, int c2, int n){
    int u = latinSquare[r][c1], v = latinSquare[r][c2];
    return ( !(frequency[c2][v]-1) + !(frequency[c1][u]-1)) - (!frequency[c1][u] + !frequency[c1][v] + !frequency[c2][v] + !frequency[c2][u]);
}
