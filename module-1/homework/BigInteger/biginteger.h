#include <vector> 
#include <string>
#include <iostream>

class BigInteger {
private:
    std::vector<int> figures;
    bool sign = true;
    static const int base = 1000000000;
    void improve();
public:       
    BigInteger();
    BigInteger(int);   
    BigInteger(std::string);  

    friend BigInteger operator +(const BigInteger& first, const BigInteger& other);
    friend BigInteger operator -(const BigInteger& first, const BigInteger& other);
    friend BigInteger operator *(const BigInteger& first, const BigInteger& other);
    BigInteger half();
    friend BigInteger operator /(const BigInteger& first, const BigInteger& other);
    friend BigInteger operator %(const BigInteger& first, const BigInteger other);      
    
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);        
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other); 

    BigInteger& operator-();
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    friend bool operator==(const BigInteger& first, const BigInteger& other);
    friend bool operator!=(const BigInteger& first, const BigInteger& other);
    friend bool operator>(const BigInteger& first, const BigInteger& other);
    friend bool operator<(const BigInteger& first, const BigInteger& other);
    friend bool operator<=(const BigInteger& first, const BigInteger& other);
    friend bool operator>=(const BigInteger& first, const BigInteger& other);

    std::string toString() const;

    operator bool();
        
    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
	friend std::istream& operator>>(std::istream&, BigInteger&);

    BigInteger& operator=(BigInteger other);

};
