#include <iostream>
#include "apiDB.hpp"

int main(int argc, char *argv[]) {
  sqlite3 *DB;
  int exit = 0;
  exit =
      sqlite3_open("inventory.db", &DB);

  if (exit) {
    std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl;
    return (-1);
  } else {
    std::cout << "Opened DB sucessfully\n";
  }
  //category table (id and name)
  std::string catStatement = "CREATE TABLE categories(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL)";
  sqlite3_stmt *preparedObject = prepareItemObject(DB, catStatement);
  if(preparedObject != nullptr){
    bool stepVerifier = stepItemObject(preparedObject);
    if(stepVerifier != false){
      terminatePrepared(preparedObject);
    }
  }
  else{
    std::cout << sqlite3_errmsg(DB) << '\n';
  }
  //item table (id, name, quantity, price, category_id)
  std::string itemStatement = "CREATE TABLE items(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, quantity INTEGER, price REAL, category_id INTEGER, FOREIGN KEY(category_id) REFERENCES categories(id)) ";
  preparedObject = prepareItemObject(DB, itemStatement);
  if(preparedObject != nullptr){
    bool stepVerifier = stepItemObject(preparedObject);
    if(stepVerifier != false){
      terminatePrepared(preparedObject);
    }
  }
  else{
    std::cout << sqlite3_errmsg(DB) << '\n';
  }
}
