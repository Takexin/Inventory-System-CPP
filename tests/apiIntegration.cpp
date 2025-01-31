#include "sqlite3.h"
#include "apiDB.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("example.db", &DB);

  if (exit) {
    std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl;
    return (-1);
  } 
  else {
    std::cout << "Opened DB sucessfully\n";
  }
  //assuming table rows (name, quantity, price, category_id)
  //creating testItem for integration
  //item testItem("testItem", 1,  1.0, "test");
  //insertItemObject(DB, testItem);


  std::string stString = "testItem";
  int returnValue = searchItem(DB, stString); 
  std::cout << "ID value of " << stString << ": " << returnValue << '\n';

  sqlite3_close(DB);
  return 0;
}
