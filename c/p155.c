//https://projecteuler.net/problem=155
//Counting Capacitor Circuits

#include <stdio.h>
#include <stdlib.h>
#define N 18

typedef struct frac {
    long p;
    long q;
} frac;


long gcd(long a, long b) { 
    if (!b) return a;
    return gcd(b,a%b);
}

int frac_cmp(const void *A, const void *B) {
    const frac *x = A, *y = B;
    long L = x->p * y->q;
    long R = y->p * x->q;
    if(L < R) return -1;
    if(L > R) return 1;
    return 0;
}

int main(void) {
    frac **solset = malloc((N+1)*sizeof(frac*));
    int *sol = malloc((N+1)*sizeof(int));

    solset[1] = malloc(sizeof(frac));
    solset[1][0].p = 1; solset[1][0].q = 1; sol[1] = 1;

    frac *all = malloc(sizeof(frac));
    all[0].p = 1; all[0].q = 1;
    int all_n = 1;

    for(int k = 2; k <= N; ++k){
        int tmp_cap = 0; //size of memory needed
        for(int i = 1; i <= k/2; ++i){
            int j = k - i;
            int ai = sol[i], aj = sol[j];
            if (ai == 0 || aj == 0) continue;
            if (i == j) tmp_cap += (ai * (ai + 1) / 2) * 2;
            else tmp_cap += ai * aj * 2;
        }
        frac *tmp = malloc(sizeof(frac) * tmp_cap);
        int tn = 0;

        for(int i = 1; i <= k/2; ++i){
            int j = k - i;
            for(int a = 0; a < sol[i]; a++){
                int bstart = (i == j) ? a : 0;
                for(int b = bstart; b < sol[j]; b++){
                    frac s = {solset[i][a].p * solset[j][b].q + solset[j][b].p * solset[i][a].q, solset[i][a].q * solset[j][b].q};
                    long g = gcd(s.p, s.q); s.p /= g; s.q /= g;
                    tmp[tn++] = s;
                    frac p = {solset[i][a].p * solset[j][b].p, solset[i][a].p * solset[j][b].q + solset[j][b].p * solset[i][a].q};
                    g = gcd(p.p, p.q); 
                    p.p /= g;
                    p.q /= g;
                    tmp[tn++] = p;
                }
            }
        }

        //sort to remove duplicates
        qsort(tmp, tn, sizeof(frac), frac_cmp);
        //count unique
        int unique = 0;
        for(int t = 0; t < tn; t++) if(t == 0 || frac_cmp(&tmp[t], &tmp[t-1]) != 0) unique++;
        solset[k] = malloc(sizeof(frac) * unique);
        sol[k] = unique;
        int idx = 0;
        for(int t = 0; t < tn; t++) if(t == 0 || frac_cmp(&tmp[t], &tmp[t-1]) != 0) solset[k][idx++] = tmp[t];
        free(tmp);

        frac *merged = malloc(sizeof(frac) * (all_n + sol[k]));
        int ia = 0, ib = 0, im = 0;
        while(ia < all_n || ib < sol[k]){
            if(ia == all_n) merged[im++] = solset[k][ib++];
            else if(ib == sol[k]) merged[im++] = all[ia++];
            else {
                int c = frac_cmp(&all[ia], &solset[k][ib]);
                if(c < 0) merged[im++] = all[ia++];
                else if(c > 0) merged[im++] = solset[k][ib++];
                else { merged[im++] = all[ia++]; ib++; }
            }
        }
        free(all);
        all = merged;
        all_n = im;
    }

    printf("%d\n", all_n);

    for(int k = 1; k <= N; ++k) free(solset[k]);
    free(solset); free(sol); free(all);
    return 0;
}
