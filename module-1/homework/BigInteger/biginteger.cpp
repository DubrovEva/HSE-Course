#include "biginteger.h"

BigInteger::BigInteger(){
}
BigInteger::BigInteger(int num) {
    if (num < 0) {
        num *= -1;
        sign = false;
    }
    while (num) {
        figures.push_back(num % 1000000000);
        num /= 1000000000;
    }
    improve();
}
BigInteger::BigInteger(std::string str) {
    if (str[0] == '-' && str != "0")
        sign = false;
        
	for (int i = str.size() - 1; i >= 1 - sign; i -= 9) {
        int x = 0;
        for (int j = 8; j >= 0; --j) {
            if (i - j < 0 || str[i - j] == '-')
                continue;
            x = x * 10 + (str[i - j] - '0');
        }
        figures.push_back(x);
	}
    improve();
}

BigInteger BigInteger::operator+(const BigInteger& other){
    BigInteger result;
    if (sign != other.sign) {
        if (sign) {
            BigInteger another = other;
            another.sign = true;
            result = *this - another;
        } else {
            BigInteger another = *this;
            another.sign = true;
            result = another - other; 
            result.sign = !result.sign;
        }
    } else {
        result.sign = sign;
        int carry = 0;
        for (size_t i = 0; i < std::max(figures.size(),(other.figures).size()) || carry; ++i) {
            if (i == result.figures.size())
                result.figures.push_back(0);
            int a = (i < figures.size() ? figures[i] : 0);
            int b = (i < other.figures.size() ? other.figures[i] : 0);
            result.figures[i] =  a + carry + b;
            carry = result.figures[i] >= base;
            if (carry)  
                result.figures[i] -= base;
        }   
    }

    result.improve();
    return result;
}
BigInteger BigInteger::operator-(const BigInteger& other){ 
    BigInteger result;
    if (*this == other)
        result = BigInteger(0);
    else if (sign && !other.sign) { // a - -b
        BigInteger another = other;
        another.sign = true;
        result = *this + another;
    } else if (!sign && other.sign) { //-a - b
        BigInteger another = *this;
        another.sign = true;
        result = another + other;
        result.sign = false;
    } else {
        if (*this > other)  {
            result.sign = true;
            result.figures = figures;
            int carry = 0;
            for (size_t i = 0; i < other.figures.size() || carry; ++i) {
                result.figures[i] -= carry + (i < other.figures.size() ? other.figures[i] : 0);
                carry = result.figures[i] < 0;
                if (carry)  result.figures[i] += base;
            }
            while (result.figures.size() > 1 && result.figures.back() == 0)
                result.figures.pop_back();
        } else {
            result.sign = false;
            result.figures = other.figures;
            int carry = 0;
            for (size_t i = 0; i < figures.size() || carry; ++i) {
                result.figures[i] -= carry + (i < figures.size() ? figures[i] : 0);
                carry = result.figures[i] < 0;
                if (carry)  result.figures[i] += base;
            }
            while (result.figures.size() > 1 && result.figures.back() == 0)
                result.figures.pop_back();

        }
    }
    result.improve();
    return result; 
}   
BigInteger BigInteger::operator*(const BigInteger& other){
    BigInteger result;
    result.sign = (sign && other.sign) || (!sign && !other.sign);
    result.figures.resize(figures.size() + other.figures.size());
    for (size_t i = 0; i < figures.size(); ++i)
        for (int j = 0, carry = 0; j < other.figures.size() || carry; ++j) {
            long long cur = 
                result.figures[i + j] + figures[i] * 1ll * (j < (int)other.figures.size() ? other.figures[j] : 0) + carry;
            result.figures[i + j] = int (cur % base);
            carry = int (cur / base);
        }
        
    result.improve();
    return result;
}
BigInteger BigInteger::half(){
    BigInteger result;
    result.figures = figures;
    int carry = 0;
    for (int i = (int) figures.size() - 1;  i >= 0; --i) {
        long long cur = result.figures[i] + carry * 1ll * base;
        result.figures[i] = int (cur / 2);
        carry = int (cur % 2);
    }
    while (result.figures.size() > 1 && result.figures.back() == 0)
        result.figures.pop_back();
    
    result.improve();
    return result; 
}
BigInteger BigInteger::operator/(const BigInteger& other){
    int carry = 0;
    BigInteger l = 1, r = *this, diff = BigInteger(1);

    while (r - l > diff) {
        BigInteger m = (r + l).half();
        if (m * other > *this)
            r = m;
        else
            l = m;
    }

    l.sign = (sign && other.sign) || (!sign && !other.sign);

    l.improve();
    return l; 
}
BigInteger BigInteger::operator%(const BigInteger other) {
    return *this - *this / other;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = *this + other;
    return *this;
}
BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = *this - other;
    return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = *this / other;
    return *this;
}
BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = *this % other;
    return *this;
}

BigInteger& BigInteger::operator-() {
    sign = !sign;
    return *this;
}
BigInteger& BigInteger::operator++() {
    BigInteger one{1};
    *this = *this + one;
	return *this;
}
BigInteger BigInteger::operator++(int) {
    BigInteger one{1}, t = *this;
    t = *this;
    *this = *this + one;
    return t;
}
BigInteger& BigInteger::operator--() {
    BigInteger one{1};
    *this = *this - one;
	return *this;
}
BigInteger BigInteger::operator--(int) {
    BigInteger one{1}, t = *this;
    t = *this;
    *this = *this - one;
    return t;
}

bool BigInteger::operator==(const BigInteger& other) {
    return (figures == other.figures) && (sign == other.sign);
}
bool BigInteger::operator!=(const BigInteger& other) {
    return !(*this == other);
}
bool BigInteger::operator>(const BigInteger& other) {
    if (*this == other)
        return false;
    if (sign && !other.sign) 
        return true;
    else if (!sign && other.sign)
        return false;
    else if (sign && other.sign) {
        if (figures.size() != other.figures.size()) {
            return figures.size() > other.figures.size();
        } else {
            for (int i = figures.size() - 1; i >= 0; --i) {
                if (figures[i] != other.figures[i])
                    return figures[i] > other.figures[i];
            }
            return false;
        }
    }
    return false;
}
bool BigInteger::operator<(const BigInteger& other){
    return !(*this > other) && (*this != other);
}
bool BigInteger::operator<=(const BigInteger& other){
    return !(*this > other);
}
bool BigInteger::operator>=(const BigInteger& other){
    return !(*this < other);
}

std::string BigInteger::toString() const {
	std::string str = (!sign) ? "-" : "";
	for (int i = figures.size() - 1; i >= 0; --i) {
		str += std::to_string(figures[i]);
	}
	return str;
}

BigInteger::operator bool(){  
    BigInteger zero{0};
    return *this == zero;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
    
	if (!x.sign) 
        out << "-";
    if (x.figures.size() == 1 && x.figures[0] == 0)
        out << "0";
    if (x.figures.empty())
        out << "0";
	for (int i = x.figures.size() - 1; i >= 0; --i){
        int m = 100000000;
        out << x.figures[i];
        while(i != x.figures.size() - 1 && x.figures[i] < m) {
            out << 0;
            m /= 10;
        }
    
    }
	return out;
}
std::istream& operator>>(std::istream& in, BigInteger& x) {
	std::string str;
	in >> str;
    x = BigInteger(str);
	return in;
}

BigInteger& BigInteger::operator=(BigInteger other){
    figures = other.figures;
    sign = other.sign;
    return *this;
}

void BigInteger::improve() {
    while (figures.size() > 0 && figures.back() == 0)
        figures.pop_back();
    if (figures.empty())
        sign = true;
}
