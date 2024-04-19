#include <gtest/gtest.h>
#include "MyExpression.h"
using namespace std;

TEST(TArithmeticExpression, not_a_word_in_Russian)
{
	string expr = "ё";
	ASSERT_ANY_THROW(TArithmeticExpression expression(expr));
}
TEST(TArithmeticExpression, can_get_operands)
{
	string expr = "a+b";
	TArithmeticExpression expression(expr);

	vector<string> v;
	v.push_back("a");
	v.push_back("b");

	ASSERT_EQ(v, expression.GetOperands());
}
TEST(TArithmeticExpression, can_get_infix)
{
	string expr = "a+b";
	TArithmeticExpression expression(expr);

	string str = "a + b ";

	ASSERT_EQ(str, expression.GetInfix());
}
TEST(TArithmeticExpression, can_get_postfix)
{
	string expr = "a + b";
	TArithmeticExpression expression(expr);

	string str = "a b + ";

	ASSERT_EQ(str, expression.GetPostfix());
}
TEST(TArithmeticExpression, can_calculate)
{
	string expr = "1+1";
	TArithmeticExpression expression(expr);
	
	map<string, double> values;

	ASSERT_EQ(2, expression.Calculate(values));
}
TEST(TArithmeticExpression, lesson_example)
{
	string expr = "(4+11-8/2*(7*3+4-7))*3";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(-171.0, expression.Calculate(values));
}
TEST(TArithmeticExpression, priority)
{
	string expr = "-sin(PI/2)+2+2*2/2!^2";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(2, round(expression.Calculate(values) * 100) / 100);
}
TEST(TArithmeticExpression, calculate_sin)
{
	string expr = "sin(PI/2)";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(1, round(expression.Calculate(values) * 100) / 100);
}
TEST(TArithmeticExpression, calculate_cos)
{
	string expr = "cos(PI/2)";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(0, round(expression.Calculate(values) * 100) / 100);
}
TEST(TArithmeticExpression, calculate_tg)
{
	string expr = "tg(PI/4)";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(1, round(expression.Calculate(values) * 100) / 100);
}
TEST(TArithmeticExpression, calculate_ctg)
{
	string expr = "ctg(PI/4)";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(1, round(expression.Calculate(values) * 100) / 100);
}
TEST(TArithmeticExpression, calculate_factorial)
{
	string expr = "5!";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(120, expression.Calculate(values));
}
TEST(TArithmeticExpression, unary_minus)
{
	string expr = "-1";
	TArithmeticExpression expression(expr);

	ASSERT_EQ("-1 ", expression.GetInfix());
	ASSERT_EQ("1 ~ ", expression.GetPostfix());

	map<string, double> values;
	EXPECT_EQ(-1, expression.Calculate(values));
}
TEST(TArithmeticExpression, pow)
{
	string expr = "5*2^2";
	TArithmeticExpression expression(expr);

	map<string, double> values;
	EXPECT_EQ(20, expression.Calculate(values));
}
TEST(TArithmeticExpression, multicharacter_lexem)
{
	string expr = "ans+row";
	TArithmeticExpression expression(expr);

	ASSERT_EQ("ans + row ", expression.GetInfix());
	ASSERT_EQ("ans row + ", expression.GetPostfix());
}
TEST(TArithmeticExpression, another_brackets)
{
	string expr = "([{ans+row}])";
	ASSERT_NO_THROW(TArithmeticExpression expression(expr));
	TArithmeticExpression expression(expr);
	ASSERT_EQ("( [ { ans + row } ] ) ", expression.GetInfix());
	ASSERT_EQ("ans row + ", expression.GetPostfix());
}
TEST(TArithmeticExpression, isValidExpression)
{
	string expr = "([{ans+row]})";
	ASSERT_ANY_THROW(TArithmeticExpression expression(expr));
	expr = "([{ans+row})";
	ASSERT_ANY_THROW(TArithmeticExpression expression(expr));
	expr = "ans+row&)";
	ASSERT_ANY_THROW(TArithmeticExpression expression(expr));
	expr = "ans+row row";
	ASSERT_ANY_THROW(TArithmeticExpression expression(expr));
	expr = "ans+";
	ASSERT_ANY_THROW(TArithmeticExpression expression(expr));
}
