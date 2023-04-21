#define RATIONAL_RATIONAL_HPP_20230215
#include <iosfwd>
#include<exception>
#include<stdexcept>

int32_t nod(int32_t a, int32_t b);

class Rational {
public:
	Rational() = default;
	Rational(const Rational&) = default;
	Rational(const int32_t n, const int32_t d);
	explicit Rational(const int32_t n) noexcept;
	~Rational() = default;

	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	Rational& operator+=(const int32_t & rhs);
	Rational& operator-=(const int32_t & rhs);
	Rational& operator*=(const int32_t & rhs);
	Rational& operator/=(const int32_t & rhs);

	Rational& operator-();
	Rational& operator++();
	Rational& operator--();
	Rational operator++(int);
	Rational operator--(int);

	bool operator==(const Rational& rhs) const noexcept;
	bool operator!=(const Rational& rhs) const noexcept;
	bool operator>(const Rational& rhs) const noexcept;
	bool operator<(const Rational& rhs) const noexcept;
	bool operator<=(const Rational& rhs) const noexcept;
	bool operator>=(const Rational& rhs) const noexcept;

	std::ostream& writeTo(std::ostream& ostrm) const noexcept;
	std::istream& readFrom(std::istream& istrm)noexcept;


private:
	int32_t num_{0};
	int32_t denum_{1};
	static const char separator{ '/' };//формат
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);


Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);


bool operator==(const Rational &lhs, const int32_t &rhs);
bool operator!=(const Rational &lhs, const int32_t &rhs);
bool operator>(const Rational &lhs, const int32_t &rhs);
bool operator<(const Rational &lhs, const int32_t &rhs);
bool operator<=(const Rational &lhs, const int32_t &rhs);
bool operator>=(const Rational &lhs, const int32_t &rhs);
