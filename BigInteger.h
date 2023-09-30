#include<vector>
#include<iostream>

class BigInteger {
public:
    BigInteger() {}
    BigInteger(int a) {
        _sign = a >= 0;
        a = abs(a);
        while (a) {
            _digits.push_back(a % _system);
            a /= _system;
        }
    }
    ~BigInteger() = default;

    int to_int() const {
        int res = 0;
        for (int i = _digits.size() - 1; i >= 0; --i) {
            res += _digits[i];
            if (i) {
                res *= _system;
            }
        }
        return _sign ? res : -res;
    }

    size_t size() const {
        return _digits.size();
    }

    bool sign() const {
        return _sign;
    }

    BigInteger& operator - () {
        _sign = !_sign;
        return *this;
    }

    bool operator == (const BigInteger& x) {
        if (_sign != x._sign) {
            return false;
        }
        if (size() != x.size()) {
            return false;
        }
        for (int i = size() - 1; i >= 0; --i) {
            if (_digits[i] != x._digits[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator < (const BigInteger& x) {
        if (_sign > x._sign) {
            return false;
        } else if (_sign < x._sign) {
            return true;
        } else if (_sign) {
            if (size() > x.size()) {
                return false;
            } else if (size() < x.size()) {
                return true;
            } else {
                for (int i = size() - 1; i >= 0; --i) {
                    if (_digits[i] < x._digits[i]) {
                        return true;
                    } else if (_digits[i] > x._digits[i]) {
                        return false;
                    }
                }
            }
        }
        if (size() > x.size()) {
            return true;
        } else if (size() < x.size()) {
            return false;
        } else {
            for (int i = size() - 1; i >= 0; --i) {
                if (_digits[i] < x._digits[i]) {
                    return false;
                } else if (_digits[i] > x._digits[i]) {
                    return true;
                }
            }
        }
        return false;
    }

    BigInteger& operator += (const BigInteger& x) {
        bool overflow = false;
        if (!(_sign ^ x._sign)) {
            for (int i = 0; i < x.size(); ++i) {
                if (i < size()) {
                    _digits[i] += (x._digits[i] + overflow);
                } else {
                    _digits.push_back(x._digits[i] + overflow);
                }
                if (_digits[i] >= _system) {
                    overflow = true;
                    _digits[i] %= 1024;
                } else {
                    overflow = false;
                }
            }
        } else {

        }
        return *this;
    }

private:
    bool _sign;
    size_t _system = 1024;
    std::vector<int> _digits;
};
