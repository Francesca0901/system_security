from z3 import BitVec, Solver, LShR, Sum, BitVecVal, sat, Concat

# Buffer: an array of 32 8-bit bytes - from product key
buffer = [BitVec(f'buffer_{i}', 8) for i in range(32)]

# Digit extraction from legi number
legi = 31337042
# digits = [int(d) for d in str(legi)][::-1]  # Reverse the digits
digits = [int(d) for d in str(legi)]

# Helper1: Sum the first 32 bytes (8 bytes per time) and check against a constant value
def get_long_from_bytes(bytes_array, start_idx, endianness='little'):
    if endianness == 'little':
        long_value = Concat(
            bytes_array[start_idx + 7], bytes_array[start_idx + 6],
            bytes_array[start_idx + 5], bytes_array[start_idx + 4],
            bytes_array[start_idx + 3], bytes_array[start_idx + 2],
            bytes_array[start_idx + 1], bytes_array[start_idx]
        )
    else:
        long_value = Concat(bytes_array[start_idx], bytes_array[start_idx + 1], bytes_array[start_idx + 2], 
                            bytes_array[start_idx + 3], bytes_array[start_idx + 4], bytes_array[start_idx + 5],
                            bytes_array[start_idx + 6], bytes_array[start_idx + 7])

    
    return long_value

long1 = get_long_from_bytes(buffer, 0, 'little')  # param_1[0] (bytes 0-7)
long2 = get_long_from_bytes(buffer, 8, 'little')  # param_1[1] (bytes 8-15)
long3 = get_long_from_bytes(buffer, 16, 'little')  # param_1[2] (bytes 16-23)
long4 = get_long_from_bytes(buffer, 24, 'little')  # param_1[3] (bytes 24-31)

helper1_condition = (long1 + long2 + long3 + long4) == BitVecVal(-0x28387878603801, 64)


# Helper2: Compare transformed digits to the first 8 bytes of the buffer
def xor71(value):
    return value ^ BitVecVal(0x71, 8)

def swapbytes(value):
    return LShR(value, 3) | (value << 5)

helper2_conditions = []
for i in range(8):
    byte_from_buffer = buffer[i]
    transformed_byte = swapbytes(xor71(byte_from_buffer))
    helper2_conditions.append(transformed_byte == BitVecVal(digits[i], 8))

# Helper3: Compare the first 8 bytes of the buffer with the last 8 bytes
helper3_conditions = []
for i in range(8):
    helper3_conditions.append((buffer[15 - i] ^ buffer[i]) == i)

# Helper4: Checksum and find a index where the value is the sum of the previous two values
sum_digits = Sum([BitVecVal(digits[i], 8) for i in range(8)])
helper4_checksum_condition = (sum_digits == buffer[0x10])

helper4_sequential_conditions = []
for i in range(0x11, 0x18):
    helper4_sequential_conditions.append(buffer[i] == buffer[i - 1] + buffer[i - 2])


# Solve the constraints
solver = Solver()
solver.add(helper1_condition)
solver.add(helper2_conditions)
solver.add(helper3_conditions)
solver.add([helper4_checksum_condition] + helper4_sequential_conditions)

if solver.check() == sat:
    model = solver.model()
    solution = [model.evaluate(buffer[i]) for i in range(32)]
    print("Solution found for buffer:", solution)
    solution_hex = ''

    for byte in solution:
        # solution_hex += '0x' + format(byte.as_long(), '02x')
        # solution_hex += ','
        solution_hex += format(byte.as_long(), '02x')

    print(solution_hex)

else:
    print("No solution found.")


