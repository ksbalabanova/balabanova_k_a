#include<iostream>
#include<sstream>
#include<cstdint>
#include <rational/rational.hpp>

int32_t nod(int32_t a, int32_t b) {
	a = a > 0 ? a : -a;
	b = b > 0 ? b : -b;
	while (a && b) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	return a + b;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
	return rhs.writeTo(ostrm);
}
std::ostream& Rational::writeTo(std::ostream& ostrm) const  noexcept{
	ostrm << num_ << separator << denum_;
	return ostrm;
}
std::istream& operator>>(std::istream& istrm, Rational& rhs) {
	return rhs.readFrom(istrm);
}
std::istream& Rational::readFrom(std::istream& istrm) noexcept {
	int32_t n(0);
	int32_t d(1);
	char divide;
	char test;
	istrm >> n;
	test = istrm.peek();
	if (test != '/') {
		istrm.setstate(std::ios_base::failbit);
	}
	istrm >> divide;
	test = istrm.peek();
	if (test == ' ') {
		istrm.setstate(std::ios_base::failbit);
	}
	istrm >> d;
	if (!istrm.bad() && !istrm.fail() && (d >= 0)) {
		*this = Rational(n, d);
	}
	else {
		istrm.setstate(std::ios_base::failbit);
	}
	return istrm;
}


Rational::Rational(const int32_t n, const int32_t d) {
	if (d == 0) {
		throw std::invalid_argument("division by zero");
	}
	int32_t x = nod(n, d);
	denum_ = d / x;
	num_ = n / x;
	if (denum_ < 0) {
		denum_ = -denum_;
		num_ = -num_;
	}
}
Rational::Rational(const int32_t n) noexcept {
	denum_ = 1;
	num_ = n;
}


Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational res = lhs;
	return Rational(res += rhs);
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
	Rational res = lhs;
	return Rational(res -= rhs);
}
Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational res = lhs;
	return Rational(res *= rhs);
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
	Rational res = lhs;
	return Rational(res /= rhs);
}


Rational& Rational::operator+=(const Rational& rhs) {
	*this = Rational(num_ * rhs.denum_ + rhs.num_ * denum_, denum_ * rhs.denum_);
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
	*this = Rational(num_ * rhs.denum_ - rhs.num_ * denum_, denum_ * rhs.denum_);
	return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
	*this = Rational(num_ * rhs.num_, denum_ * rhs.denum_);
	return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
	*this = Rational(num_ * rhs.denum_, denum_ * rhs.num_);
	return *this;
}


Rational& Rational::operator+=(const int& rhs) {
	*this += Rational(rhs);
	return *this;
}
Rational& Rational::operator-=(const int& rhs) {
	*this -= Rational(rhs);
	return *this;
}
Rational& Rational::operator*=(const int& rhs) {
	*this *= Rational(rhs);
	return *this;
}
Rational& Rational::operator/=(const int& rhs) {
	*this /= Rational(rhs);
	return *this;
}


Rational& Rational::operator-() {
	num_ = -num_;
	return *this;
}
Rational& Rational::operator++() {
	*this += 1;
	return *this;
}
Rational& Rational::operator--() {
	*this -= 1;
	return *this;
}


Rational Rational::operator++(int) {
	Rational old = *this;
	*this += 1;
	return old;
}
Rational Rational::operator--(int) {
	Rational old = *this;
	*this -= 1;
	return old;
}

bool Rational::operator==(const Rational& rhs) const noexcept {
	if (num_ == rhs.num_ && denum_ == rhs.denum_) {
		return true;
	}
	else {
		return false;
	}
}
bool Rational::operator!=(const Rational& rhs) const noexcept {
	if (num_ == rhs.num_ && denum_ == rhs.denum_) {
		return false;
	}
	else {
		return true;
	}
}
bool Rational::operator>(const Rational& rhs) const noexcept {
	return (num_ * rhs.denum_ > rhs.num_ * denum_);
}
bool Rational::operator<(const Rational& rhs) const noexcept {
	return (num_ * rhs.denum_ < rhs.num_ * denum_);
}
bool Rational::operator<=(const Rational& rhs) const noexcept {
	return (num_ * rhs.denum_ <= rhs.num_ * denum_);
}
bool Rational::operator>=(const Rational& rhs) const noexcept {
	return (num_ * rhs.denum_ >= rhs.num_ * denum_);
}


bool operator==(const Rational& lhs, const int x) {
	return (lhs == Rational(x));
}
bool operator!=(const Rational& lhs, const int x) {
	return (lhs != Rational(x));
}
bool operator>(const Rational& lhs, const int x) {
	return (lhs > Rational(x));
}
bool operator<(const Rational& lhs, const int x) {
	return (lhs < Rational(x));
}
bool operator<=(const Rational& lhs, const int x) {
	return (lhs <= Rational(x));
}
bool operator>=(const Rational& lhs, const int x) {
	return (lhs >= Rational(x));
}

