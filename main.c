#include <gmp.h>
#include <stdio.h>



void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, mpz_t a, mpz_t b)
{
    mpz_t x1, y1, u ,v, q, r, m, n, aux1, aux2;
    mpz_inits(x1, y1, u, v, q, r, m, n, aux1, aux2, NULL);
    mpz_set_ui(x1, 0);
    mpz_set_ui(y1, 1);
    mpz_set_ui(u, 1);
    mpz_set_ui(v, 0);

    while(mpz_cmp_ui(a, 0) != 0)
    {
        mpz_tdiv_qr(q, r, b, a);
        mpz_mul(aux1, u, q);
        mpz_sub(aux2, x1, aux1);
        mpz_set(m, aux2);
        mpz_mul(aux1, v, q);
        mpz_sub(aux2, y1, aux1);
        mpz_set(n, aux2);
        mpz_set(b, a);
        mpz_set(a, r);
        mpz_set(x1, u);
        mpz_set(y1, v);
        mpz_set(u, m);
        mpz_set(v, n);
    }
    mpz_set(g, b);
    mpz_set(x, x1);
    mpz_set(y, y1);
}

int inverso_modular(mpz_t r, mpz_t a, mpz_t n)
{
    mpz_t g, x, y;
    mpz_inits(g, x, y , NULL);
    mdc_estendido(g, x, y, a, n);

    if(mpz_cmp_ui(g, 1) == 0)
    {
        mpz_set(r, x);
        return 1;
    }
    return 0;
}



void mdc(mpz_t g,
                             mpz_t a,  mpz_t b)
{
    mpz_t q, r;
    mpz_inits(q, r, NULL);
    

    while(mpz_cmp_ui(b, 0) != 0)
    {
        mpz_tdiv_r(r, a, b);
        gmp_printf("resto: %Zd\n", r);
        mpz_set(a, b);
        gmp_printf("a = %Zd\n", a);
        mpz_set(b, r);
        gmp_printf("b = %Zd\n", b);

    }
    mpz_set(g, a);
}


void main()
{
    mpz_t a, b, x, y, g, r;
    mpz_inits(a, b, g, x, y, r, NULL);
    gmp_scanf("%Zd %Zd", a, b);
    if(inverso_modular(r, a, b))
    {
        gmp_printf("inverso modular = %Zd\n", r);

    }
    else
        gmp_printf("nao existe inverso modular\n");
}