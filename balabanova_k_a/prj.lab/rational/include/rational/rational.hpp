#define RATIONAL_RATIONAL_HPP_20230215
#include <iosfwd>
#include<exception>
#include<stdexcept>

int32_t nod(int32_t a, int32_t b);

class Rational {

public:
	Rational() = default;
	Rational(const Rational& rhs) = default;
	Rational(const int32_t n, const int32_t d);
	Rational(const int32_t n);
	~Rational() = default;

	Rational operator+(const Rational& rhs);
	Rational operator-(const Rational& rhs);
	Rational operator*(const Rational& rhs);
	Rational operator/(const Rational& rhs);

	Rational operator+=(Rational& rhs);
	Rational operator-=(Rational& rhs);
	Rational operator*=(Rational& rhs);
	Rational operator/=(Rational& rhs);

	Rational operator+(const int x);
	Rational operator-(const int x);
	Rational operator*(const int x);
	Rational operator/(const int x);

	Rational operator+=(const int x);
	Rational operator-=(const int x);
	Rational operator*=(const int x);
	Rational operator/=(const int x);

	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;
	bool operator>(const Rational& rhs);
	bool operator<(const Rational& rhs);
	bool operator<=(const Rational& rhs);
	bool operator>=(const Rational& rhs);

	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);


private:
	int32_t num{ 0 };
	int32_t denum{ 1 };
	static const char separator{ '/' };//формат
};

inline std::istream& operator>>(std::istream& istrm, Rational& rhs) {
	return rhs.readFrom(istrm);
}
inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
	return rhs.writeTo(ostrm);
}

Rational operator-(const Rational& rhs);
