#include "CommandLine.h"
#pragma warning (disable : 4996)

void CommandLine::add_command()
{
	cin >> command;
	cin.ignore();
}

void CommandLine::set_name(String& sampleName)
{
	while (true)
	{
		cin.get(letter);

		if (letter == ' ' || letter == '\n')
			break;

		sampleName.push_back(letter);
	}
}

void CommandLine::copy_rolls_from_file(String& file_name)
{
	ofstream file;
	file.open(file_name.get_str());

	int countOfRows = table.getMaxRow();

	for (int i = 1; i < countOfRows; i++)
	{
		if (!table.getRows()[i].get_is_empty())
		{
			int countOfCols = table.getRows()[i].get_capacity();

			for (int j = 1; j < countOfCols; j++)
			{
				int len = strlen(table.getCellOnRow(i, j));
				file.write(table.getCellOnRow(i, j), len);

				if (j != countOfCols - 1)
					file.write(",", sizeof(char));
			}
		}
		file.write("\n", sizeof(char));
	}

	file.close();
}
void CommandLine::new_file()
{
	ofstream newFile(file_name.get_str()); // Създаваме празен файл, както е по условие.
	cerr << "Such file doesn't exist. A new empty file with the given name was created for you" << std::endl;
	newFile.close();
}
void CommandLine::read_from_file(ifstream& file)
{
	file.open(file_name.get_str());

	char ch = 'a';
	int curr_row = 1;
	int curr_col = 1;

	String empty_str;
	Cell empty_cell;

	String temp_str;
	Cell temp_cell;
	Table temp_table;

	bool is_empty = true;

	while (true)
	{
		file.get(ch);

		if (file.eof())
			break;
		if (ch == '\n')
		{
			if (!is_empty)
			{
				temp_cell.set_value(temp_str.get_str());
				temp_cell.remove_spaces();
				temp_table.edit(temp_cell.get_value(), curr_row, curr_col);
			}

			curr_row++;
			curr_col = 1;

			temp_str = empty_str;
			temp_cell = empty_cell;

			is_empty = true;
		}

		else if (ch != ',')
		{
			temp_str.push_back(ch);
			is_empty = false;
		}
		else if (ch == ',')
		{
			temp_cell.set_value(temp_str.get_str());
			temp_cell.remove_spaces();
			temp_table.edit(temp_cell.get_value(), curr_row, curr_col);

			curr_col++;

			temp_str = empty_str;
			temp_cell = empty_cell;
		}
	}
	table = temp_table;
}

void CommandLine::edit()
{
	String temp_str;

	int row;
	cin >> row;
	cin.ignore();

	int col;
	cin >> col;
	cin.ignore();

	while (true)
	{
		cin.get(letter);

		if (letter == '\n')
			break;

		temp_str.push_back(letter);
		value.set_str(temp_str.get_str());
	}

	cell.set_value(value.get_str());

	if (cell.is_valid_num(temp_str) == -1)
	{
		std::cout << "Error: row:" << row << ", col:" << col << ", ";
		value.print();
		std::cout << " is unknown data type." << std::endl;
	}
	table.edit(cell.get_value(), row, col);
}

void CommandLine::save(String& file_name)
{
	copy_rolls_from_file(file_name);

	std::cout << "Successfully saved " << file_name.get_str() << std::endl;
}

void CommandLine::saveas()
{
	String userChosenfile_name; // Създаваме името на файла, в което потребителят иска да запише промените.

	set_name(userChosenfile_name);

	copy_rolls_from_file(userChosenfile_name);

	std::cout << "Successfully saved another " << userChosenfile_name.get_str() << std::endl;
}

void CommandLine::close() const
{
	std::cout << "Successfully closed" << " " << file_name.get_str();
}

void CommandLine::exit() const
{
	std::cout << "Exiting the program..." << std::endl;
}

void CommandLine::help() const
{
	std::cout << "The following commands are supported:" << std::endl;
	std::cout << "open <file>                opens <file>" << std::endl;
	std::cout << "close			            closes currently opened file" << std::endl;
	std::cout << "save			            saves the currently open file" << std::endl;
	std::cout << "saveas <file>	            saves the currently open file in <file>" << std::endl;
	std::cout << "help			            prints this information" << std::endl;
	std::cout << "exit			            exists the program" << std::endl;
}
void CommandLine::help_table() const
{
	std::cout << "edit <row> <col> <value>   edit cell on <row> and <col> with <value>*" << std::endl;
	std::cout << "print			            prints the table" << std::endl;
	help();
	std::cout << "*<value> can be string, quote, formula(= R1C2 + R1C3) or number" << std::endl;
}
void CommandLine::open()
{
	std::cout << "Write exit to stop the program." << std::endl;

	String empty_file_name;
	ifstream file;

	while (strcmp(command, "exit") != 0)
	{
		add_command();

		if (strcmp(command, "open") == 0)
		{
			set_name(file_name);

			file.open(file_name.get_str());

			if (file.fail())
			{
				new_file();

				file.open(file_name.get_str());
			}
			else
				std::cout << "Successfully opened " << file_name.get_str() << std::endl;

			file.close();

			read_from_file(file);

			while (true)
			{
				add_command();
				if (strcmp(command, "open") == 0)
					std::cout << "You have to close the file before opening another one." << std::endl;

				else if (strcmp(command, "save") == 0)
					save(file_name);

				else if (strcmp(command, "saveas") == 0)
					saveas();

				else if (strcmp(command, "close") == 0)
				{
					close();
					file.close();

					file_name = empty_file_name;
					break;
				}

				else if (strcmp(command, "exit") == 0)
				{
					exit();
					return;
				}

				else if (strcmp(command, "help") == 0)
					help_table();

				else if (strcmp(command, "edit") == 0)
					edit();

				else if (strcmp(command, "print") == 0)
					table.print();
			}
		}
	}
}