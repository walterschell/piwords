#include "gen_val.h"
#include "piqpr8.h"
#include <stddef.h>

static int index = 1;
static unsigned char buffer = 0;
static size_t buffer_size = 0;
const static unsigned char top_5 = 0xf8;

static unsigned char get_mask();

int next_val(void)
{
    unsigned char temp = get_byte(index++);
    
    buffer &= (temp & get_mask(buffer_size)) >> buffer_size;

    unsigned char ret = buffer & get_mask(5);
    buffer = temp << (8 - buffer_size);
    buffer_size = (buffer_size + 5) % 8;

    return ret;
}

static unsigned char get_mask(size_t mask_size)
{
    return 0xff << (8 - mask_size);
}