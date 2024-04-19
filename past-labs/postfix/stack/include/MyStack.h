#ifndef _MY_STACK_
#define _MY_STACK_

#include <iostream>

template <class T>
class TStack {
protected:
	size_t size;
	size_t top;
	T* mas;
public:
	TStack(size_t size = 1);
	TStack(TStack<T>& stack) noexcept;
	~TStack() noexcept;

	void Push(T element);
	void Pop();
	T TopView();
	
	size_t GetSize() noexcept;
	size_t GetTop() noexcept;

	bool IsFull() noexcept;
	bool IsEmpty() noexcept;

	TStack<T>& operator=(const TStack<T>& stack) noexcept;

	//операторы вводы и выводы
	friend std::ostream& operator<<(std::ostream& ostr, const TStack<T>& stack) noexcept{
		for (size_t i = 0; i < stack.size; i++) {
			ostr << i + 1 << ". " << stack.mas[i] << std::endl;
		}
		return ostr;
	}
	friend std::istream& operator>>(std::istream& istr, const TStack<T>& stack) noexcept{
		for (size_t i = 0; i < stack.size; i++) {
			istr >> stack.mas[i];
		}
		return istr;
	}
};

#include "../src/MyStack.hpp"

#endif
