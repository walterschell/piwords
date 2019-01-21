#ifndef GEN_VAL_H
#define GEN_VAL_H

#ifdef __cplusplus
extern "C" {
#endif

int init_vals(const char *file);
int next_val(int *p_good);
void deinit_vals(void);

#ifdef __cplusplus
}
#endif

#endif
