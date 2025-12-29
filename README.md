# MiniSQL
**a small SQL-like storage engine implemented in C++.**
- **Purpose:**: Simple database engine for storing tables and rows with a minimal SQL-like interface and on-disk serialization.

**Build & Run**
- **Important:** Make sure you have CMake installed. if not, please visit https://cmake.org/download/
- **Build:** Create a build directory and run CMake then build with your generator. Example (Windows PowerShell):

```powershell
mkdir build
cd build
cmake ..
cmake --build .
```

- **Run:** After building, run the produced executable (example path):

```powershell
.\build\minisql.exe
```

**Usage**
- **Project entry:** The `src/main.cpp` is now allow create, view and drop tables.
- **Data files:** Persistent data is stored under the `data/` folder (catalog, schema, users metadata).
- **Note that each data file is now only append row, no header, no row pointer**

**Column Types (allowed)**
- **INT:** 32-bit integer.
- **TEXT:** Variable-length text; specify a length when storing/serializing.
- **DOUBLE:** 64-bit floating point number.
- **BOOLEAN:** Boolean values (true/false).

**Allow command** (case sensitive)
- **Create table:** CREATE TABLE table_name (column_name1 COLUMN_TYPE1, column_name2 COLUMN_TYPE2, ...)
- **View tables:** SHOW TABLE
- **INSERT:** INSERT INTO <table> VALUES (column1, column2, ...)
- **SELECT:** SELECT * FROM <table> *note that only allow * for now*

**Examples**
- **Create a table (conceptual):** Define columns using the allowed types. Example schema description:

- **Table name:** users
- **Columns:** id(INT), name(TEXT), balance(DOUBLE), active(BOOLEAN)

- **Serialize / load:** The storage and serializer modules in `src/storage/` handle converting rows to/from disk format.

- **Command:** CREATE TABLE users (id INT, name TEXT, balance DOUBLE, active BOOLEAN)

**Where to look in the source**
- **Main:** `src/main.cpp`
- **Catalog:** `src/catalog/catalog.cpp` and `include/catalog/catalog.h`
- **Storage & serializer:** `src/storage/serializer.cpp`, `src/storage/storage_io.cpp`, and `include/storage/*`
- **Utilities:** `src/util/*` and `include/util/*`
