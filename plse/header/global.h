#define N 100
#define inf 1e9

extern int latinSquare[N][N], frequency[N][N], rows[N][N], clms[N][N], swappable[N][N];
extern int columnViolation[N], rowViolation[N], temp[N];
extern int localMinimum, globalMinimum, iteration;
 
extern int tabu[N*N][N*N], fix[N], temp2[N];