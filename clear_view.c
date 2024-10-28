#include <cstddef>

void check_product_key(uint param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint bitwise_mask;
  uint current_bit;
  char *input_str;
  byte *pbVar4;
  bool bVar5;
  bool bVar6;
  byte buffer [296];
  byte *input_ptr;
  
  input_ptr = buffer + 0x20;
  do {
    printf("Please enter product key: ");
    input_str = fgets((char *)input_ptr,0x100,stdin);
    if (input_str == (char *)0x0) {
      iVar3 = feof(stdin);
      if (iVar3 == 0) {
        perror("Failed to read input");
      }
                    /* WARNING: Subroutine does not return */
      exit((uint)(iVar3 == 0));
    }
    input_str = strchr((char *)input_ptr,10);
    if (input_str != (char *)0x0) {
      *input_str = '\0';
    }
    current_bit = 0;
    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;
    buffer[4] = 0;
    buffer[5] = 0;
    buffer[6] = 0;
    buffer[7] = 0;
    buffer[8] = 0;
    buffer[9] = 0;
    buffer[10] = 0;
    buffer[0xb] = 0;
    buffer[0xc] = 0;
    buffer[0xd] = 0;
    buffer[0xe] = 0;
    buffer[0xf] = 0;
    buffer[0x10] = 0;
    buffer[0x11] = 0;
    buffer[0x12] = 0;
    buffer[0x13] = 0;
    buffer[0x14] = 0;
    buffer[0x15] = 0;
    buffer[0x16] = 0;
    buffer[0x17] = 0;
    buffer[0x18] = 0;
    buffer[0x19] = 0;
    buffer[0x1a] = 0;
    buffer[0x1b] = 0;
    buffer[0x1c] = 0;
    buffer[0x1d] = 0;
    buffer[0x1e] = 0;
    buffer[0x1f] = 0;
    pbVar4 = input_ptr;
    while( true ) {
      bVar1 = *pbVar4;
      input_str = (char *)CONCAT71((int7)((ulong)input_str >> 8),bVar1);
      if (bVar1 == 0) break;
      if ((int)current_bit >> 1 == 0x20) {
        fputs("Warning: ignoring excess input\n",stderr);
        goto LAB_00401aa6;
      }
      iVar3 = (int)input_str;
      if ((char)bVar1 < '[') {
        if ((char)bVar1 < 'G') {
          if ((char)bVar1 < ':') {
            iVar3 = iVar3 + -0x30;
            bVar6 = SBORROW1(bVar1,'/');
            cVar2 = -0x2f;
            bVar5 = bVar1 == 0x2f;
            goto LAB_00401a5d;
          }
          iVar3 = iVar3 + -0x37;
          if (5 < (byte)(bVar1 + 0xbf)) goto LAB_00401a90;
LAB_00401a7b:
          input_str = (char *)(long)((int)current_bit >> 1);
          buffer[(long)input_str] =
               buffer[(long)input_str] | (byte)(iVar3 << ((byte)(~current_bit << 2) & 4));
          current_bit = current_bit + 1;
        }
        else {
LAB_00401a68:
          bitwise_mask = fputs("Invalid character\n",stderr);
          input_str = (char *)(ulong)bitwise_mask;
        }
      }
      else if ((char)bVar1 < 'g') {
        iVar3 = iVar3 + -0x57;
        bVar6 = SBORROW1(bVar1,'`');
        cVar2 = -0x60;
        bVar5 = bVar1 == 0x60;
LAB_00401a5d:
        if (!bVar5 && bVar6 == (char)(bVar1 + cVar2) < '\0') goto LAB_00401a7b;
      }
      else {
        input_str = (char *)(ulong)(iVar3 - 0x67U);
        if ((byte)(iVar3 - 0x67U) < 0x14) goto LAB_00401a68;
      }
LAB_00401a90:
      pbVar4 = pbVar4 + 1;
    }
    if (current_bit == 0x40) {
LAB_00401aa6:
      current_bit = FUN_00401940((long *)buffer,param_1);
      if ((char)current_bit != '\0') {
        puts("Activation successful!");
        return;
      }
      puts("Failed to validate product key. Please try again.\n");
    }
    else {
      fputs("Input too short\n",stderr);
    }
  } while( true );
}