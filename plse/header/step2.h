
int getMaxViolatedRowGreedily(int c)
{
    int mx = -inf, x = 0;
    for (int i = 1; i <= rows[c][0]; i++){
        int r = rows[c][i];
        if (clms[r][0] > 1)
        {
            int v = latinSquare[r][c];
            if (frequency[c][v] > mx)
                mx = frequency[c][v], x = 0, temp[x++] = r;
            else if (frequency[c][v] == mx)
                temp[x++] = r;
        }
    }
    return temp[myRand(x) - 1];
}



int getMaxViolatedRowByFixedPriority(int c, int n)
{
    int mx = -inf, x = 0;
    for (int i = 1; i <= rows[c][0]; i++){
        int r = rows[c][i];
        if (clms[r][0] > 1)
        {
            int v = latinSquare[r][c];
            if (frequency[c][v] > mx)
                mx = frequency[c][v], x = 0, temp[x++] = r;
            else if (frequency[c][v] == mx)
                temp[x++] = r;
        }
    }
    int temp4[x];
    for(int i=0; i<x; i++)temp4[i] =  fix[ temp[i] ];
    return temp[myRand(temp4, x)];
}




int getMaxViolatedRowGreedilyExceptTabu(int c, int n)
{
    int mx = -inf, x = 0;
    for (int i = 1; i <= rows[c][0]; i++){
        int r = rows[c][i];
        if (clms[r][0] > 1 && tabu[r][c]>iteration)
        {
            int v = latinSquare[r][c];
            if (frequency[c][v] > mx)
                mx = frequency[c][v], x = 0, temp[x++] = r;
            else if (frequency[c][v] == mx)
                temp[x++] = r;
        }
    }
    if(x==0)return rows[c][myRand( rows[c][0] )];
    return temp[myRand(x) - 1];
}


int getRowBestOfTheBest(int c){
    int mx = -inf, x = 0;
    for (int i = 1; i <= rows[c][0]; i++){
        int r = rows[c][i];
        if (clms[r][0] > 1)
        {
            int v = latinSquare[r][c];
            if (frequency[c][v] > mx)
                mx = frequency[c][v], x = 0, temp[x++] = r;
            else if (frequency[c][v] == mx)
                temp[x++] = r;
        }
    }
    return temp[myRand(x) - 1];
}