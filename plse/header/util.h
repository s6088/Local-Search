int cell (int r, int c, int n){
    return (n-1)*r + c;
}



inline int myRand(int n)
{
    return 1 + (rand() % n);
}

void generateGrid(int n)
{

    for (int i = 1; i <= n; i++)
    {

        memset(temp, 0, sizeof temp);

        for (int j = 1; j <= n; j++)
            if (swappable[i][j])
                temp[latinSquare[i][j]] = 1;

        int x = n;

        for (int j = 1; j <= n; j++)
            if (!swappable[i][j])
            {
                while (temp[x])
                    x--;
                latinSquare[i][j] = x;
                temp[x] = 1;
            }
    }
}

void resetVeriables(int n)
{

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            frequency[j][latinSquare[i][j]]++;
            


    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            rowViolation[i] += (frequency[j][ latinSquare[i][j] ] > 1);
            if (!frequency[i][j])
                localMinimum++, columnViolation[i]++;
        }

    
    
}

void input(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            string temp;
            cin >> temp;
            stringstream ss(temp);
            if (temp != "-")
            {
                ss >> latinSquare[i][j], swappable[i][j] = latinSquare[i][j];
            }
            else
            {
                rows[j][++rows[j][0]] = i;
                clms[i][++clms[i][0]] = j;
            }
        }
    }
}

inline int ifSwap(int r, int c1, int c2)
{
    int u = latinSquare[r][c1], v = latinSquare[r][c2];
    return (!(frequency[c1][v] + 1) + !(frequency[c2][u] + 1) + !(frequency[c2][v] - 1) + !(frequency[c1][u] - 1)) - (!frequency[c1][u] + !frequency[c1][v] + !frequency[c2][v] + !frequency[c2][u]);
}

inline void cellSwap(int r, int c1, int c2)
{
    int u = latinSquare[r][c1], v = latinSquare[r][c2];
    int cnt1 = -(!frequency[c1][u] + !frequency[c1][v]);
    int cnt2 = -(!frequency[c2][u] + !frequency[c2][v]);
    frequency[c1][u]--, frequency[c2][v]--, frequency[c1][v]++, frequency[c2][u]++;
    cnt1 += (!frequency[c1][u] + !frequency[c1][v]);
    cnt2 += (!frequency[c2][u] + !frequency[c2][v]);
    columnViolation[c1] += cnt1;
    columnViolation[c2] += cnt2;
    localMinimum += (cnt1 + cnt2);
    int tmp = latinSquare[r][c1];
    latinSquare[r][c1] = latinSquare[r][c2], latinSquare[r][c2] = tmp;
}


extern bool isLatinSquare(int n)
{
    set<int> r, c;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (latinSquare[i][j] < 1 || latinSquare[i][j] > n)
            {
                cout << "disaster" << endl;
                return false;
            }
            c.insert(latinSquare[j][i]);
            r.insert(latinSquare[i][j]);
            if (swappable[i][j] > 0 && swappable[i][j] != latinSquare[i][j])
            {
                cout << "fixed cell has changed" << endl;
                return false;
            }
        }
        if (r.size() != n || c.size() != n)
        {
            return false;
        }
        r.clear(), c.clear();
    }
    return true;
}


void randomStep(int r){
    int x = myRand(clms[r][0]);
    int y = myRand(clms[r][0]);
    cellSwap(r, clms[r][x], clms[r][y]);
}