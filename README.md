**Project Description**
- **Name:**: minisql — a small, learning-focused SQL-like storage engine implemented in C++.
- **Purpose:**: Simple database engine for storing tables and rows with a minimal SQL-like interface and on-disk serialization.

**Build & Run**
- **Build:**: Create a build directory and run CMake then build with your generator. Example (Windows PowerShell):

```powershell
mkdir build
cd build
cmake ..
cmake --build .
```

- **Run:**: After building, run the produced executable (example path):

```powershell
.\build\minisql.exe
```

**Usage**
- **Project entry:**: The `src/main.cpp` binary initializes the engine and accepts commands (see the source for supported CLI operations).
- **Data files:**: Persistent data is stored under the `data/` folder (catalog, schema, users metadata).

**Column Types (allowed)**
- **INT:**: 32-bit integer.
- **TEXT:**: Variable-length text; specify a length when storing/serializing.
- **DOUBLE:**: 64-bit floating point number.
- **BOOLEAN:**: Boolean values (true/false).

These types match the `ColumnType` enum in `include/storage/types.h`.

**Examples**
- **Create a table (conceptual):**: Define columns using the allowed types. Example schema description:

- **Table name:**: users
- **Columns:**: id(INT), name(TEXT), balance(DOUBLE), active(BOOLEAN)

- **Serialize / load:**: The storage and serializer modules in `src/storage/` handle converting rows to/from disk format.

**Where to look in the source**
- **Main:**: `src/main.cpp`
- **Catalog:**: `src/catalog/catalog.cpp` and `include/catalog/catalog.h`
- **Storage & serializer:**: `src/storage/serializer.cpp`, `src/storage/storage_io.cpp`, and `include/storage/*`
- **Utilities:**: `src/util/*` and `include/util/*`

**Notes & Next Steps**
- This README is a concise overview. For full usage (CLI commands, SQL-like syntax), inspect `src/main.cpp` and the `catalog`/`storage` implementations.
- If you want, I can add example CLI commands or a `USAGE.md` with exact command syntax and example datasets.