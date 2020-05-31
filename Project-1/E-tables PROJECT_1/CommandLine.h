#include <fstream>
#include "Table.h"

using namespace std;

const int MAX_SIZE_OF_COMMAND = 8;
/// The user interface class.
class CommandLine
{
private:
	String file_name; /**< Name of the opened file(Undetermined length). */
	String value;
	Cell cell;
	Table table;

	char command[MAX_SIZE_OF_COMMAND];
	char letter;

	void set_name(String& sampleName);  /**< new_cells to set the name of a file. */

	/** 
	* The functions mentioned below are new_cellss for the realisation of the main command open().
	* Consequently, they are private member functions.
	* @see new_file() @see read_from_file()
	*/
	void copy_rolls_from_file(String& difffile_name); 
	void new_file(); /**< This function creates a new, empty file with the file_name global variable when open is used. */
	/**
	* Extracts the content of a file and creates a "virtual table" saved in global variable table. The user works with it and depending on
	* whether he wants to edit, save the changes in the current file or a new one or not save the changes at all, he uses the commands
	* edit(), save() , saveas() or close() respectively.
	*/
	void read_from_file(ifstream& file);

public:
	void add_command();
	/**
	* Below are the functions of the commands
	*/
	void edit();
	void save(String& file_name);
	void saveas();
	void close() const;
	void exit() const;
	void help() const;
	void help_table() const;

	void open();
};