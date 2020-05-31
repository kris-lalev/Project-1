#include "Row.h"
/// Objects of class Table are made up of Row-s and a table is like a virtual matrix of cells.
class Table
{
private:
	Row* rows; /**< Dynamically allocated array of objects of type Row */
	/** Dynamically allocated array which elements are the max lengths of cells from each column, the number of the
	* lowest row and the lenght of the biggest row
	*/
	int* lenOfMaxCols;
	int maxRow;
	int maxCol;

	/** The two functions mentioned below are private member functions because they are only used inside
	* calculateformulacellsreference(). Their purpose is to calculate the value of a cell be it number, formula or string
	* or reference to another cell.. The result and index(current position in formula) are passed by reference, because
	* their new values are needed in the main function. They return true or false depending on the success of the calculation. 
	*/
	/**
	* this function calculates the part of the formula which is a number. 
	*/
	bool calculate_cell_num_value(const char* cell, double& result, int& ind);
	/**
	* this function calculates the part of the formula which is reference to another cell.
	*/
	bool calculate_cell_ref_value(const char* cell, double& result, int& ind);	
	int findMaxLenOfCellInCols(); /**< Function to fill #lenOfMaxCols */
	/** Function to allign the table to the #maxRow and #maxCol */
	void fill_empty_cells(); 
	
public:
	Table();

	/**
	* Getters @see getCellOnRow() @see getRows()
	*/
	int getMaxRow() const;
	const char* getCellOnRow(int row, int col) const; /**< Getter cell on row and col. */
	Row* getRows() const;

	void addRow(int numOfRow); /**< Adding a row in the table by its position(starting from 1) */
	/** Function used in the CommandLine class to edit value of a cell.
	* Automatically creates the cell's colum and/or row if they don't exist 
	* and then fills the cell with <value>.
	*/
	void edit(const String& value, int row, int col); 
	/**
	* The main function that calculates the final result of a formula
	* @returns the final result and makes it the new value of the specified cell.
	* Splits the formula into two sides lhsCell and rhsCell and calculates them
	* (validats and converts to number or converted to 0, if the value was invalid).
	* Used in print() as validator and calculator.
	*/
	bool calculateFormulaCellsReference(int row, int col, double& res);
	/**
	* Function used in the CommandLine class to print the content of a table.
	*/
	void print();



};