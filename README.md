# tp-algebra

Implementation of extended gcd algorithm and modular inverse calculator using the GMP library for the C language.

The functions are named in portuguese, so i'll translate them here and give them a description of what they do:

mdc_estendido = extended_gcd
  (returns a x, y and g, such that xa + yb = g = gcd(a, b).)
  
inverso_modular = modular_inverse
  (returns 1 if the modular inverse exists and sets it to r, or 0 if it doesn't.)

exp_binaria = binary_exp
  (uses binary exponentiation to calculate b^e % n.)

talvez_primo = maybe_prime
  (uses the miller primality test to return 1 if the test is inconclusive, or 0 if n is composite.)

numero_aleatorio = random_number
  (generates a random number r, such that 2 <= r < n)

provavelmente_primo = probably_prime
  (uses the miller-rabin primality test to return 1 if n is prime with a probability at most 4^(-iter), or 0 if it's composite.)

primo_aleatorio = random_prime
  (returns a random prime n, such that 2 <= n < 2^b.)
  
gera_chaves = generate_keys
  (returns a random prime n, a public key e and a private key d.)

codifica = codify
  (converts a string to a base 256 number.)

decodifica = decodify
  (converts a base 256 number to a string.)
  
criptografa = cryptograph
  (returns a C such that C = M^e % n.)

descriptografa = decryptograph
  (returns a M such that M = C^d % n.)
