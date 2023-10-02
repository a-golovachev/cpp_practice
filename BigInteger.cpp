#include "BigInteger.h"

int main() {
    BigInteger a(1023);
    BigInteger b(999999);
    std::cout << (a - b).to_int();
}

