#include<vector>
#include<iostream>

class BigInteger {
public:
    BigInteger() {}
    BigInteger(int a) {
        _sign = a >= 0;
        while (a) {
            _digits.push_back(a % _system);
            a /= _system;
        }
    }
    ~BigInteger() = default;

    int to_int() {
        int res = 0;
        for (int i = _digits.size() - 1; i >= 0; --i) {
            res += _digits[i];
            if (i) {
                res *= _system;
            }
        }
        return _sign ? res : -res;
    }
private:
    bool _sign;
    size_t _system = 1000;
    std::vector<int> _digits;
};
