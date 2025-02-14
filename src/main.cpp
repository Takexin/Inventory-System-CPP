#include "apiDB.hpp"
#include <limits>

// function prototypes
void addItem(sqlite3 *DB);
void addCat(sqlite3 *DB);
void removeItem(sqlite3 *DB);
void searchTable(sqlite3 *DB);

int main(int argc, char *argv[]) {
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("inventory.db", &DB);

  if (exit) {
    std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl;
    return (-1);
  } else {
    std::cout << "Opened DB sucessfully\n";
  }
  // usr, add itm, add cat, rmv itm, seach items, exit
  const int options[] = {0, 1, 2, 3, 4};
  std::string startText =
      " ___                      _                     ____            _\n"
      "|_ _|_ ____   _____ _ __ | |_ ___  _ __ _   _  / ___| _   _ ___| |_ ___ "
      "_ __ ___\n"
      " | || '_ \\ \\ / / _ \\ '_ \\| __/ _ \\| '__| | | | \\___ \\| | | / __| "
      "__/ _ \\ '_ ` _ \\\n"
      " | || | | \\ V /  __/ | | | || (_) | |  | |_| |  ___) | |_| \\__ \\ ||  "
      "__/ | | | | |\n"
      "|___|_| |_|\\_/ \\___|_| |_|\\__\\___/|_|   \\__, | |____/ \\__, "
      "|___/\\__\\___|_| |_| |_|\n"
      "                                         |___/         |___/\n"
      "------------------------------------------------------------------------"
      "-----------------------\n";
  std::cout << startText << '\n';
  int option = 0;
  const int exitOpt = 6;
  const int catOpt = 2;
  const int itemOpt = 1;
  const int rmvOpt = 3;
  const int searchItemOpt = 4;
  const int searchCatOpt = 5;
  const int searchTableOpt = 7;
  while (option != exitOpt) {
    std::cout << "\nSelect an option:" << "\n"
              << itemOpt << "-Add item\n"
              << catOpt << "-Add category\n"
              << rmvOpt << "-Remove item\n"
              << exitOpt << "-exit\n";
    std::cin >> option;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (option) {
    case searchTableOpt: {
      searchTable(DB);
      break;
    }
    case itemOpt: {
      addItem(DB);
      break;
    }
    case catOpt: {
      addCat(DB);
      break;
    }
    case rmvOpt: {
      removeItem(DB);
      break;
    }
    case exitOpt: {
      break;
    }
    }
  }
  sqlite3_close(DB);
  return 0;
}
void addItem(sqlite3 *DB) {
  std::string desiredName;
  int desiredQuantity = 0;
  float desiredPrice = 0.0;
  std::string desiredCat;
  std::cout << "\n\nPlease provide the name of the item: ";
  std::cin >> desiredName;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "\n\nPlease provide the quantity of the item: ";
  std::cin >> desiredQuantity;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "\n\nPlease provide the price of the item: ";
  std::cin >> desiredPrice;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "\n\nPlease provide the category of the item (null otherwise): ";
  std::cin >> desiredCat;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  item desiredItem(desiredName, desiredQuantity, desiredPrice, desiredCat);
  insertItemObject(DB, desiredItem);
}
void addCat(sqlite3 *DB) {
  std::string desiredName;
  std::cout << "\n\nPlease provide the name of the category: ";
  std::cin >> desiredName;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  insertCat(DB, desiredName);
}
void removeItem(sqlite3 *DB) {
  std::string desiredName;
  std::cout << "\n\nPlease provide the name of the item: ";
  std::cin >> desiredName;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  int deleteVerifier = deleteItem(DB, desiredName);
  if (deleteVerifier == -1) {
    std::cout << "multiDelete Falhou\n";
  }
}
void searchTable(sqlite3 *DB) {
  std::string desiredName;
  std::cout << "\n\nPlease provide the name of the item to search: ";
  std::cin >> desiredName;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  searchItem(DB, desiredName);
}
