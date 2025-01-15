// TODO:
// nome
// categoria: bebida, higiene, limpeza, etc..;
// identificador;
// quantidade;
// num de prod vendidos;
// preco
#include <iostream>

class item {
public:
  item();
  item(std::string name, int quantity, float price)
      : name(name), quantity(quantity), price(price);
  item(std::string name, int quantity, float price, std::string cat)
      : name(name), quantity(quantity), price(price), category(cat);

  void setName(std::string desiredName);
  std::string getName();

  int getId();

  void setCategory(std::string desiredCategory);
  std::string getCategory();

  void setPrice(int desiredPrice);
  float getPrice();

  void setNumSold(int desiredNumSold);
  int getNumSold();

  item(item &&) = default;
  item(const item &) = default;
  item &operator=(item &&) = default;
  item &operator=(const item &) = default;
  ~item();

private:
  int id;
  int quantity;
  std::string name;
  std::string category;
  float price;
  int numSold;
};

item::setName(std::string desiredName) { name = desiredName; }
item::getName() { return name; }
