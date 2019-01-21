#include "gen_val.h"
#include "piqpr8.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <mpfr.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PERCITION 10000000

static char * g_digits = NULL;
static size_t g_d_index = 0;
static size_t g_max_digits = 0;

int init_vals(const char *filename)
{
    FILE *fin = fopen(filename, "r");
    mpfr_t number;
    mpfr_exp_t exp;
    mpfr_init2(number, PERCITION);
    mpfr_inp_str(number, fin, 10, MPFR_RNDN);
    g_digits = mpfr_get_str(NULL, &exp, 2, 0, number, MPFR_RNDN);
    g_max_digits = strlen(g_digits);
    g_d_index = 2; // move past "1."
    return 0;
}

int next_val(int *p_good)
{
    int ret = 0;
    int count = 5;

    while(count > 0 && g_d_index < g_max_digits)
    {
        ret = ret << 1;
        if(g_digits[g_d_index] == '1')
        {
            ret = ret | 0x01;
        }
        --count;
        ++g_d_index;
    }

    if(p_good)
    {
        *p_good = 1;
    }

    if(count == 0)
    {
       return ret;
    }
    else
    {
        if(p_good)
        {
            *p_good = 0;
        }
        return 0;
    }
}

void deinit_vals()
{
    if(g_digits)
        mpfr_free_str(g_digits);
}
