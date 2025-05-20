#pragma once

#include <cstring>
#include <fstream>

template <typename T>
class ArrayView
{
public:

	ArrayView(const T* arr) = delete;
	ArrayView(const T* arr, size_t size);

	const T& operator[](size_t index) const;

	template <typename F>
	friend std::ostream& operator<<(std::ostream& os, const ArrayView<F>& view);

	size_t getSize() const;

	bool isEmpty() const;

	ArrayView<T> subArr(unsigned beginIndex) const;
	ArrayView<T> subArr(unsigned beginIndex, size_t size) const;

private:
	const T* begin;
	const T* end;
};

template <typename T>
ArrayView<T>::ArrayView(const T* arr, size_t size) : begin(arr), end(arr + size) {}

template <>
ArrayView<char>::ArrayView(const char* arr) : ArrayView(arr, strlen(arr)) {}

template <typename T>
const T& ArrayView<T>::operator[](size_t index) const
{	
 	return begin[index];
}

template <typename T>
size_t ArrayView<T>::getSize() const
{
	return end - begin;
}

template <typename T>
bool ArrayView<T>::isEmpty() const
{
	return getSize() == 0;
}

template <typename F>
std::ostream& operator<<(std::ostream& os, const ArrayView<F>& view)
{
	const F* iter = view.begin;

	while (iter != view.end)
	{
		os << *iter;
		iter++;
	}

	return os;
}

template <typename T>
ArrayView<T> ArrayView<T>::subArr(unsigned beginIndex) const
{
	if (beginIndex > getSize())
	{
		throw std::invalid_argument("Cannot create subview with larger starting index than the original view");
	}

	return ArrayView<T>(begin + beginIndex, getSize() - beginIndex);
}

template <typename T>
ArrayView<T> ArrayView<T>::subArr(unsigned beginIndex, size_t size) const
{
	if (beginIndex + size > getSize())
	{
		throw std::invalid_argument("Cannot create subview with larger scope than the original view");
	}

	return ArrayView<T>(begin + beginIndex, size);
}
