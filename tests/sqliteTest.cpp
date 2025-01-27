#include "sqlite3.h"
#include <iostream>

int main(int argc, char *argv[]) {
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("example.db", &DB); // using file as database pointer adress

  if (exit) {
    std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl;
    return (-1);
  } 
  else {
    std::cout << "Opened DB sucessfully\n";
  }
  return 0;
}
