#include "BigInteger.h"

int main() {
    BigInteger a(222222);
    BigInteger b(-222222);
    std::cout << (a - b).to_int();
}

