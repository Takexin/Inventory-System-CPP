#include <iostream>
#include <limits>
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
  //usr, add itm, add cat, rmv itm, exit
  int options[] = {0, 1, 2, 3, 4};
  std::string startText =
    " ___                      _                     ____            _\n"
    "|_ _|_ ____   _____ _ __ | |_ ___  _ __ _   _  / ___| _   _ ___| |_ ___ _ __ ___\n"
    " | || '_ \\ \\ / / _ \\ '_ \\| __/ _ \\| '__| | | | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\\n"
    " | || | | \\ V /  __/ | | | || (_) | |  | |_| |  ___) | |_| \\__ \\ ||  __/ | | | | |\n"
    "|___|_| |_|\\_/ \\___|_| |_|\\__\\___/|_|   \\__, | |____/ \\__, |___/\\__\\___|_| |_| |_|\n"
    "                                         |___/         |___/\n"
    "-----------------------------------------------------------------------------------------------\n";
  std::cout << startText << '\n';

  while(options[0] != options[4]){
  std::cout << "\nSelect an option:" << "\n" << options[1] << "-Add item\n" 
    << options[2] << "-Add category\n" 
    << options[3] << "-Remove item\n" 
    << options[4] << "-exit\n"; 
  std::cin >> options[0];
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  switch(options[0]){
    case 4:{
      break;
    }
  }

  }
  sqlite3_close(DB);
  return 0;
}
