#include <arrayd/arrayd.hpp>

void ArrayD::resize(std::ptrdiff_t size) {
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
		delete[] data_;
		data_ = data;
		capacity_ = capacity;
	}
	ssize_ = size;
}

double& ArrayD::operator[](std::ptrdiff_t i) {
	if (i < 0 || ssize_ < i) {
		throw;
	}
	return data_[i];
}

std::ptrdiff_t ArrayD::size() const{
	return ssize_;
}

ArrayD::ArrayD() {
	ssize_ = 0;
	data_ = nullptr;
	capacity_ = 0;
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
	ssize_ = size;
	capacity_ = size;
	if (ssize_ != 0) {
		data_ = new double[ssize_];
	}
	else {
		data_ = 0;
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