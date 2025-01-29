#include <iostream>
#include "item.hpp"

int main (int argc, char *argv[]) {
  //creating items

  std::string name1 = "Toothbrush";
  int quantity1 = 727;
  float price1 = 10.22;
  item item1(name1, quantity1, price1);

  //std::cout << item1.getName() << '\n';
  item item2("Toothbrush", 727, 10.22, "Clean");
  std::cout << item2.getName() << '\n';


  return 0;
}
