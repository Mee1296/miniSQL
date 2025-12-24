# MiniSQL
**a small SQL-like storage engine implemented in C++.**
- **Purpose:**: Simple database engine for storing tables and rows with a minimal SQL-like interface and on-disk serialization.

**Build & Run**
- **Important:**Make sure you have CMake installed. if not, visit https://cmake.org/download/
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
- **Project entry:** The `src/main.cpp` is still under construction.
- **Data files:** Persistent data is stored under the `data/` folder (catalog, schema, users metadata).

**Column Types (allowed)**
- **INT:** 32-bit integer.
- **TEXT:** Variable-length text; specify a length when storing/serializing.
- **DOUBLE:** 64-bit floating point number.
- **BOOLEAN:** Boolean values (true/false).

**Examples**
- **Create a table (conceptual):** Define columns using the allowed types. Example schema description:

- **Table name:** users
- **Columns:** id(INT), name(TEXT), balance(DOUBLE), active(BOOLEAN)

- **Serialize / load:** The storage and serializer modules in `src/storage/` handle converting rows to/from disk format.

**Where to look in the source**
- **Main:** `src/main.cpp`
- **Catalog:** `src/catalog/catalog.cpp` and `include/catalog/catalog.h`
- **Storage & serializer:** `src/storage/serializer.cpp`, `src/storage/storage_io.cpp`, and `include/storage/*`
- **Utilities:** `src/util/*` and `include/util/*`
