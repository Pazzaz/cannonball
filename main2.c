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
    mpz_t tmp1;
    mpz_t tmp2;
    mpz_t tmp3;
    mpz_init(tmp1);
    mpz_init(tmp2);
    mpz_init(tmp3);
    unsigned long S = 5;
    unsigned long Sm2 = S-2;
    unsigned long Sm4 = S-4;

    int array_size = 1000;
    printf("array size: %d\n", array_size);
    mpz_t *large;
    large = malloc(array_size * sizeof(mpz_t));
    unsigned long addition[array_size];
    unsigned long addition2[array_size];

    // Starting with s = 5
    for(unsigned long i = 0;i < array_size; i++)
    {
        unsigned long b = (i*i*(i+1))*4;
        mpz_init_set_ui(large[i], b);
    }

    for(unsigned long i = 0;i < array_size; i++)
    {   
        addition[i] = 4*(( (i*i*i)-i)/3);
    }

    for(unsigned long i = 0;i < array_size; i++)
    {   
        addition2[i] = 8*(( (i*i*i)-i)/3);
    }
    for(char mod = 0;; mod++) {
        char skip = 0;
        if (mod == 2) {
            S += 2;
            Sm2 += 2;
            Sm4 += 2;
            mod = 0;
            skip = 1;
        } else {
            S += 1;
            Sm2 += 1;
            Sm4 += 1;
        }
        if (S>>32) {
            return 1;
        }
        unsigned long Sm4tSm4 = Sm4*Sm4;

        for (unsigned long j = 2; j < array_size; j++)
        {   
            if (skip) {
                mpz_add_ui(large[j], large[j], addition2[j]);
            } else {
                mpz_add_ui(large[j], large[j], addition[j]);
            }
        
            mpz_mul_ui(tmp1, large[j], Sm2);
            mpz_add_ui(tmp1, tmp1, Sm4tSm4);

            if(mpz_perfect_square_p(tmp1)) {
                mpz_sqrt(tmp2, tmp1);
                mpz_add_ui(tmp2, tmp2, Sm4);

                printf("current progress: %ld\n", S);
                unsigned long Sm2t2 = Sm2*2;
                if(mpz_divisible_ui_p(tmp2, Sm2t2)) {
                    mpz_divexact_ui(tmp2, large[j], 8);
                    mpz_get_str(str2, 10, tmp2);
                    printf("sides: %ld, height: %ld, count: %s\n", S, j, str2);
                }
            }
        }
    return 0;
}