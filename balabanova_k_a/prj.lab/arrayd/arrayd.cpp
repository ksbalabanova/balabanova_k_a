#include <arrayd/arrayd.hpp>

void ArrayD::resize(const std::ptrdiff_t size) {
	if (size <= 0) {
		throw std::invalid_argument("New size must be greater than 0");
	}
	if (size > ssize_) {
		int capacity = 0;
		if (size >= ssize_ * 2) {
			capacity = size;
		}
		else {
			capacity = ssize_ * 2;
		}
		double* data = new double[capacity];
		for (int i = 0; i < ssize_; ++i) {
			data[i] = data_[i];
		}
		for (int i = ssize_; i < size; ++i) {
			data[i] = 0;
		}
		delete[] data_;
		data_ = data;
		capacity_ = capacity;
		ssize_ = size;
	}
}

[[nodiscard]] double& ArrayD::operator[](std::ptrdiff_t i) {
	if (i < 0 || ssize_ < i) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}

[[nodiscard]] const double& ArrayD::operator[](const std::ptrdiff_t i) const {
	if (i < 0 || ssize_ < i) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}

[[nodiscard]] std::ptrdiff_t ArrayD::size() const noexcept{
	return ssize_;
}

ArrayD::ArrayD(const ArrayD& rhs) {
	ssize_ = rhs.ssize_;
	data_ = rhs.data_;
	capacity_ = rhs.capacity_;
	if (ssize_ != 0) {
		data_ = new double[ssize_];
	}
	else {
		data_ = 0;
	}
	for (int i = 0; i < ssize_; ++i) {
		data_[i] = rhs.data_[i];
	}
}
ArrayD::ArrayD(const std::ptrdiff_t size) {
	if (size < 0) {
		throw std::invalid_argument("Size of the new array must be greater than 0");
	}
	ssize_ = size;
	capacity_ = size;
	if (ssize_ != 0) {
		data_ = new double[ssize_];
	}
	else {
		data_ = 0;
	}
	for (int i = 0; i < ssize_; ++i) {
		data_[i] = 0.0;
	}
}

ArrayD ArrayD::operator=(const ArrayD& rhs) {
	if (this != &rhs) {
		delete[] data_;
		ssize_ = rhs.ssize_;
		capacity_ = rhs.capacity_;
		data_ = new double[capacity_];
		for (int i = 0; i < capacity_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
	return *this;
}
ArrayD::~ArrayD(){
	delete[] data_;
}

void ArrayD::insert(const std::ptrdiff_t& i, const double& x) {
	if (i < 0 || i > ssize_) {
		throw std::invalid_argument("index doesn't exist");
	}
	ssize_ += 1;
	double* old = data_;
	data_ = new double[ssize_];
	for (int j = 0; j < i; ++j) {
		data_[j] = old[j];
	}
	data_[i] = x;
	for (int j = i + 1; j < ssize_; ++j) {
		data_[j] = old[j - 1];
	}
	delete[] old;
}

void ArrayD::remove(const int& i) {
	if (i < ssize_) {
		if (ssize_ > 1) {
			for (int j = i; j < ssize_ - 1; ++j) {
				data_[j] = data_[j + 1];
			}
		}
		ssize_ -= 1;
	}
}

std::istream& ArrayD::ReadFrom(std::istream& istrm) {
	if (ssize_ > 0) {
		int i = 0;
		double xi = 0;
		while (!istrm.eof() && istrm.good() && i < ssize_) {
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
	if (ssize_ > 0) {
		int i = 0;
		while (ostrm.good() && i < ssize_) {
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
