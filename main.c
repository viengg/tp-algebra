#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "myfunctions.h"

void main()
{
    char *msg = malloc(sizeof(char)*501);
    gmp_randstate_t rnd;
    gmp_randinit_default(rnd);
    gmp_randseed_ui(rnd, 1114522567);

    mpz_t n, e, d, mensagem, M, C;
    mpz_inits(n, e ,d, mensagem, M, C, NULL);

    printf("Digite uma mensagem: ");
    scanf("%[^\n]%*c", msg);
    codifica(mensagem, msg);
    gmp_printf("mensagem codificada = %Zd\n\n", mensagem);

    gera_chaves(n, e, d, rnd);
 
    criptografa(C, mensagem, n, e);
    gmp_printf("mensagem criptografada = %Zd\n\n", C);

    printf("Liberando a mensagem original da memoria!\n\n");
    mpz_clear(mensagem);
    free(msg);

    descriptografa(M, C, n, d);
    gmp_printf("mensagem descriptografada = %Zd\n", M);

    printf("mensagem M decodificada = %s\n", decodifica(M));
    mpz_clears(n, e ,d, mensagem, M, C, NULL);
    
}
