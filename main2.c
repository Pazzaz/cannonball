#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    mpz_init_set_str(big, "10000", 10);
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
    mpz_set_str(Sbig, "6", 10);

    int array_size = 100000;
    mpz_t *large;
    large = malloc(array_size * sizeof(mpz_t));
    mpz_t *addition;
    addition = malloc(array_size * sizeof(mpz_t));
    mpz_t *addition2;
    addition2 = malloc(array_size * sizeof(mpz_t));

    // Starting with s = 5
    for(unsigned long i = 0;i < array_size; i++)
    {
        unsigned long b = (i*i*(i+1))*4;
        mpz_init_set_ui(large[i], b);
    }

    for(unsigned long i = 0;i < array_size; i++)
    {   
        mpz_init_set_ui(addition[i], 4*(( (i*i*i)-i)/3));
    }

    for(unsigned long i = 0;i < array_size; i++)
    {   
        mpz_init_set_ui(addition2[i], 8*(( (i*i*i)-i)/3));
    }
    // for(unsigned long i = 0;i < array_size; i++)
    // {   
    //     mpz_get_str(str1, 10, large[i]);
    //     printf("large before: %s\n", str1);
    // }
    printf("haha\n");
    for(char mod = 1;;mpz_add_ui(Sbig, Sbig, 1), mod++) {
        if(mod % 3 == 0) {
            mpz_add_ui(Sbig, Sbig, 1);
        }
        mpz_sub_ui(Sm2, Sbig, 2);
       

        mpz_sub_ui(Sm4, Sbig, 4);
        mpz_mul(Sm4tSm4, Sm4, Sm4);

        for (unsigned long j = 2; j < array_size; j++)
        {   
            if(mod % 3 == 0) {
                mpz_add(large[j], large[j], addition2[j]);
            } else {
                mpz_add(large[j], large[j], addition[j]);
            }

            mpz_mul(tmp1, large[j], Sm2);
            mpz_add(tmp1, tmp1, Sm4tSm4);

            if(mpz_perfect_square_p(tmp1)) {
                mpz_sqrt(tmp2, tmp1);
                mpz_add(tmp2, tmp2, Sm4);

                mpz_mul_ui(Sm2t2, Sm2, 2);
                if(mpz_divisible_p(tmp2, Sm2t2)) {
                    mpz_divexact_ui(tmp2, large[j], 8);
                    mpz_get_str(str2, 10, tmp2);
                    mpz_get_str(str3, 10, Sbig);
                    if (mpz_divisible_ui_p(Sm2, 3)) continue;
                    printf("sides: %s, height: %ld, count: %s\n", str3, j, str2);
                }
            }
        }
    }
    // for(unsigned long i = 0;i < array_size; i++)
    // {   
    //     mpz_get_str(str1, 10, large[i]);
    //     printf("large after: %s\n", str1);

    // }
    return 0;
}
