#include<iostream>
#include<sstream>
#include <rational/rational.hpp>

int32_t nod(int32_t a, int32_t b) {
	a = std::abs(a);
	b = std::abs(b);
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

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
	ostrm << num << separator << denum;
	return ostrm;
}
std::istream& Rational::readFrom(std::istream& istrm) {
	int n(0);
	char sl(0);
	int d(1);
	istrm >> n >> sl >> d;
	if (istrm.good() || istrm.eof() && !istrm.fail()) {
		if (Rational::separator == sl) {
			istrm.clear();
			*this = Rational(n, d);
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}

Rational Rational::operator+(const Rational& rhs) {
	return Rational((*this).num * rhs.denum + rhs.num * (*this).denum, rhs.denum * (*this).denum);

}
Rational Rational::operator-(const Rational& rhs) {
	return Rational((*this).num * rhs.denum - rhs.num * (*this).denum, rhs.denum * (*this).denum);
}
Rational Rational::operator*(const Rational& rhs) {
	return Rational((*this).num * rhs.num, (*this).denum * rhs.denum);
}
Rational Rational::operator/(const Rational& rhs) {
	return Rational((*this).num * rhs.denum, (*this).denum * rhs.num);
}

Rational Rational::operator+=(Rational& rhs) {
	Rational res = { ((*this).num * rhs.denum) + (rhs.num * denum), (*this).denum * rhs.denum };
	return res;
}
Rational Rational::operator-=(Rational& rhs) {
	Rational res = { ((*this).num * rhs.denum) - (rhs.num * (*this).denum), (*this).denum * rhs.denum };
	return res;
}
Rational Rational::operator*=(Rational& rhs) {
	Rational res = { (*this).num * rhs.num, (*this).denum * rhs.denum };
	return res;
}
Rational Rational::operator/=(Rational& rhs) {
	Rational res = { (*this).num * rhs.denum, (*this).denum * rhs.num };
	return res;
}


Rational Rational::operator+(const int x) {
	Rational rhs(x);
	return Rational((*this).num * rhs.denum + rhs.num * (*this).denum, rhs.denum * (*this).denum);

}
Rational Rational::operator-(const int x) {
	Rational rhs(x);
	return Rational((*this).num * rhs.denum - rhs.num * (*this).denum, rhs.denum * (*this).denum);
}
Rational Rational::operator*(const int x) {
	Rational rhs(x);
	return Rational((*this).num * rhs.num, (*this).denum * rhs.denum);
}
Rational Rational::operator/(const int x) {
	Rational rhs(x);
	return Rational((*this).num * rhs.denum, (*this).denum * rhs.num);
}

Rational Rational::operator+=(const int x) {
	Rational rhs(x);
	Rational res = { ((*this).num * rhs.denum) + (rhs.num * denum), (*this).denum * rhs.denum };
	return res;
}
Rational Rational::operator-=(const int x) {
	Rational rhs(x);
	Rational res = { ((*this).num * rhs.denum) - (rhs.num * (*this).denum), (*this).denum * rhs.denum };
	return res;
}
Rational Rational::operator*=(const int x) {
	Rational rhs(x);
	Rational res = { (*this).num * rhs.num, (*this).denum * rhs.denum };
	return res;
}
Rational Rational::operator/=(const int x) {
	Rational rhs(x);
	Rational res = { (*this).num * rhs.denum, (*this).denum * rhs.num };
	return res;
}

Rational operator-(const Rational& rhs) {
	return (Rational(0, 1) - rhs);
}

bool Rational::operator==(const Rational& rhs) const {
	if (num == rhs.num && denum == rhs.denum) {
		return true;
	}
	else {
		return false;
	}
}
bool Rational::operator!=(const Rational& rhs) const {
	if (num == rhs.num && denum == rhs.denum) {
		return false;
	}
	else {
		return true;
	}
}
bool Rational::operator>(const Rational& rhs) {
	return (num * rhs.denum > rhs.num * denum);
}
bool Rational::operator<(const Rational& rhs) {
	return (num * rhs.denum < rhs.num * denum);
}
bool Rational::operator<=(const Rational& rhs) {
	return (num * rhs.denum <= rhs.num * denum);
}

bool Rational::operator>=(const Rational& rhs) {
	return (num * rhs.denum >= rhs.num * denum);
}

Rational::Rational(const int32_t n, const int32_t d) {
	if (d == 0) {
		throw std::invalid_argument("division by zero");
	}
	int32_t x = nod(n, d);
	denum = d / x;
	num = n / x;
	if (denum < 0) {
		denum = -denum;
		num = -num;
	}

};
Rational::Rational(const int32_t n) {
	denum = 1;
	num = n;
	if (denum < 0) {
		denum = -denum;
		num = -num;
	}
};
