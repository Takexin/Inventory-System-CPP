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
int idResultQuery(sqlite3_stmt *stHandle, int iCol){
  int verifier = sqlite3_column_int(stHandle, iCol);
  if(verifier == NULL){
    std::cout << "Search unsucessfull, try again";
  }
  else{
    return verifier
  }
  return -1;
}

int searchItem(sqlite3 *DB, std::string objectName){
  int searchResult = 0;
  std::string statement = "SELECT id FROM items WHERE name = '" ;
  statement.append(objectName);
  statement.append("'");
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      searchResult = idResultQuery(preparedObject, 0);
      terminatePrepared(preparedObject);
    }
  }
}
