#include <stdio.h>
#include <stdlib.h>


int main() {

    int test = 0xFE45DF;

    int a, b, c;

    a = test / (256 * 256);
    b = test / 256 % 256;
    c = test % 256;

    printf("0x%02X %02X %02X", a, b, c);

    return 0;
}