#include "Cell.h"

Cell::Cell()
{
	value.set_str(" ");

}
Cell::Cell(const char* str)
{
	value.set_str(str);

}

void Cell::set_value(const char* str)
{
	value.set_str(str);
}

const char* Cell::get_value_str() const
{
	return value.get_str();
}
const String Cell::get_value() const
{
	return value;
}

bool Cell::is_valid(const char* str, int len, int i)
{
	for (; i < len - 1; i++)
	{
		if (!((str[i] == '.') && ((str[i] >= '0') || (str[i] <= '9'))))
			return 0;
	}
	return 1;
}
bool Cell::is_fractured(const char* str, int len)
{
	int dots = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '.')
			dots++;
	}
	if ((dots > 1) || (str[0] == '.') || (str[len - 1] == '.'))
		return 0;
	return 1;
}

void Cell::remove_spaces()
{
	String empty_cell;

	const char* mStr = value.get_str();
	int len = strlen(mStr);

	int last_quote = -1;
	int countOfR = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (mStr[i] == '"')
		{
			last_quote = i;
			break;
		}
	}

	for (int i = 0; i < len; i++)
	{
		if (mStr[i] == ' ')
			continue;
		if (mStr[i] == '=')
		{
			for (int j = i; j < len; j++)
			{
				if (mStr[j] == 'R')
					countOfR++;

				if (mStr[j] == ' ' && countOfR > 2)
					continue;
				else
					empty_cell.push_back(mStr[j]);
			}
			break;
		}
		else if (mStr[i] == '"')
		{
			for (int j = i; j <= last_quote; j++)
				empty_cell.push_back(mStr[j]);
			break;
		}
		else
			empty_cell.push_back(mStr[i]);
	}
	value = empty_cell;
}

int Cell::is_valid_num(const String& value)
{
	int len = strlen(value.get_str());
	const char* str = value.get_str();
	int start = 1;

	if (str[0] == '=')
		return 2;

	if ((str[0] == '"') && (str[len - 1] == '"'))
	{
		if ((str[1] == '+') || (str[1] == '-'))
		{
			if (!is_valid(str, len, start + 1))
				return -1;
		}

		else if ((str[1] != '+') && (str[1] != '-'))
		{
			if (!is_valid(str, len, start))
				return -1;
		}

		if (!is_fractured(str, len))
			return -1;
		return 0;
	}

	if ((str[0] >= '0') && (str[0] <= '9'))
	{
		int start = 0;

		if ((str[0] == '+') || (str[0] == '-'))
			start = 1;
		else if ((str[0] != '+') && (str[0] != '-'))
			start = 0;
		if (!is_valid(str, len + 1, start))
			return -1;

		if (!is_fractured(str, len))
			return -1;
	}	
	return 1;
}

double Cell::str_to_num()
{
	double number = 0;
	double digit = 0;
	int start = 0;
	int len = strlen(value.get_str());
	int isFract = 0;

	switch (is_valid_num(value))
	{
	case -1: return 0;
	case 0: start = 1; break;
	case 1: start = 0; break;
	case 2: return 0;
	default: break;
	}

	for (int i = start; i < len - 1; i++)
	{
		if (value.get_str()[i] == '.')
		{
			isFract = i;
			break;
		}
	}
	bool has_sign = false;
	bool sign = true;
	if (start)
	{
		if (value.get_str()[1] == '+')
		{
			has_sign = true;
			sign = true;
		}
		else if (value.get_str()[1] == '-')
		{
			has_sign = true;
			sign = false;
		}
	}
	if (!isFract)
	{
		for (int i = start + has_sign; i < len - start; i++)
		{
			digit = value.get_str()[i] - '0';
			number = number * 10 + digit;
		}
	}
	else
	{
		for (int i = start + has_sign; i < isFract; i++)
		{
			digit = value.get_str()[i] - '0';
			number = number * 10 + digit;
		}
		for (int i = isFract + 1, j = 1; i < len - start; i++, j++)
		{
			digit = value.get_str()[i] - '0';
			number = number + (digit / (pow(10, j)));
		}
	}
	return sign ? number : -number;
}

void Cell::print() const
{
	int len = strlen(value.get_str());
	if (value.get_str()[0] == '"' && value.get_str()[len - 1] == '"')
	{
		if (value.get_str()[2] == '"' && value.get_str()[len - 2] == '"' && value.get_str()[1] == '\\' && value.get_str()[len - 3] == '\\')
		{
			for (int i = 0; i < len; i++)
			{
				if (i != 2 && i != len - 2 && i != 1 && i != len - 3)
					std::cout << value.get_str()[i];
			}
		}
		else
		{
			for (int i = 1; i < len - 1; i++)
				std::cout << value.get_str()[i];
		}
	}
	else
		value.print();
}

int lenOfNum(int num)
{
	int numOfDigits = 0;
	while (num)
	{
		++numOfDigits;
		num /= 10;
	}
	return numOfDigits;
}