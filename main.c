#include <gmp.h>
#include <stdio.h>



void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b)
{
    mpz_t x1, y1, u ,v, q, r, m, n, aux1, aux2, a1, b1;
    mpz_inits(x1, y1, u, v, q, r, m, n, aux1, aux2, a1, b1, NULL);
    mpz_set_ui(x1, 0);
    mpz_set_ui(y1, 1);
    mpz_set_ui(u, 1);
    mpz_set_ui(v, 0);
    mpz_set(a1, a);
    mpz_set(b1, b);

    while(mpz_cmp_ui(a1, 0) != 0)
    {
        mpz_tdiv_qr(q, r, b1, a1);
        mpz_mul(aux1, u, q);
        mpz_sub(aux2, x1, aux1);
        mpz_set(m, aux2);
        mpz_mul(aux1, v, q);
        mpz_sub(aux2, y1, aux1);
        mpz_set(n, aux2);
        mpz_set(b1, a1);
        mpz_set(a1, r);
        mpz_set(x1, u);
        mpz_set(y1, v);
        mpz_set(u, m);
        mpz_set(v, n);
    }
    mpz_set(g, b1);
    mpz_set(x, x1);
    mpz_set(y, y1);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n)
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



void mdc(mpz_t g, const mpz_t a, const mpz_t b)
{
    mpz_t q, r, a1, b1;
    mpz_inits(q, r, NULL);
    mpz_set(a1, a);
    mpz_set(b1, b);
    

    while(mpz_cmp_ui(b1, 0) != 0)
    {
        mpz_tdiv_r(r, a1, b1);
        mpz_set(a1, b1);
        mpz_set(b1, r);
    }
    mpz_set(g, a1);
}


void main()
{
    mpz_t a, b, x, y, g, r;
    mpz_inits(a, b, g, x, y, r, NULL);
    gmp_scanf("%Zd %Zd", a, b);
    mdc_estendido(g, x, y, a, b);
    gmp_printf("(%Zd)*(%Zd) + (%Zd)*(%Zd) = mdc(%Zd,%Zd) = %Zd\n",
                                                     x, a, y, b, a, b, g);
    if(inverso_modular(r, a, b))
    {
        gmp_printf("Inverso modular = %Zd\n", r);

    }
    else
        gmp_printf("Nao existe inverso modular\n");
}