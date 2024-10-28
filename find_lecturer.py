def find_lecturer_legi(multiplier, modulus):
    # Find the modular inverse of the multiplier modulo the modulus
    return pow(multiplier, -1, modulus)

modulus = 0x5f5e107
multiplier1 = 0x5078599
multiplier2 = 0x849fb9

# Compute the Legi numbers for each multiplier
legi2 = find_lecturer_legi(multiplier2, modulus)

print("Lecturer Edition Legi (multiplier 2):", legi2)
