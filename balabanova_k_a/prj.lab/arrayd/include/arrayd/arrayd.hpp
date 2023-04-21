#include<iostream>
#include <cstddef>

class ArrayD {
private:
	std::ptrdiff_t size_ = 0;
	double* data_ = nullptr;
	int capacity_ = 0;

public:
	ArrayD() = default;
	ArrayD(const ArrayD& rhs);
	ArrayD(const std::ptrdiff_t size);
	ArrayD& operator=(const ArrayD& rhs);
	~ArrayD();
	
	[[nodiscard]] double& operator[](std::ptrdiff_t i);
	[[nodiscard]] const double& operator[](const std::ptrdiff_t i) const;
	[[nodiscard]] std::ptrdiff_t ssize() const noexcept;

	void resize(const std::ptrdiff_t size);
	void insert(const std::ptrdiff_t& i, const double& x);
	void remove(const int& i);

	std::istream& ReadFrom(std::istream& istrm);
	std::ostream& WriteTo(std::ostream& ostrm);
};

std::ostream& operator<<(std::ostream& ostrm, ArrayD& array);
std::istream& operator>>(std::istream& istrm, ArrayD& array);
