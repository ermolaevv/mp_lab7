TArithmeticExpression::TArithmeticExpression(std::string& infix) : infix(infix)
{
	IsValidExpression();
	ToInfix();
	ToPostfix();
}

std::vector<std::string> TArithmeticExpression::Parse(const std::string& inp, TypeParse type)
{	
	std::vector<std::string> lexems;
	std::string tmp = "";

	switch (type)
	{
	case INFIX:
		for (char c : inp) {
			if (std::regex_match(std::string(1, c), std::regex("[\\w\\d\\.\\,]"))) {
				if (c == ',')
					tmp += '.';
				else
					tmp += c;
			}
			else {
				if (tmp != "")
					lexems.push_back(tmp);
				if (c != 32) {
                    if ((c == '/') && lexems.back() == "/") {
                        lexems.pop_back();
                        lexems.push_back("//");
                    }
					else if ((c == '-') && (lexems.size() == 0 || priority.count(lexems.back()))) {
						lexems.push_back("~");
					}
					else if (priority.count(std::string(1, c))) {
						lexems.push_back(std::string(1, c));
					}
					else {
						throw std::logic_error(
							std::format("Unresolve symbol at {}/{}", this->infix.find(std::string(1, c)) + 1, this->infix.size()));
					}
				}
				tmp = "";
			}
		}
		if (tmp != "")
			lexems.push_back(tmp);
		break;
	case POSTFIX:
		std::stringstream sinp(inp);
		while (sinp >> tmp)
			lexems.push_back(tmp);
		break;
	}
	return lexems;
}

void TArithmeticExpression::ToPostfix() {
	auto lexems = Parse(infix, INFIX);
	TStack<std::string> st(lexems.size());
	std::string stackItem;
	for (std::string item : lexems) {
		if (std::regex_match(item, std::regex("[\\(\\[\\{]"))) {
			st.Push(item);
		}
		else if (std::regex_match(item, std::regex("[\\)\\]\\}]"))) {
			stackItem = st.TopView();
			st.Pop();
			std::string comp;
			if (item == ")") comp = "(";
			else if (item == "]") comp = "[";
			else comp = "{";
			while (stackItem != comp) {
				postfix += stackItem + " ";
				stackItem = st.TopView();
				st.Pop();
			}
		}
		else if (std::regex_match(item, std::regex("[\\+\\-\\*\\/\\!\\~\\^\\%\\=]|(//)|(sin)|(cos)|(tg)|(ctg)"))) {
			while (!st.IsEmpty()) {
				stackItem = st.TopView();
				st.Pop();
				if (priority.at(item) <= priority.at(stackItem))
					postfix += stackItem + " ";
				else {
					st.Push(stackItem);
					break;
				}
			}
			st.Push(item);
		}
		else {
			if (item == "PI") {
				postfix += item + " ";
			}
			else {
				try {
					double _ = std::stod(item);
				}
				catch (std::invalid_argument e) {
					operands.insert({ item, 0.0 });
				}
				postfix += item + " ";
			}
		} 
	}

	while (!st.IsEmpty()) {
		stackItem = st.TopView();
		st.Pop();
		postfix += stackItem + " ";
	}
}

void TArithmeticExpression::ToInfix()
{
	auto lexems = Parse(infix, INFIX);
	infix = "";
	for (auto lexem : lexems) {
		if (lexem == "~")
			infix += lexem;
		else
			infix += lexem + " ";
	}
}

std::vector<std::string> TArithmeticExpression::GetOperands() const
{
	std::vector<std::string> op;
	for (const auto& item : operands)
		op.push_back(item.first);
	return op;
}


double TArithmeticExpression::Calculate(const std::map<std::string, double>& values)
{
	for (auto& val : values)
	{
		try
		{
			operands.at(val.first) = val.second;
		}
		catch (std::out_of_range&) {}
	}
	double leftOperand, rightOperand;
	auto postfixLexems = Parse(postfix, POSTFIX);
	TStack<double> st(postfixLexems.size() + values.size());
	for (std::string lexem : postfixLexems )
	{	
		if (std::regex_match(lexem, std::regex("[\\+\\-\\/\\*\\^\\%\\=]|(//)"))) {
			double res = 0;
			rightOperand = st.TopView();
			st.Pop();
			leftOperand = st.TopView();
			st.Pop();

			if (lexem == "+") res = leftOperand + rightOperand;
			if (lexem == "-") res = leftOperand - rightOperand;
			if (lexem == "*") res = leftOperand * rightOperand;
			if (lexem == "^") res = std::pow(leftOperand, rightOperand);
			if (lexem == "/") {
				if (rightOperand == 0)
					throw std::logic_error("Divition by zero");
				res = leftOperand / rightOperand;
			}
            if (lexem == "//") {
                if (rightOperand == 0)
                    throw std::logic_error("Divition by zero");
                res = (int)leftOperand / (int)rightOperand;
            }
            if (lexem == "%") {
				if (rightOperand == 0)
					throw std::logic_error("Divition by zero");
				res = (int)leftOperand % (int)rightOperand;
			}
            if (lexem == "=") {
                auto round = [](double a, double d = 1000000000000) {return int(a * d + 0.5) / d; };
				res = round(leftOperand) == round(rightOperand);
			}
			st.Push(res);
		}
		else if (std::regex_match(lexem, std::regex("[\\!\\~]|(sin)|(cos)|(tg)|(ctg)")))
		{
			leftOperand = st.TopView();
			st.Pop();

			if (lexem == "!") 
				st.Push(std::tgamma(leftOperand + 1));
			if (lexem == "~") st.Push(-1 * leftOperand);
			if (lexem == "sin") st.Push(std::sin(leftOperand));
			if (lexem == "cos") st.Push(std::cos(leftOperand));
			if (lexem == "tg") st.Push(std::tan(leftOperand));
			if (lexem == "ctg") st.Push(std::cos(leftOperand) / std::sin(leftOperand));
		}
		else if (lexem == "PI") {
			st.Push(PI);
		}
		else {
			try {
				st.Push(std::stod(lexem));
			}
			catch (std::invalid_argument e){
				st.Push(operands[lexem]);
			}
		}
	}
	return st.TopView();
}

void TArithmeticExpression::IsValidExpression() {
	TStack<std::string> stack(this->infix.size());
	auto lexems = Parse(this->infix, INFIX);
	int operandBalance = 0;

	for (std::string lexem : lexems) {
		if (std::regex_match(lexem, std::regex("[\\(\\{\\[]"))) {
			stack.Push(lexem);
		}
		else if (std::regex_match(lexem, std::regex("[\\)\\]\\}]"))) {
			std::string openBracket;

			if (lexem == ")") openBracket = "(";
			if (lexem == "]") openBracket = "[";
			if (lexem == "}") openBracket = "{";

			if (stack.IsEmpty() || stack.TopView() != openBracket) {
				// Несоответствие скобок
				throw std::logic_error(
					std::format("Wrong bracket {} at {}/{}", lexem, this->infix.find(lexem)+1, this->infix.size()));
			}
			stack.Pop();
		}
		else if (priority.count(lexem)) {
			// Операторы допустимы
			if (std::regex_match(lexem, std::regex("[\\+\\-\\/\\*\\^\\=\\%]|(//)"))) 
				operandBalance--;
			continue;
		}
		else if (std::regex_match(lexem, std::regex("[\\d\\.\\w]+"))) {
			// Допустимые символы: буквы, цифры и точка (для десятичных чисел)
			operandBalance++;
			continue;
		}
		else {
			// Недопустимый символ
			throw std::logic_error(
				std::format("Unresolved symbol {} at {}/{}", lexem, this->infix.find(lexem) + 1, this->infix.size()));
		}
	}

	// Проверка на оставшиеся открывающие скобки
	if (!stack.IsEmpty()) {
		std::string closeBracket, lexem = stack.TopView();

		if (lexem == "(") closeBracket = ")";
		if (lexem == "[") closeBracket = "]";
		if (lexem == "{") closeBracket = "}";

		throw std::logic_error(
			std::format("Expected {0} at {1}/{1}", closeBracket, this->infix.size()) + "\n");
	}

	// Проверка на количество операндов
	if (operandBalance < 1) {
		throw std::logic_error("Too few operands");
	}
	else if (operandBalance > 1) {
		throw std::logic_error("Too many operands");
	}
}
