#include <iostream>
#include <cstddef>

template<typename T>
class ArrayT{
private:
	std::ptrdiff_t ssize_ = 0;
	T* data_ = nullptr;
	int capacity_ = 0;

public:
	ArrayT() = default;
	ArrayT(const ArrayT& rhs);
	ArrayT(const std::ptrdiff_t size = 0);
	T operator=(const ArrayT<T>& rhs);
	~ArrayT();

	[[nodiscard]] T& operator[](std::ptrdiff_t i);
	[[nodiscard]] const T& operator[](const std::ptrdiff_t i) const;
	[[nodiscard]] std::ptrdiff_t size() const noexcept;

	void resize(const std::ptrdiff_t size);
	void insert(const std::ptrdiff_t& i,const T& x);
	void remove(const int& i);

	std::istream& ReadFrom(std::istream& istrm);
	std::ostream& WriteTo(std::ostream& ostrm);
};

template<typename T>
ArrayT<T>::ArrayT<T>(const ArrayT<T>& rhs) {
	ssize_ = rhs.ssize_;
	data_ = rhs.data_;
	capacity_ = rhs.capacity_;
	if (ssize_ != 0) {
		data_ = new T[ssize_];
	}
	else {
		data_ = 0;
	}
	for (int i = 0; i < ssize_; ++i) {
		data_[i] = rhs.data_[i];
	}
}

template<typename T>
ArrayT<T>::ArrayT<T>(const std::ptrdiff_t size) {
	ssize_ = size;
	capacity_ = size;
	if (ssize_ != 0) {
		data_ = new T[ssize_];
	}
	else {
		data_ = 0;
	}
	for (int i = 0; i < ssize_; ++i) {
		data_[i] = 0.0;
	}
}

template<typename T>
T ArrayT<T>::operator=(const ArrayT& rhs) {
	if (this != &rhs) {
		delete[] data_;
		ssize_ = rhs.ssize_;
		capacity_ = rhs.capacity_;
		data_ = new T[capacity_];
		for (int i = 0; i < capacity_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
	return *this;
}

template<typename T>
ArrayT<T>::~ArrayT<T>() {
	delete[] data_;
}


template<typename T>
[[nodiscard]] const T& ArrayT<T>::operator[](std::ptrdiff_t i) const {
	if (i < 0 || ssize_ < i) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}

template<typename T> 
[[nodiscard]] T& ArrayT<T>::operator[](const std::ptrdiff_t i) {
	if (i < 0 || ssize_ < i) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}

template<typename T> 
[[nodiscard]] std::ptrdiff_t ArrayT<T>::size() const noexcept {
	return ssize_;
}



template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t size) {
	if (size <= 0) {
		throw std::invalid_argument("New size must be greater than 0");
	}
	if (size > ssize_) {
		std::ptrdiff_t capacity = 0;
		if (size >= ssize_ * 2) {
			capacity = size;
		}
		else {
			capacity = ssize_ * 2;
		}
		T* data = new T[capacity];
		for (int i = 0; i < ssize_; ++i) {
			data[i] = data_[i];
		}
		for (int i = ssize_; i < size; ++i) {
			data[i] = 0.0;
		}
		delete[] data_;
		data_ = data;
		capacity_ = capacity;
		ssize_ = size;
	}
}

template<typename T>
void ArrayT<T>::insert(const std::ptrdiff_t& i, const T& x) {
	if (i < 0 || i > ssize_) {
		throw std::invalid_argument("index doesn't exist");
	}
	ssize_ += 1;
	T* old = data_;
	data_ = new T[ssize_];
	for (int j = 0; j < i; ++j) {
		data_[j] = old[j];
	}
	data_[i] = x;
	for (int j = i + 1; j < ssize_; ++j) {
		data_[j] = old[j - 1];
	}
	delete[] old;
}

template <typename T> 
void ArrayT<T>::remove(const int& i) {
	if (i < ssize_) {
		if (ssize_ > 1) {
			for (int j = i; j < ssize_ - 1; ++j) {
				data_[j] = data_[j + 1];
			}
		}
		ssize_ -= 1;
	}
}


template <typename T> 
std::istream& ArrayT<T>::ReadFrom(std::istream& istrm) {
	if (ssize_ > 0) {
		int i = 0;
		T xi = 0;
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

template <typename T> 
std::ostream& ArrayT<T>::WriteTo(std::ostream& ostrm) {
	if (ssize_ > 0) {
		int i = 0;
		while (ostrm.good() && i < ssize_) {
			ostrm << data_[i] << " ";
			i++;
		}
	}
	return ostrm;
}

template <typename T> 
std::ostream& operator<<(std::ostream& ostrm, const ArrayT<T>& array) {
	return array.WriteTo(ostrm);
}

template <typename T> 
std::istream& operator>>(std::istream& istrm, ArrayT<T>& array) {
	return array.ReadFrom(istrm);
}
