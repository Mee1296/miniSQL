#pragma once
#include <string>

class CommandExecutor {
public:
  void run(); // REPL loop
  void execute(const std::string &line);

private:
  void handleCreateTable(const std::string &command);
  void handleDropTable(const std::string &command);
  void handleShowTables();
  void handleInsert(const std::string &command);
  void handleSelect(const std::string &command);

  // helpers
  static std::string trim(const std::string &str);
};
