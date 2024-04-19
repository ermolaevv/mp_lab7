const std::map<std::string, int> TArithmeticExpression::priority = {
	{"(", 0},
	{"[", 0},
	{"{", 0},
	{")", 0},
	{"]", 0},
	{"}", 0},

	{"+", 1},
	{"-", 1},
	{"*", 2},
	{"/", 2},

	{"^", 3},
	{"~", 3},
	{"!", 3},

	{"sin", 4},
	{"cos", 4},
	{"tg", 4},
	{"ctg", 4},
};
