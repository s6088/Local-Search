#include <bits/stdc++.h>
using namespace std;

int main (){
    freopen("o.txt", "r", stdin);
    int v, c = 0, x = 0, mn = INT_MAX, mx = INT_MIN;
    double t, avrgt = 0;
    char s [100], smn[100], smx[100];

    int tot = 0;
    while(scanf("%d %lf %s", &v, &t, s) != EOF){
        if(mn > v){
            mn = v;
            strcpy(smn, s);
        }
        if(mx < v){
            mx = v;
            strcpy(smx, s);
        }
        x += (v==0);
        tot += v;
        avrgt += t;
        c++;
    }

    // printf("%.3lf %.3lf",(double)(x*100)/c, (double)tot/c);

    printf("avrg time\t\t:\t\t%lf\nsucess rate\t\t:\t\t%.4lf\navrg vio\t\t:\t\t%.4lf\nminimum violation\t:\t\t%d %s\nmaximum violation\t:\t\t%d %s\n",  (double)avrgt/c, (double)(x*100)/c, (double)tot/c ,mn, smn, mx, smx);
    
}
