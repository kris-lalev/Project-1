#include "Cell.h"

/// Objects of class Row are made up of cells.
class Row
{
private:
    Cell* cells; /**< Dynamically allocated array of objects of type Cell */
    int capacity;
    int id; /**< Unique number of each row */
    bool is_empty; /**< True by default. Used when printing, writing and reading from file. */

public:
    Row(int id = 0);

    /** Getters for the different data members. @see bool get_is_empty() const @see const int get_capacity() 
    * const @see const char* get_cell_str(int index) const @see const double get_cell_num_value(int index) const
    * @see const String get_cell_value(int index) const
    */
    Cell* get_cells() const;
     
    bool get_is_empty() const;
    const int get_capacity() const;
    const char* get_cell_str(int index) const; /**< Returns the value of cell on colum index as const char*. */
    const double get_cell_num_value(int index) const; /**< Returns the value of cell on colum index converted to a number. */
    const String get_cell_value(int index) const; /**< Returns the value of cell on colum index as object of type String. */

    
    bool is_formula(int index) const;/**< Checks if the cell is a formula @see int Cell::is_valid_num(const String& value) */

    /** Adds a cell at a certain position. Resizes the row if needed.
    */
    void edit_cell(const String& value, int pos_cell);

    void print_cell(int index) const;/**< Prints the value of cell on colum index . */
    void print() const;/**< Prints the row. */
};