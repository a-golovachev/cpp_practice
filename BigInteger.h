#include<vector>
#include<iostream>

class BigInteger {
public:
    BigInteger() {}
    BigInteger(int a) {
        _sign = a >= 0;
        a = std::abs(a);
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

    BigInteger abs() const {
        BigInteger res = *this;
        res._sign = true;
        return res;
    }

    BigInteger& operator = (const BigInteger& x) {
        _sign = x._sign;
        _system = x._system;
        _digits = x._digits;
        return *this;
    }

    BigInteger operator - () const {
        BigInteger res = *this;
        res._sign = !_sign;
        return res;
    }

    bool operator < (const BigInteger& x) const {
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

    bool operator > (const BigInteger& x) const {
        return (x < *this);
    }

    bool operator == (const BigInteger& x) const {
        return !((x < *this) || (x > *this));
    }

    bool operator >= (const BigInteger& x) const {
        return !(*this < x);
    }

    bool operator <= (const BigInteger& x) const {
        return !(*this > x);
    }

    bool operator != (const BigInteger& x) const {
        return !(*this == x);
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
                    _digits[i] %= _system;
                } else {
                    overflow = false;
                }
            }
            if (overflow) {
                _digits.push_back(1);
            }
        } else {
            if (x.abs() > abs()) {
                for (int i = 0; i < x.size(); ++i) {
                    if (i < size()) {
                        _digits[i] = (x._digits[i] - _digits[i] - overflow);
                    } else {
                        _digits.push_back(x._digits[i] - overflow);
                    }
                    if (_digits[i] < 0) {
                        overflow = true;
                        _digits[i] %= _system;
                    } else {
                        overflow = false;
                    }
                }
                _sign = x.sign();
            } else {
                for (int i = 0; i < size(); ++i) {
                    if (i < x.size()) {
                        _digits[i] -= (x._digits[i] + overflow);
                    } else if (overflow) {
                        --_digits[i];
                    } else {
                        break;
                    }
                    if (_digits[i] < 0) {
                        overflow = true;
                        _digits[i] %= _system;
                    } else {
                        overflow = false;
                    }
                }
            }
            clean_zeroes();
        }
        return *this;
    }

    BigInteger operator + (const BigInteger& x) const {
        BigInteger res = *this;
        return res += x;
    }

    BigInteger operator - (const BigInteger& x) const {
        BigInteger res = *this + (-x);
        return res;
    }

    BigInteger& operator -= (const BigInteger& x) {
        return *this += (-x);
    }

    BigInteger& operator ++ () {
        return *this += 1;
    }

    BigInteger& operator -- () {
        return *this -= 1;
    }

private:
    bool _sign;
    size_t _system = 1024;
    std::vector<int> _digits;

    void clean_zeroes() {
        for (int i = size() - 1; !(_digits[i] || size() == 1); --i) {
            _digits.pop_back();
        }
    }
};
