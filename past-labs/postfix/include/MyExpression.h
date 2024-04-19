#ifndef _MY_EXPRESSION_
#define _MY_EXPRESSION_

#define PI 3.14
#include "../stack/include/MyStack.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <regex>
#include <format>

enum TypeParse {
	INFIX,
	POSTFIX
};

/*
	* Класс реализует базовые функции:
		– Получение, хранение и возврат исходной (инфиксной) формы
		– Преобразование в постфиксную форму
		– Возврат постфиксной формы
		– Вычисление арифметического выражения при заданных значениях операндов
	* Добавленные раширения функциональности:
		– Поддержа неодносимвольных имен операндов
		– Поддержка констант в выражении, как целых, так и вещественных (а также константа PI)
		– Поддержка унарных префиксных (например, унарный минус) и постфиксных (например, факториал) операций
		– Поддержка функций
			- sin
			- cos
			- tg
			- ctg
		– Возможность использовать разные виды скобок: (), {}, []
		- Анализ корректности выражения, c выдачей позиции и описания ошибки
	*/
class TArithmeticExpression
{
	
	static const std::map<std::string, int> priority;

	std::string infix;
	std::string postfix;
	std::map<std::string, double> operands;

	std::vector<std::string> Parse(const std::string& inp, TypeParse type);
	void ToPostfix();
	void ToInfix();
	void IsValidExpression();
public:
	TArithmeticExpression(std::string& infix);
	std::string GetInfix() const { return std::regex_replace(infix.data(), std::regex("~"), "-"); }
	std::string GetPostfix() const { return postfix; }
	std::vector<std::string> GetOperands() const;
	double Calculate(const std::map < std::string , double > & values);
};

#include "../src/Priority.hpp"
#include "../src/MyExpression.hpp"

#endif
