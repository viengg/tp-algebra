# tp-algebra

Implementation of extended gcd algorithm and modular inverse calculator using the GMP library for the C language.

The functions are named in portuguese, so i'll translate them here and give them a description of what they do:

mdc_estendido = extended_gcd
  returns a x, y and g, such that x*a + y*b = g = gcd(a, b).
  
inverso_modular = modular_inverse
  returns 1 if the modular_inverse exists and set it to r, or 0 if it doesn't.

exp_binaria = binary_exp
  uses binary exponentiation to calculate b^e mod(n).

talvez_primo = maybe_prime
  uses the miller primality test to return 1 if the n is probably prime, or 0 if it's composite.

numero_aleatorio = random_number
  generates a random number r, such that 2 <= r < n

provavelmente_primo = probably_prime
  uses the miller-rabin primality test to return 1 if n is prime with the odds of being wrong equal to 4^(-iter), or 0 if it's composite.

primo_aleatorio = random_prime
  returns a random prime n, such that 2 <= n < 2^b.
