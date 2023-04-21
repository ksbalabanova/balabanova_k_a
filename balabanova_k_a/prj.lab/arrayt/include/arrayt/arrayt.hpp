#include <iostream>
#include <cstddef>

template<typename T>
class ArrayT{
private:
	std::ptrdiff_t size_ = 0;
	T* data_ = nullptr;
	int capacity_ = 0;

public:
	ArrayT() = default;
	ArrayT(const ArrayT& rhs);
	ArrayT(const std::ptrdiff_t size);
	ArrayT<T>& operator=(const ArrayT<T>& rhs);
	~ArrayT();

	[[nodiscard]] T& operator[](std::ptrdiff_t i);
	[[nodiscard]] const T& operator[](const std::ptrdiff_t i) const;
	[[nodiscard]] std::ptrdiff_t ssize() const noexcept;

	void resize(const std::ptrdiff_t size);
	void insert(const std::ptrdiff_t& i,const T& x);
	void remove(const int& i);

	std::istream& ReadFrom(std::istream& istrm);
	std::ostream& WriteTo(std::ostream& ostrm);
};

template<typename T>
ArrayT<T>::ArrayT(const ArrayT<T>& rhs) {
	size_ = rhs.size_;
	capacity_ = rhs.capacity_;
	if (capacity_ > 0) {
		data_ = new T[capacity_];
		for (std::ptrdiff_t i = 0; i < size_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
	else {
		data_ = nullptr;
	}
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size) {
	if (size < 0) {
		throw std::invalid_argument("Size of the new array must be greater than 0");
	}
	if (size > 0) {
		resize(size);
	}
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs) {
	if (this != &rhs) {
		delete[] data_;
		size_ = 0;
		capacity_ = 0;
		data_ = nullptr;
		if (rhs.capacity_ > 0) {
			data_ = new T[rhs.capacity_];
			capacity_ = rhs.capacity_;
			for (std::ptrdiff_t i = 0; i < rhs.size_; ++i) {
				data_[i] = rhs.data_[i];
			}
		}
		size_ = rhs.size_;
	}
	return *this;
}

template<typename T>
ArrayT<T>::~ArrayT() {
	delete[] data_;
}


template<typename T>
[[nodiscard]] const T& ArrayT<T>::operator[](std::ptrdiff_t i) const {
	if (i < 0 || i >= size_) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}

template<typename T> 
[[nodiscard]] T& ArrayT<T>::operator[](const std::ptrdiff_t i) {
	if (i < 0 || i >= size_) {
		throw std::invalid_argument("index does not exist");
	}
	return data_[i];
}

template<typename T> 
[[nodiscard]] std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
	return size_;
}



template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t size) {
	if (size <= 0) {
		throw std::invalid_argument("New size must be greater than 0");
	}
	if (size <= size_) {
		size_ = size;
		return;
	}
	if (size > capacity_) {
		T* data = new T[size] {};
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

template<typename T>
void ArrayT<T>::insert(const std::ptrdiff_t& i, const T& x) {
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

template <typename T> 
void ArrayT<T>::remove(const int& i) {
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


template <typename T> 
std::istream& ArrayT<T>::ReadFrom(std::istream& istrm) {
	if (size_ > 0) {
		int i = 0;
		T xi = 0;
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

template <typename T> 
std::ostream& ArrayT<T>::WriteTo(std::ostream& ostrm) {
	if (size_ > 0) {
		int i = 0;
		while (ostrm.good() && i < size_) {
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
