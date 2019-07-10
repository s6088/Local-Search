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
