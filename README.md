# SimpleDB
SimpleDB is a lightweight and easy-to-use Database Management System designed for educational purposes, providing fundamental database functionalities such as storage, retrieval, and basic SQL query processing. It aims to help developers and students understand the core concepts of database systems through a minimal and approachable implementation.

## Features
* Create Table: Define a new table with specified column names.
* Drop Table: Delete a table from the database.
* Use Table: Switch the active table for performing operations.
* Select Data: Retrieve data from a table based on specified conditions.
* Insert Data: Add new rows of data into the active table.
* Delete Data: Remove rows from the active table based on specified conditions.
* Update Data: Modify existing rows in the active table based on specified conditions.

## Command Grammar
The commands supported by SimpleDB follow this grammar:

* CREATE <table_name> WITH <column_name, ...>
* DROP <table_name>
* USE <table_name>
* QUIT: Exit the SimpleDB program.
* SELECT <column_name [ == || != || < || > || >= || <= ] value, ... || *>
* INSERT <column_name=val, ...>
* DELETE <column_name[ == || != || < || > || >= || <= ]value, ...>
* UPDATE <column_name[ == || != || < || > || >= || <= ]value, ... || *> WITH <column_name=value, ...>

## Usage

### Compiling and Running
To compile SimpleDB, use the provided compile.sh script. Ensure you have g++ installed.

```bash
./test/compile.sh
```

### Debugging
For debugging SimpleDB with gdb, use the debug.sh script after compilation.

```bash
./test/debug.sh
```

### Socket Usage
SimpleDB supports socket communication. Use the following command format:

```bash
./SimpleDB -p <port_number> || ./SimpleDB
```
Replace <port_number> with the desired port for socket communication.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
