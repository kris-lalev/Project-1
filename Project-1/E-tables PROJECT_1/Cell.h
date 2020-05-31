#include "String.h"
//using namespace std;

/// The cells are an independent class and make up the table. 
class Cell
{
private:
	String value; /**< Type String because each cell could be initialized with a value which length is undetermined(number, formula, etc.). */

	/**
	* Private member functions.
	* They are used to help understand what is in the cell(number, quote
	* External access should't be allowed.
	* @see is_fractured
	*/
	bool is_valid(const char* str, int len, int i); 
	bool is_fractured(const char* str, int len);
public:
	/**
	* A default constructor and a constructor with parameters.
	* @see Cell(const char* str, int row, int col)
	*/
	Cell();
	Cell(const char* str);

	/**
	* Setter for the value of the cell.
	*/
	void set_value(const char* str);
	/**


	/**
	* Getters for the value of the cell. It can be returned as const char* or String depending on the needs of the user.
	* @see get_value() const
	*/
	const char* get_value_str() const;
	const String get_value() const;

	/**
	* The programmer needs the value of the cell to be as clear as possible.
	* So when a cell is read from a file, the unneccessary spaces are removed.
	* Nowever the spaces inside quote marks and formulas are kept to keep the value
	* of the cell intact. This is done by the remove_spaces(); function of the cell.
	*/
	void remove_spaces();

	/**
	* For the true vaule of the cell to be calculated, first its type is needed.
	* This function returns different integers according to the type.
	* -1(invalid), 0(string which is valid number), 1(valid number), 2(formula)
	*/
	int is_valid_num(const String& value);
	/**
	* Checks the return value of is_valid_num(const String& value) 
	* If it is either 0 or 1, converts it to number.
	* Else, returns 0.
	*/
	double str_to_num();

	void print() const; /**< Prints the value of the cell. Removes unnecessary quote marks*/
};


int lenOfNum(int num); /**< Returns the length of a number. */