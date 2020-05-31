#include "Row.h"

Row::Row(int id)
{
	capacity = 4;
	cells = new Cell[capacity];
	this->id = id;
	is_empty = true;
}

Cell* Row::get_cells() const
{
	return cells;
}

bool Row::get_is_empty() const
{
	return is_empty;
}
const int Row::get_capacity() const
{
	return capacity;
}
const char* Row::get_cell_str(int index) const
{
	return cells[index].get_value_str();
}
const double Row::get_cell_num_value(int index) const
{
	return cells[index].str_to_num();
}
const String Row::get_cell_value(int index) const
{
	return cells[index].get_value();
}

bool Row::is_formula(int index) const
{
	if (cells[index].is_valid_num(cells[index].get_value()) == 2)
		return true;
	return false;
}

void Row::edit_cell(const String& value, int pos_cell)
{
	if (capacity > pos_cell)
	{
		cells[pos_cell] = *new Cell(value.get_str());
		is_empty = false;
		if (cells[pos_cell].is_valid_num(value) == -1)
			return;
	}
	else
	{
		Cell* new_cells = new Cell[pos_cell + 1];

		for (int i = 0; i < capacity; i++)
		{
			new_cells[i] = cells[i];
		}
		delete[] cells;

		cells = new Cell[pos_cell + 1];
		cells = new_cells;

		capacity = pos_cell + 1;

		cells[pos_cell] = *new Cell(value.get_str());
		is_empty = false;
		if (cells[pos_cell].is_valid_num(value) == -1)
			return;
	}
}

void Row::print_cell(int index) const
{
	cells[index].print();
}
void Row::print() const
{
	for (int i = 1; i < capacity; i++)
		print_cell(i);

	std::cout << std::endl;
}