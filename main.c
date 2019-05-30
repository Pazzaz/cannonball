#include <gmp.h>
#include <stdio.h>

int main(void)
{
    char str1[100];
    char str2[100];
    char str3[100];
    char str4[100];
    mpz_t n;
    mpz_t Sbig;
    mpz_t tmp1;
    mpz_t tmp2;
    mpz_t tmp3;
    mpz_t sum;
    mpz_t big;
    mpz_t pns;
    mpz_t Sm2;
    mpz_t Sm4;
    mpz_t Sm4tSm4;
    mpz_t Sm2t8;
    mpz_t Sm2t2;
    mpz_init_set_str(big, "100000", 10);
    mpz_init(Sbig);
    mpz_init(pns);
    mpz_init(sum);
    mpz_init(n);
    mpz_init(tmp1);
    mpz_init(tmp2);
    mpz_init(tmp3);
    mpz_init(Sm2t8);
    mpz_init(Sm2);
    mpz_init(Sm4);
    mpz_init(Sm4tSm4);
    mpz_init(Sm2t2);
    mpz_set_str(Sbig, "5", 10);

    for(;;mpz_add_ui(Sbig, Sbig, 1)) {
        mpz_set_str(pns, "1", 10);
        mpz_set_str(sum, "1", 10);
        mpz_sub_ui(Sm2, Sbig, 2);
        mpz_mul_ui(Sm2t8, Sm2, 8);
        mpz_mul(sum, sum, Sm2t8);
        mpz_set_ui(n, 1);
        mpz_sub_ui(Sm4, Sbig, 4);
        mpz_mul(Sm4tSm4, Sm4, Sm4);
        mpz_mul_ui(Sm2t2, Sm2, 2);
        for(;mpz_cmp(n, big); mpz_add_ui(n, n, 1)) {
            // Skip when we have solutions: S = 3n+2
            if (mpz_divisible_ui_p(Sm2, 3)) break;
            // pns = n(S-2)+1+pns
            mpz_mul(tmp1, n, Sm2);
            mpz_add_ui(tmp1, tmp1, 1);
            mpz_add(pns, tmp1, pns);

            // sum = sum+pns*8*(S-2)
            mpz_mul(tmp2, pns, Sm2t8);
            mpz_add(sum, sum, tmp2);

            mpz_add(tmp2, sum, Sm4tSm4);

            if(mpz_perfect_square_p(tmp2)) {
                mpz_sqrt(tmp2, tmp2);
                mpz_add(tmp2, tmp2, Sm4);
                if(mpz_divisible_p(tmp2, Sm2t2)) {
                    mpz_get_str(str1, 10, n);
                    mpz_divexact(tmp3, sum, Sm2t8);
                    mpz_get_str(str2, 10, tmp3);
                    mpz_get_str(str3, 10, Sbig);
                    mpz_get_str(str4, 10, n);
                    printf("sides: %s height: %s, count: %s, n: %s\n", str3, str1, str2, str4);
                }
            }
        }

    }
    return 0;
}
