
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

int getMaxViolatedRowGreedilyExceptTabu(int c, int n)
{
    int mx = -inf, x = 0;
    for (int i = 1; i <= rows[c][0]; i++){
        int r = rows[c][i];
        if (clms[r][0] > 1 && tabu[cell()][cell()])
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


int getRowBestOfTheBest(int c){

}