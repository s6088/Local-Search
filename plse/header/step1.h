int getViolatedClmRandomly(int n)
{
    int mx = -inf, x = 0;
    for (int i = 1; i <= n; i++)
        if (columnViolation[i])
            temp[x++] = i;
    return temp[myRand(x) - 1];
}

int getMaxViolatedClm(int n)
{
    int mx = -inf, x = 0;
    for (int i = 1; i <= n; i++)
        if (columnViolation[i] > mx)
            x = 0, temp[x++] = i;
        else if (columnViolation[i] == mx)
            temp[x++] = i;
    return temp[myRand(x) - 1];
}

int getSecondMaxViolatedClm(int n)
{

    int mx1 = -inf, mx2 = -inf, x = 0;

    for (int i = 1; i <= n; i++)
    {
        if (columnViolation[i] > mx1)
        {
            mx2 = mx1;
            mx1 = columnViolation[i];
        }
        else if (columnViolation[i] > mx2 && columnViolation[i] != mx1)
        {
            mx2 = columnViolation[i];
        }
    }

    if (mx2 == -inf)
        mx2 = mx1;

    for (int i = 1; i <= n; i++)
    {
        if (columnViolation[i] == mx2)
        {
            temp[x++] = i;
        }
    }

    return temp[myRand(x) - 1];
}

int getMinViolatedClm(int n)
{
    int mn = inf, x = 0;
    for (int i = 1; i <= n; i++)
        if (columnViolation[i] && columnViolation[i] < mn)
            x = 0, temp[x++] = i;
        else if (columnViolation[i] == mn)
            temp[x++] = i;
    return temp[myRand(x) - 1];
}

int getViolatedClmByNovelty(int n, int p)
{

    int mx1 = -inf, mx2 = -inf, x = 0, r = myRand(100);

    for (int i = 1; i <= n; i++)
    {
        if (columnViolation[i] > mx1)
        {
            mx2 = mx1;
            mx1 = columnViolation[i];
        }
        else if (columnViolation[i] > mx2 && columnViolation[i] != mx1)
        {
            mx2 = columnViolation[i];
        }
    }

    if (r > p && mx2 != -inf)
        mx1 = mx2;

    for (int i = 1; i <= n; i++)
        if (columnViolation[i] == mx1)
            temp[x++] = i;

    return temp[myRand(x) - 1];
}
