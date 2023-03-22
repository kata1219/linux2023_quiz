#include <stdio.h>
#include <stdint.h>

uint64_t next_pow2_built_in(uint64_t x)
{
    return (1 << 64 - __builtin_clzl(x));
}

uint64_t next_pow2(uint64_t x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return ++x;
}

int main()
{
    printf("%ld\n", next_pow2(7));
    printf("%ld\n", next_pow2(13));
    printf("%ld\n", next_pow2(42));
}