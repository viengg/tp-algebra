
void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b);

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n);

void exp_binaria(mpz_t r, const mpz_t b, const mpz_t e, const mpz_t n);

int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q);

void numero_aleatorio(mpz_t r, const mpz_t n, gmp_randstate_t rnd);

int provavelmente_primo(const mpz_t n, unsigned int iter, gmp_randstate_t rnd);

void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd);

void gera_chaves(mpz_t n, mpz_t e, mpz_t d, gmp_randstate_t rnd);

void codifica(mpz_t r, const char *str);

char *decodifica(const mpz_t n);

void criptografa(mpz_t C, const mpz_t M, const mpz_t n, const mpz_t e);

void descriptografa(mpz_t M, const mpz_t C, const mpz_t n, const mpz_t d);