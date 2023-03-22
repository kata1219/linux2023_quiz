#include <stdio.h>

int concatenatedBinary_built_in(int n)
{
    const int M = 1e9 + 7;
    int len = 0; /* the bit length to be shifted */
    /* use long here as it potentially could overflow for int */
    long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!(i ^ 1 << __builtin_ctz(i)))
        // if (__builtin_clz(i) + __builtin_ctz(i) == 31)
            len++;
        ans = (i | (ans << len)) % M;
    }
    return ans;
}

int concatenatedBinary(int n)
{
    const int M = 1e9 + 7;
    int len = 0; /* the bit length to be shifted */
    /* use long here as it potentially could overflow for int */
    long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        /* removing the rightmost set bit
         * e.g. 100100 -> 100000
         *      000001 -> 000000
         *      000000 -> 000000
         * after removal, if it is 0, then it means it is power of 2
         * as all power of 2 only contains 1 set bit
         * if it is power of 2, we increase the bit length
         */
        if (!(i ^ (i & ~(i - 1))))
            len++;
        ans = (i | (ans << len)) % M;
    }
    return ans;
}

int main()
{
    printf("%d\n", concatenatedBinary(1));
    printf("%d\n", concatenatedBinary(3));
    printf("%d\n", concatenatedBinary(12));
    // printf("%d\n", concatenatedBinary_built_in(1));
    // printf("%d\n", concatenatedBinary_built_in(3));
    // printf("%d\n", concatenatedBinary_built_in(12));
}