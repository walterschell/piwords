#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <unistd.h>

static double expm(double p, double ak)
{
    int i, j;
    double p1, pt, r;
#define ntp 25
    static double tp[ntp];
    static int tp1 = 0;

    if (tp1 == 0)
    {
        tp1 = 1;
        tp[0] = 1.;

        for(i = 1; i < ntp; i++) tp[i] = 2. * tp[i-1];
    }

    if (ak == 1.) return 0.;

    for (i = 0; i < ntp; i++) if (tp[i] > p) break;

    pt = tp[i-1];
    p1 = p;
    r = 1.;

    for (j = 1; j <= i; j++){
      if (p1 >= pt){
        r = 16. * r;
        r = r - (int) (r / ak) * ak;
        p1 = p1 - pt;
      }
      pt = 0.5 * pt;
      if (pt >= 1.){
        r = r * r;
        r = r - (int) (r / ak) * ak;
      }
    }

    return r;
}

#define eps 1e-17

typedef struct
{
    int m;
    int k;
    double s;
}
ctx_t;

static double init_ctx(ctx_t *c, int m)
{
    c->m = m;
    c->k = 0;
    c->s = 0.;
}


static double series(ctx_t * c, int id)
{
    int k;
    double ak, p, s, t;

    if(c->k != id - 1)
    {
        abort();
    }

    ak = 8 * k + c->m;
    p = id - k;

    s = c->s;
    for(k = id; k <= id + 100; k++)
    {
        ak = 8 * k + c->m;
        t = pow(16., (double)(id - k)) / ak;
        if (t < eps) break;
        s = s + t;
        s = s - (int) s;
    }

    return s;
}
