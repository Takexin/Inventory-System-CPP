#include "sqlite3.h"
#include "item.hpp"
#include <iostream>
#include <string>



void terminatePrepared(sqlite3_stmt *pStmt){
  int verifier = sqlite3_finalize(pStmt);
  if(verifier != 0){
    std::cout << "Error in finalizing prepared statement \n";
  }
  else {
    std::cout << "finalized prepared statement sucessfully \n";
  }
}


sqlite3_stmt *prepareItemObject(sqlite3 *DB, std::string &statement){
  //handle object prepare statement 
  int nByte = -1;
  sqlite3_stmt *stHandle = nullptr;
  const char *pzTail = nullptr;
  int prepareStatement = sqlite3_prepare_v2(DB, statement.c_str(), nByte, &stHandle, &pzTail);
  std::cout << prepareStatement << '\n';
  if (prepareStatement != 0){
    std::cout << "prepared statement failed. \n";
    return nullptr;
  }
  else{
    std:: cout << "prepared statement was sucessfull. \n";
  }
  return stHandle;
}
bool stepItemObject(sqlite3_stmt *stHandle){
  int result = sqlite3_step(stHandle);
  if (result != 101){
    std::cout << "step failed. \n";
    return false;
  }
  else {
    std::cout << "step was sucessfull \n";
  }
  return true;
}

void createTable(sqlite3 *DB, std::string desiredStatement){
  sqlite3_stmt *preparedObject = prepareItemObject(DB, desiredStatement);
  if (preparedObject != nullptr) {
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      terminatePrepared(preparedObject);
    }
  }
}

void insertItemObject(sqlite3 *DB,item desiredItem){
  //assuming table rows (name, quantity, price, category)
  std::string statement = "INSERT INTO items(name, quantity, price, category_id) VALUES('";
  statement.append(desiredItem.getName());
  statement.append("',");
  statement.append(std::to_string(desiredItem.getQuantity()));
  statement.append(",");
  statement.append(std::to_string(desiredItem.getPrice()));
  statement.append(",'");
  statement.append(desiredItem.getCategory());
  statement.append("')");
  std::cout << statement << '\n'; 

    //TODO
    //EXECUTE FUNCTIONS ONLY IF PREVIOUS ROUTINE DID NOT FAIL
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      terminatePrepared(preparedObject);
    }
  }

}
int main(int argc, char *argv[]) {
  sqlite3 *DB;
  int exit = 0;
  exit =
      sqlite3_open("example.db", &DB); // using file as database pointer adress

  if (exit) {
    std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl;
    return (-1);
  } else {
    std::cout << "Opened DB sucessfully\n";
  }

  //create item object
  item testItem("Rope 15ft", 45,  14.40, "Rope equipment");
  insertItemObject(DB, testItem);



  //category id foreign key not included 
  //std::string tableCreationString = "CREATE TABLE items(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, quantity INT NOT NULL, price REAL, category_id TEXT)";
  //createTable(DB, tableCreationString);
  // sqlite3_exec(sqlite3*, const char *sql, sqlite_callback, void *data, char **errmsg);
  
  //use sqlite3_prepare_v2() instead of sqlite3_prepare() -- method for the current routine;

  //ALWAYS destroy prepared statement after using (avoiding memory leaks) - sqlite3_finalize();

  //use sqlite3_step() to evaluate the prepared statement aka.check for valid input
  //(must use one for each row in statement);

  //when using sqlite3_prepare_v2() multiple times, use sqlite3_reset() instead;
  
  return 0;
}
