#include "Table.h"

Table::Table()
{
	maxRow = 1;
	maxCol = 1;
	lenOfMaxCols = new int[10];
	rows = new Row(maxRow);
}

int Table::getMaxRow() const
{
	return maxRow;
}
const char* Table::getCellOnRow(int row, int col) const
{
	return rows[row].get_cell_str(col);
}
Row* Table::getRows() const
{
	return rows;
}

void Table::addRow(int numOfRow)
{
	if (maxRow <= numOfRow)
	{
		Row* new_cells = new Row[numOfRow + 1];

		for (int i = 0; i < maxRow; i++)
		{
			new_cells[i] = rows[i];
		}
		delete[] rows;

		rows = new Row[numOfRow + 1];
		rows = new_cells;

		maxRow = numOfRow + 1;

		rows[numOfRow] = *new Row(numOfRow);
	}

	fill_empty_cells();
}

void Table::edit(const String& value, int row, int col)
{
	if (maxRow <= row)
	{
		addRow(row);
		rows[row].edit_cell(value, col);

		maxRow = row + 1;
	}
	else
		rows[row].edit_cell(value, col);

	if (maxCol < rows[row].get_capacity())
		maxCol = rows[row].get_capacity();
}


bool Table::calculate_cell_num_value(const char* cell, double& result, int& ind) {
	int pos_dot = 0;
	bool dot = false;
	int digit = 0;
	int i = 0;
	for (; (cell[i] >= '0' && cell[i] <= '9') || (cell[i] == '.'); i++)
	{
		if (cell[i] == '.')
		{
			dot = true;
			pos_dot = i;
			break;
		}
		digit = cell[i] - '0';
		result = result * 10 + digit;
	}
	
	if (cell[i] != ' ' && cell[i] == '.' && cell[i] != '\n')
		return false;
	
	if (dot)
	{
		for (int j = 1; (cell[i] >= '0' && cell[i] <= '9') || (cell[i] == '.'); i++, j++)
		{
			if (cell[i] == '.') {
				std::cout << "Invalid number. The dots can't be more than one or a number can't start with a dot." << std::endl;
				return false;
			}
				return false;
			digit = cell[i] - '0';
			result = result + (digit / (pow(10, j)));

		}
		if (cell[i] != ' ' && cell[i] != '\n')
			return false;
	}
	ind += i;
	return true;

}
bool Table::calculate_cell_ref_value(const char* cell, double& result, int& ind) {
	int i = 1; // Start after R
	int row = 0;
	int col = 0;
	int digit = 0;
	for (; cell[i] >= '0' && cell[i] <= '9'; i++)
	{
		digit = cell[i] - '0';
		row = row * 10 + digit;
	}
	if (cell[i] != 'C')
		return false;
	i++;
	digit = 0;
	for (; cell[i] >= '0' && cell[i] <= '9'; i++)
	{
		digit = cell[i] - '0';
		col = col * 10 + digit;
	}
	if (row > maxRow - 1 || col > maxCol - 1)
	{
		result = 0;
		std::cout << "Invalid cell. Value is 0!" << std::endl;
		return true;
	}
	else
	{
		if (rows[row].is_formula(col))
			calculateFormulaCellsReference(row, col, result);
		else
			result = rows[row].get_cell_num_value(col);
	}
	ind += i;
	return true;
}


bool Table::calculateFormulaCellsReference(int row, int col, double& res)
{
	int len = strlen(rows[row].get_cell_str(col));
	const char* cell = rows[row].get_cell_str(col);

	double lhsCell = 0;
	double rhsCell = 0;

	char Operator = 'a';
	int dots = 0;
	bool l_cal = false;
	bool r_cal = false;
	double temp_cell = 0;
	for (int i = 1; i < len; i++)
	{
		if (cell[i] > '0' && cell[i] < '9')
		{
			if (!calculate_cell_num_value(&cell[i], temp_cell, i))
				return false;
			if (!l_cal) {
				lhsCell = temp_cell;
				l_cal = true;
			}
			else
			{
				rhsCell = temp_cell;
				r_cal = true;
			}
			temp_cell = 0;
		}
		else if (cell[i] == 'R')
		{
			if (!calculate_cell_ref_value(&cell[i], temp_cell, i))
				return false;
			if (!l_cal) {
				lhsCell = temp_cell;
				l_cal = true;
			}
			else
			{
				rhsCell = temp_cell;
				r_cal = true;

			}
			temp_cell = 0;
		}
		else if (cell[i] == '*' || cell[i] == '^' || cell[i] == '/' || cell[i] == '+' || cell[i] == '-')
			Operator = cell[i];
		else if (!(cell[i] == ' '))
			return false;
		if (r_cal && l_cal)
			break;
	}


	if (Operator == '/' && rhsCell == 0)
		return false;
	else if (Operator == '+')
		 res = lhsCell + rhsCell;
	else if (Operator == '-')
		res = lhsCell - rhsCell;
	else if (Operator == '*')
		res = lhsCell * rhsCell;
	else if (Operator == '/')
		res = lhsCell / rhsCell;
	else if (Operator == '^')
		res = pow(lhsCell, rhsCell);
	return true;
}


int Table::findMaxLenOfCellInCols()
{
	int len = 0;
	int maxLen = 0;
	double res = 0;
	lenOfMaxCols = new int[maxCol];

	for (int col = 1; col < maxCol; col++)
	{
		len = 0;
		maxLen = 0;
		for (int row = 1; row < maxRow; row++)
		{
			if (rows[row].get_is_empty())
				len = 0;

			else if (rows[row].is_formula(col))
			{
				if (!calculateFormulaCellsReference(row, col, res))
				{
					len = 5;
					continue;
				}
				calculateFormulaCellsReference(row, col, res);
				if (!((int)res == res))
				{
					res = round(res * 100 + 0.5) / 100;
					len = lenOfNum((int)res) + 2;
				}
				else
					len = lenOfNum((int)res);
			}

			else
			{
				len = strlen(rows[row].get_cell_str(col));
				if (rows[row].get_cell_str(col)[0] == '"' && rows[row].get_cell_str(col)[len - 1] == '"')
				{
					if (rows[row].get_cell_str(col)[2] == '"' && rows[row].get_cell_str(col)[len - 2] == '"' &&
						rows[row].get_cell_str(col)[1] == '\\' && rows[row].get_cell_str(col)[len - 3] == '\\')
						len = len - 4;
					else
						len = len - 2;
				}
			}
			if (maxLen < len)
				maxLen = len;
		}
		lenOfMaxCols[col] = maxLen;
	}
	return maxLen;
}
void Table::fill_empty_cells()
{
	for (int i = 0; i < maxRow; i++)
	{
		if (rows[i].get_is_empty())
			continue;
		for (int j = rows[i].get_capacity(); j < maxCol; j++)
			rows[i].edit_cell(Cell().get_value(), j);
	}
}

void Table::print()
{
	int len = 0;

	fill_empty_cells();
	findMaxLenOfCellInCols();

	for (int i = 1; i < maxRow; i++)
	{
		for (int j = 1; j < maxCol; j++)
		{
			double res = 0;

			if (rows[i].get_is_empty())
				break;

			if (rows[i].is_formula(j))
			{
				if (!calculateFormulaCellsReference(i, j, res))
				{
					std::cout << "ERROR | ";
					len = 5;
					continue;
				}
				calculateFormulaCellsReference(i, j, res);
				if (!((int)res == res))
				{
					res = round(res * 100 + 0.5) / 100;
					len = lenOfNum((int)res) + 2;
				}
				else
					len = lenOfNum((int)res);
				std::cout << res;
			}
			else
			{
				rows[i].print_cell(j);
				len = strlen(rows[i].get_cell_str(j));
			}
			for (int k = 0; k < lenOfMaxCols[j] - len; k++)
			{
				std::cout << ' ';
			}
			if (j != maxCol - 1)
				std::cout << " | ";
		}
		std::cout << std::endl;
	}
}