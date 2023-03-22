#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_pattern(uint16_t x)
{
    const uint16_t n = 0xFFFF;
    return (n ^ x) < (x & ~(x - 1));
}

bool is_pattern_orig(uint16_t x)
{
    if (!x)
        return 0;

    for (; x > 0; x <<= 1)
    {
        if (!(x & 0x8000))
            return false;
    }

    return true;
}

int main()
{
    int count = 0;
    for (int i = 0; i < 65536; i++)
    {
        int tmp = is_pattern(i);
        if(tmp)
        {
            printf("%d\n", i);
            count++;
        }
    }
    printf("%d\n", count);

    return 0;
}