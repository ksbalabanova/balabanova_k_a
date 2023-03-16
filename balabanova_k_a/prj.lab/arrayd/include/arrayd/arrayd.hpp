#include<ostream>
#include<cstdeff>

class ArrayD {
private:
	std::ptrdiff_t ssize_ = 0;
	double* data_ = nullptr;
	int capacity_ = 0;

public:
	ArrayD();
	ArrayD(const ArrayD& rhs);
	ArrayD(const std::ptrdiff_t size);
	ArrayD operator=(const ArrayD& rhs);
	~ArrayD();
	void resize(std::ptrdiff_t size);
	double& operator[](std::ptrdiff_t i);
	std::ptrdiff_t 	size() const;

};
inline ostream& operator <<(ostream& ostr, ArrayD rhs) {
	for (int i = 0; i < rhs.ssize_(); ++i) {
		std::count << rhs[i] << ' ';
	}
	return ostrm;
}

