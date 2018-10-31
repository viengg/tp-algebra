#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

    mpz_clears(x1, y1, u, v, q, r, m, n, aux1, aux2, a1, b1, NULL);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n)
{
    mpz_t g, x, y;
    mpz_inits(g, x, y , NULL);
    mdc_estendido(g, x, y, a, n);

    if(mpz_cmp_ui(g, 1) == 0)
    {
        mpz_set(r, x);
        mpz_clears(g, x, y, NULL);
        return 1;
    }
    mpz_clears(g, x, y, NULL);
    return 0;
}

void exp_binaria(mpz_t r, const mpz_t b, const mpz_t e, const mpz_t n)
{
    mpz_t result, x, y;
    mpz_inits(result, x, y, NULL);
    mpz_set_ui(result, 1);
    mpz_set(x, b);
    mpz_set(y, e);

    mpz_tdiv_r(x, x, n);

    while(mpz_cmp_ui(y, 0) > 0)
    {
        if(mpz_odd_p(y))
        {
            mpz_mul(result, result, x);
            mpz_tdiv_r(result, result, n);
        }
        
        mpz_tdiv_q_ui(y, y, 2);
        mpz_mul(x, x, x);
        mpz_tdiv_r(x, x, n);
    }

    mpz_set(r, result);
    mpz_clears(result, x, y, NULL);

}


int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, 
                                unsigned int t, const mpz_t q)
{
    mpz_t x, a_aux;
    mpz_inits(x, a_aux, NULL);
    mpz_mod(a_aux, a, n);

    if(mpz_cmp_ui(a_aux, 0) == 0)
    {
        mpz_clears(x, a_aux, NULL);
        return 1;   
    }

    exp_binaria(x, a_aux, q, n);

    if(mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n1) == 0)
    {
        mpz_clears(x, a_aux, NULL);
        return 1;
    }

    for(int i = 1; i < t; i++)
    {
        mpz_mul(x, x, x);
        mpz_mod(x, x, n);

        if(mpz_cmp(x, n1) == 0)
        {
            mpz_clears(x, a_aux, NULL);
            return 1;
        }
        else if(mpz_cmp_ui(x, 1) == 0)
        {
            mpz_clears(x, a_aux, NULL);
            return 0;
        }
    }

    mpz_clears(x, a_aux, NULL);
    return 0;

}

void numero_aleatorio(mpz_t r, const mpz_t n, gmp_randstate_t rnd)
{
    mp_bitcnt_t num_bits = mpz_sizeinbase(n, 2);
    do
    {
        mpz_urandomb(r, rnd, num_bits);
    } while (!(mpz_cmp_ui(r, 2) >= 0 && mpz_cmp(r, n) <= 0));
}

int provavelmente_primo(const mpz_t n, unsigned int iter, 
                                        gmp_randstate_t rnd)
{
    mpz_t n1, q, a;
    int t = 0;
    mpz_inits(n1, q, a, NULL);
    mpz_sub_ui(n1, n, 1);
    mpz_set(q, n1);

    if(mpz_cmp_ui(n, 2) == 0)
    {
        mpz_clears(n1, q, a, NULL);
        return 1;
    }

    if(mpz_even_p(n))
    {
        mpz_clears(n1, q, a, NULL);
        return 0;
    }

    while(mpz_even_p(q))
    {
        t++;
        mpz_div_ui(q, q, 2);
    }

    for(int i = 0; i < iter; i++)
    {
        numero_aleatorio(a, n1, rnd);
        if(!talvez_primo(a, n, n1, t, q))
        {
            mpz_clears(n1, q, a, NULL);
            return 0;
        }
    }
    mpz_clears(n1, q, a, NULL);
    return 1;
}

void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd)
{
    do
    {
        mpz_urandomb(r, rnd, b);
    }while(!provavelmente_primo(r, 20, rnd));
}

void gera_chaves(mpz_t n, mpz_t e, mpz_t d, gmp_randstate_t rnd)
{
    mpz_t p, q, p1, q1, phi, g;
    mpz_inits(p, q, p1, q1, phi, g, NULL);
    mpz_set_ui(e, 65536);
    primo_aleatorio(p, 20, rnd);
    primo_aleatorio(q, 20, rnd);
    mpz_mul(n, p, q);
    //gmp_printf("%Zd = %Zd * %Zd\n", n, p, q);
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);
    
    do
    {
        mpz_add_ui(e, e, 1);
        mpz_gcd(g, e, phi);
    }while(mpz_cmp_ui(g, 1) != 0);

    inverso_modular(d, e, phi);
    mpz_mod(d, d, phi);
    mpz_clears(p, q, p1, q1, phi, g, NULL);
}

void codifica(mpz_t r, const char *str)
{
    mpz_t aux, pot;
    mpz_inits(aux, pot, NULL);

    for(int i = 0; i < strlen(str); i++)
    {
        mpz_ui_pow_ui(pot, 256, i);
        mpz_mul_ui(aux, pot, str[i]);
        mpz_add(r, r, aux);
    }

    mpz_clears(aux, pot, NULL);
}

char *decodifica(const mpz_t n)
{
    int i = 0;
    char *mensagem = malloc(sizeof(char)*501);
    mpz_t n_aux, r;
    mpz_inits(n_aux, r, NULL);
    mpz_set(n_aux, n);

    while(mpz_cmp_ui(n_aux, 0) != 0)
    {
        mpz_tdiv_qr_ui(n_aux, r, n_aux, 256);
        mensagem[i++] = mpz_get_ui(r);
    }

    mpz_clears(n_aux, r, NULL);
    mensagem[i] = '\0';
    return mensagem;
}
void main()
{
    char *msg;
    gmp_randstate_t rnd;
    gmp_randinit_default(rnd);
    gmp_randseed_ui(rnd, 1114522567);

    mpz_t n, e, d, r;
    mpz_inits(n, e ,d, r, NULL);
    gera_chaves(n, e, d, rnd);
    codifica(r, "puta que pariu velho voce e muito retardado deus me livre e me guarde");
    gmp_printf("mensagem = %Zd\n", r);
    msg = decodifica(r);
    gmp_printf("mensagem decodificada = %s\n", msg);
}