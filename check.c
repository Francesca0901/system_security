#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ulong unsigned long
#define uint unsigned int
#define undefined8 int8_t
#define byte unsigned char

undefined8 helper1(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[1] + param_1[0] + param_1[2] + param_1[3];
  return lVar1 == -0x28387878603801;
}



uint xor71(uint param_1)

{
  return param_1 ^ 0x71;
}

byte swapbytes(byte param_1)

{
  return param_1 >> 3 | param_1 << 5;
}

undefined8 helper2(long legi_ptr,long key_ptr)

{
  byte bVar1;
  uint uVar2;
//   long also_cnt;
  long cnt;
  
  cnt = 0;
  do {
    uVar2 = xor71((uint)*(byte *)(key_ptr + cnt));
    bVar1 = swapbytes((byte)uVar2);
    if (bVar1 != *(byte *)(legi_ptr + cnt)) {
      return 0;
    }
    cnt = cnt + 1;
  } while (cnt != 8);
  return 1;
}


undefined8 helper3(long param_1)

{
  long lVar1;
  
  lVar1 = 0;
  do {
    if ((uint)(*(byte *)((param_1 + 0xf) - lVar1) ^ *(byte *)(param_1 + lVar1)) != (uint)lVar1) {
        printf("%d\n", (uint)(*(byte *)((param_1 + 0xf) - lVar1) ^ *(byte *)(param_1 + lVar1)));
      return 0;
    }
    lVar1 = lVar1 + 1;
  } while (lVar1 != 8);
  return 1;
}



undefined8 helper4(long param_1,long param_2)

{
  long counter;
  char sum;
  
  counter = 0;
  sum = '\0';
  do {
    sum = sum + *(char *)(param_1 + counter);
    counter = counter + 1;
  } while (counter != 8);
  printf("%d\n", *(char *)(param_2 + 0x10));
  if (*(char *)(param_2 + 0x10) == sum) {
    counter = 0x11;
    while (*(char *)(param_2 + counter) ==
           (char)(*(char *)(param_2 + -2 + counter) + *(char *)(param_2 + -1 + counter))) {
      counter = counter + 1;
      if (counter == 0x18) {
        return 1;
      }
    }
  }
  return 0;
}


uint actual_check(long *key,uint legi_number)

{
  int8_t uVar1;
  long counter;
  uint uVar2;
  long *key_2;
  char *legi_ptr;
  bool bVar3;
  char legi [8];
  ulong legi_id;
  
  counter = 7;
  legi_id = (ulong)legi_number;
  do {
    legi_ptr = legi;
    legi[counter] = (char)(legi_id % 10);
    bVar3 = counter != 0;
    counter = counter + -1;
    legi_id = legi_id / 10;
  } while (bVar3);
  key_2 = key;
  uVar1 = helper1(key);
  uVar2 = (uint)uVar1;
  uVar1 = helper2((long)legi_ptr,(long)key);
  uVar2 = uVar2 & (uint)uVar1;
  uVar1 = helper3((long)key_2);
  uVar2 = uVar2 & (uint)uVar1;
  uVar1 = helper4((long)legi_ptr,(long)key);
  return (uint)uVar1 & uVar2;
}

int main()
{
    // buffer = [97, 81, 113, 73, 105, 105, 121, 105, 110, 127, 108, 109, 74, 115, 80, 97, 23, 120, 143, 7, 150, 157, 51, 208, 24, 142, 90, 201, 61, 37, 202, 101]
    // uint8_t input_bytes[32] = {
    //     0x69, 0x79, 0x69, 0x69, 0x49, 0x71, 0x51, 0x61, // First long (little-endian representation)
    //     0x61, 0x50, 0x73, 0x4a, 0x6d, 0x6c, 0x7f, 0x6e, // Second long
    //     0xd0, 0x33, 0x9d, 0x96, 0x07, 0x8f, 0x78, 0x17, // Third long
    //     0x65, 0xca, 0x25, 0x3d, 0xc9, 0x5a, 0x8e, 0x18  // Fourth long
    // };

    uint8_t input_bytes[32] = {
        0x69,0x79,0x69,0x69,0x49,0x71,0x51,0x61,0x66,0x57,0x74,0x4d,0x6a,0x6b,0x78,0x69,0x17,0x80,0x97,0x17,0xae,0xc5,0x73,0x38,0x19,0x77,0x2a,0xb9,0x25,0x25,0x9a,0xfc
    };  

    // 0x61,0x51,0x71,0x49,0x69,0x69,0x79,0x69,
    // 0x6e,0x7f,0x6c,0x6d,0x4a,0x73,0x50,0x61,
    // 0x17,0x78,0x8f,0x07,0x96,0x9d,0x33,0xd0,
    // 0x19,0x7f,0x32,0xc9,0x3d,0x4d,0xda,0x64

    long* key = (long*)input_bytes;
    memcpy(key, input_bytes, 32);

    uint legi_number = 31337042;
    uint result = actual_check(key, legi_number);
    printf("result: %d\n", result);
    return 0;
}


