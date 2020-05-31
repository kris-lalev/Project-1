@mainpage Short description and main idea of the project

The project is focused on working with electronic tables. It allows you to create a table with undetermined number of
cells,which content can be of types string("Can be a number"), quote("\"SMH "\"), formula( = R1C1 + R2C2), number(123). 

The puprose of the project provide the an interface to work with electronic tables, giving him the opportunity to make calculations 
and save data using the built-in functions in it. The table has build-in input verification so if the user makes
mistakes in the calculations such as: using a string instead of a number, input of invalid values, division by zero, etc.
they will be corrected.

###Object- oriented design

It's widely known that one of the biggest advantages of *Object-Oriented programming* is *code reuse* which is
possible due to the *relationship* between classes.
This project uses a **has-a relationship** type of realtionship. The classes are constructed with the following relations:
- Each *row* in the table is a unlimited majority of cells. The best way to create Class Row is to make 
it have data member(dynamically allocated aray or vector) which elements are objects of type Cell.

- A *table* is a unlimited set of rows, ordered in a specific way, as well. It has 
a data member(dynamically allocated aray or vector) which elements are objects of type Row.

**In conclution**, the e-table is, some kind of matrix composed of objects of type Row wcich are themselves composed of 
objects of type Cell creating a virtual matrix.