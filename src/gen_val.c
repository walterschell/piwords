#include "gen_val.h"
#include "piqpr8.h"
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static int __index = 1;
static uint16_t buffer = 0;
static size_t buffer_size = 0;

static uint16_t get_mask(size_t mask_size);

const char * binstring(uint16_t x)
{
    static char buf[17];
    memset(buf, '0', 16);
    buf[16] = 0;
    size_t index = 0;
    while(x > 0)
    {
        if(x & 0x8000)
        {
            buf[index] = '1';
        }
        x <<= 1;
        index++;
    }
    return buf;
}

int next_val(void)
{
    unsigned char ret;
    // printf("buffer: %s\t", binstring(buffer));
    // printf("buffer_size %lu;\t", buffer_size);

    if(buffer_size < 5)
    {
        uint16_t temp = get_byte(__index++);

        // printf("temp: %s;\t", binstring(temp));

        buffer |= (temp << (8 - buffer_size));

        //buffer <<= (8 - buffer_size);

        // printf("buffer: %s;\t", binstring(buffer));

        ret = (buffer & get_mask(5)) >> 8;

        buffer_size += 3;
    }
    else
    {
        ret = (buffer >> 8) & 0xf8;
        buffer_size -= 5;
        // printf("\t\t\t\t\t\t\t");
    }

    buffer <<= 5;
    ret >>= 3;

    // printf("ret: %s\n", binstring(ret));

    return ret;
}

static uint16_t get_mask(size_t mask_size)
{
    return (0xff << (16 - mask_size)) & 0xffff;
}
