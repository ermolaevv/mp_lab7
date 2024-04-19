#include "MyStack.h"

template<class T>
TStack<T>::TStack(size_t size)
{
	if (size == 0)
		throw std::domain_error("Stack size = 0 throws Heap Curruption Error");

	this->size = size;
	this->top = 0;
	this->mas = new T[this->size]();
}

template<class T>
TStack<T>::TStack(TStack<T>& stack) noexcept
{
	this->size = stack.size;
	this->top = stack.top;
	this->mas = new T[this->size]();
	std::copy(stack.mas, stack.mas + stack.size, this->mas);
}

template<class T>
TStack<T>::~TStack() noexcept
{
	if (this->mas != nullptr) {
		delete[] this->mas;
		this->mas = nullptr;
	}

	this->size = 0;
	this->top = 0;
}

template<class T>
void TStack<T>::Push(T element)
{
	if (this->IsFull())
		throw std::logic_error("Stack overflow");
	this->mas[this->top++] = element;
}

template<class T>
void TStack<T>::Pop()
{
	if (this->IsEmpty())
		throw std::logic_error("Stack is empty");
	this->mas[--this->top] = T();
}

template<class T>
T TStack<T>::TopView()
{
	if (this->IsEmpty())
		throw std::logic_error("Stack is empty");
	return this->mas[this->top - 1];
}

template<class T>
size_t TStack<T>::GetSize() noexcept
{
	return this->size;
}

template<class T>
size_t TStack<T>::GetTop() noexcept
{
	return this->top;
}

template<class T>
bool TStack<T>::IsFull() noexcept
{
	return this->top == this->size;
}

template<class T>
bool TStack<T>::IsEmpty() noexcept
{
	return this->top == 0;
}

template<class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& stack) noexcept
{
	if (this == &stack)
		return *this;

	if (this->size != stack.size) {
		if (this->mas != nullptr)
			delete[] this->mas;

		this->size = stack.size;
		this->mas = new T[this->size]();
	}
	
	this->top = stack.top;
	std::copy(stack.mas, stack.mas + stack.size, this->mas);

	return *this;
}
