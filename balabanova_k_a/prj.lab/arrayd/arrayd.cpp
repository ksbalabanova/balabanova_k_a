#include <arrayd/arrayd.hpp>

ArrayD::ArrayD(const ArrayD& rhs) {
	size_ = rhs.size_;
	capacity_ = rhs.capacity_;
	if (capacity_ > 0) {
		data_ = new double[capacity_];
		for (std::ptrdiff_t i = 0; i < size_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
	else {
		data_ = nullptr;
	}
}
ArrayD::ArrayD(const std::ptrdiff_t size) {
	if (size < 0) {
		throw std::invalid_argument("Size of the new array must be greater than 0");
	}
	if (size_ > 0) {
		resize(size);
	}	
}
ArrayD ArrayD::operator=(const ArrayD& rhs) {
	if (this != &rhs) {
		delete[] data_;
		size_ = 0;
		capacity_ = 0;
		data_ = nullptr;
		if (rhs.capacity_ > 0) {
			data_ = new double[rhs.capacity_];
			capacity_ = rhs.capacity_;
			for (std::ptrdiff_t i = 0; i < capacity_; ++i) {
				data_[i] = rhs.data_[i];
			}
		}
		size_ = rhs.size_;
	}
	return *this;
}
ArrayD::~ArrayD() {
	delete[] data_;
}

[[nodiscard]] double& ArrayD::operator[](const std::ptrdiff_t i) {
	if (i < 0 || i >= size_) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}
[[nodiscard]] const double& ArrayD::operator[](const std::ptrdiff_t i) const {
	if (i < 0 || i >= size_) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}
[[nodiscard]] std::ptrdiff_t ArrayD::ssize() const noexcept{
	return size_;
}

void ArrayD::insert(const std::ptrdiff_t& i, const double& x) {
	if (i < 0 || i > size_) {
		throw std::invalid_argument("index doesn't exist");
	}
	if (size_ == capacity_) {
		resize(size_ + 1);
	}
	if (size_ == 0) {
		data_[0] = x;
	}
	else {
		for (ptrdiff_t j = size_ - 1; j >= i; --j) {
			data_[j + 1] = data_[j];
		}
		data_[i] = x;
	}
	size_++;
}
void ArrayD::remove(const int& i) {
	if (size_ == 0) {
		return;
	}
	if (i < 0 || i >= size_) {
		throw std::invalid_argument("index does not exist");
	}
	for (int j = i; j < size_ - 1; ++j) {
		data_[j] = data_[j + 1];
	}
	size_--;
}
void ArrayD::resize(const std::ptrdiff_t size) {
	if (size <= 0) {
		throw std::invalid_argument("New size must be greater than 0");
	}
	if (size <= size_) {
		size_ = size;
		return;
	}
	if (size > capacity_) {
		double* data = new double[size] {};
		for (size_t i = 0; i < size_; ++i) {
			data[i] = data_[i];
		}
		delete[] data_;
		data_ = data;
		size_ = size;
		capacity_ = size * 2;
		return;
	}
	if (size <= capacity_) {
		size_ = size;
	}
}

std::istream& ArrayD::ReadFrom(std::istream& istrm) {
	if (size_ > 0) {
		int i = 0;
		double xi = 0;
		while (!istrm.eof() && istrm.good() && i < size_) {
			istrm >> xi;
			data_[i] = xi;
			i++;
		}
	}
	else {
		throw std::exception();
	}
	return istrm;
}
std::ostream& ArrayD::WriteTo(std::ostream& ostrm) {
	if (size_ > 0) {
		int i = 0;
		while (ostrm.good() && i < size_) {
			ostrm << data_[i] << " ";
			i++;
		}
	}
	return ostrm;
}

std::ostream& operator<<(std::ostream& ostrm, ArrayD& array) {
	return array.WriteTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, ArrayD& array) {
	return array.ReadFrom(istrm);
}
