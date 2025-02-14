#include "item.hpp"
#include "sqlite3.h"
#include <string>

void terminatePrepared(sqlite3_stmt *pStmt) {
  int verifier = sqlite3_finalize(pStmt);
  if (verifier != 0) {
    std::cout << "Error in finalizing prepared statement \n";
  } else {
    std::cout << "finalized prepared statement sucessfully \n";
  }
}

sqlite3_stmt *prepareItemObject(sqlite3 *DB, std::string &statement) {
  // handle object prepare statement
  int nByte = -1;
  sqlite3_stmt *stHandle = nullptr;
  const char *pzTail = nullptr;
  int prepareStatement =
      sqlite3_prepare_v2(DB, statement.c_str(), nByte, &stHandle, &pzTail);
  std::cout << prepareStatement << '\n';
  if (prepareStatement != 0) {
    std::cout << "prepared statement failed. \n";
    return nullptr;
  } else {
    std::cout << "prepared statement was sucessfull. \n";
  }
  return stHandle;
}
bool stepItemObject(sqlite3_stmt *stHandle) {
  int result = sqlite3_step(stHandle);
  if (result != 101 && result != 100) {
    std::cout << "step failed. \n";
    return false;
  } else {
    std::cout << "step was sucessfull \n";
  }
  return true;
}

void createTable(sqlite3 *DB, std::string desiredStatement) {
  sqlite3_stmt *preparedObject = prepareItemObject(DB, desiredStatement);
  if (preparedObject != nullptr) {
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      terminatePrepared(preparedObject);
    }
  }
}
int idResultQuery(sqlite3_stmt *stHandle, int iCol) {
  int verifier = sqlite3_column_int(stHandle, iCol);
  if (!verifier) {
    std::cout << "Search unsucessfull, try again\n";
  } else {
    return verifier;
  }
  return -1;
}
int searchCat(sqlite3 *DB, std::string objectName) {
  int searchResult = -1;
  std::string statement = "SELECT id FROM categories WHERE name = ?1";
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    int bindHandle =
        sqlite3_bind_text(preparedObject, 1, objectName.c_str(), -1, nullptr);
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      searchResult = idResultQuery(preparedObject, 0);
      if (searchResult != -1) {
        terminatePrepared(preparedObject);
      } else {
        std::cout << sqlite3_errmsg(DB) << std::endl;
      }

    } else {
      std::cout << sqlite3_errmsg(DB) << '\n'; // don't mind the jank
    }
  }
  return searchResult;
}
int searchItem(sqlite3 *DB, std::string objectName) {
  int searchResult = -1;
  std::string statement = "SELECT id FROM items WHERE name = ?1";
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    int bindHandle =
        sqlite3_bind_text(preparedObject, 1, objectName.c_str(), -1, nullptr);
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      searchResult = idResultQuery(preparedObject, 0);
      if (searchResult != -1) {
        terminatePrepared(preparedObject);
      } else {
        std::cout << sqlite3_errmsg(DB) << std::endl;
      }

    } else {
      std::cout << sqlite3_errmsg(DB) << '\n'; // don't mind the jank
    }
  }
  return searchResult;
}
int insertItemObject(sqlite3 *DB, item desiredItem) {
  // assuming table rows (name, quantity, price, category)
  std::string statement = "INSERT INTO items(name, quantity, price, "
                          "category_id) VALUES(?1, ?2, ?3, ?4)";

  std::cout << statement << '\n';

  // TODO
  // EXECUTE FUNCTIONS ONLY IF PREVIOUS ROUTINE DID NOT FAIL
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    int bindHandle = sqlite3_bind_text(
        preparedObject, 1, desiredItem.getName().c_str(), -1, nullptr);
    if (bindHandle != 0) {
      std::cout << sqlite3_errmsg(DB);
      return -1;
    }
    bindHandle = sqlite3_bind_int(preparedObject, 2, desiredItem.getQuantity());
    if (bindHandle != 0) {
      std::cout << sqlite3_errmsg(DB);
      return -1;
    }
    bindHandle =
        sqlite3_bind_double(preparedObject, 3, (double)desiredItem.getPrice());
    if (bindHandle != 0) {
      std::cout << sqlite3_errmsg(DB);
      return -1;
    }
    std::string itemCat = desiredItem.getCategory();
    if (itemCat.compare("null") == 0) {
      bindHandle = sqlite3_bind_null(preparedObject, 4);
    } else {
      int catSearch = searchCat(DB, itemCat);
      if (catSearch != -1) {
        bindHandle = sqlite3_bind_int(preparedObject, 4, catSearch);
      } else {
        return -1;
        std::cout << "Category not found, try again.\n";
      }
    }
    if (bindHandle != 0) {
      std::cout << sqlite3_errmsg(DB);
      return -1;
    }
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      terminatePrepared(preparedObject);
    }
  }
  return 1;
}
void insertCat(sqlite3 *DB, std::string desiredCategory) {
  // assuming name only
  std::string statement = "INSERT INTO categories(name) VALUES('";
  statement.append(desiredCategory);
  statement.append("')");
  std::cout << statement << '\n';

  // TODO
  // EXECUTE FUNCTIONS ONLY IF PREVIOUS ROUTINE DID NOT FAIL
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      terminatePrepared(preparedObject);
    }
  }
}

int deleteItem(sqlite3 *DB, std::string objectName) {
  // prepare statement binding (I'm cool now)
  std::string statement = "DELETE FROM items WHERE name = ?1";
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    int stepCount = 0;
    int stepHandle = 0;
    int bindHandle =
        sqlite3_bind_text(preparedObject, 1, objectName.c_str(), -1, nullptr);
    if (bindHandle == SQLITE_OK) {
      stepHandle = sqlite3_step(preparedObject);
      if (stepHandle == SQLITE_DONE) {
        return 1;
      } else {
        return -1;
      }
    }
  } else {
    std::cout << sqlite3_errmsg(DB) << '\n';
  }
  return -1;
}

void editItem(sqlite3 *DB, std::string tableName, std::string objectName,
              std::string desiredColumn, std::string desiredValue) {
  // table, object, column, value
  int searchResult = -1;
  std::string statement = "UPDATE ";
  statement.append(tableName);
  statement.append("SET ");
  statement.append(desiredColumn);
  statement.append(" = '");
  statement.append(desiredValue);
  statement.append("' WHERE id = ");
  statement.append(std::to_string(searchItem(DB, objectName)));
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      terminatePrepared(preparedObject);
    } else {
      std::cout << sqlite3_errmsg(DB) << '\n'; // don't mind the jank
    }
  }
}
void editItem(sqlite3 *DB, std::string tableName, int objectID,
              std::string desiredColumn, std::string desiredValue) {
  // table, object, column, value
  int searchResult = -1;
  std::string statement = "UPDATE ";
  statement.append(tableName);
  statement.append(" SET ");
  statement.append(desiredColumn);
  statement.append(" = '");
  statement.append(desiredValue);
  statement.append("' WHERE id = ");
  statement.append(std::to_string(objectID));
  std::cout << statement << '\n';
  sqlite3_stmt *preparedObject = prepareItemObject(DB, statement);
  if (preparedObject != nullptr) {
    bool stepTry = stepItemObject(preparedObject);
    if (stepTry != false) {
      terminatePrepared(preparedObject);
    } else {
      std::cout << sqlite3_errmsg(DB) << '\n'; // don't mind the jank
    }
  }
}
