int whomToSwapGreedily(int r, int c1)
{
    int mn = inf, x = 0;
    for (int i = 1; i <= clms[r][0]; i++){
        int c2 = clms[r][i];
        if (c2 != c1)
        {
            int v = ifSwap(r, c1, c2);
            if (v < mn)
                mn = v, x = 0, temp[x++] = c2;
            else if (v == mn)
                temp[x++] = c2;
        }
    }
    return temp[myRand(x) - 1];
}


int whomToSwapGreedilyExceptTabu(int r, int c1, int n)
{
    int mn = inf, x = 0;
    for (int i = 1; i <= clms[r][0]; i++){
        int c2 = clms[r][i];
        if (c2 != c1 && tabu[cellNo(r, c1, n)][latinSquare[r][c2]]<iteration  && tabu[cellNo(r, c2, n)][latinSquare[r][c1]]<iteration)
        {
            int v = ifSwap(r, c1, c2);
            if (v < mn)
                mn = v, x = 0, temp[x++] = c2;
            else if (v == mn)
                temp[x++] = c2;
        }
    }
    if(x==0)return clms[r][myRand( clms[r][0] )];
    return temp[myRand(x) - 1];
}
