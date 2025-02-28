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
      : name(name), quantity(quantity), price(price) {};
  item(std::string name, int quantity, float price, std::string cat)
      : name(name), quantity(quantity), price(price), category(cat) {};
  item(const char *cname, int desiredQuantity, float desiredPrice,
       const char *ccat);
  void setName(std::string desiredName);
  std::string getName();

  void setCategory(std::string desiredCategory);
  std::string getCategory();

  void setPrice(float desiredPrice);
  float getPrice();

  void setQuantity(int desiredQuantity);
  int getQuantity();
  void setNumSold(int desiredNumSold);
  int getNumSold();

  void setId(int num);
  int getId();

  item(item &&) = default;
  item(const item &) = default;
  item &operator=(item &&) = default;
  item &operator=(const item &) = default;

private:
  int id;
  int quantity;
  std::string name;
  std::string category;
  float price;
  int numSold;
};

// string literal constructor
item::item(const char *cname, int desiredQuantity, float desiredPrice,
           const char *ccat) {
  std::string stringName = std::string(cname);
  std::string stringCat = std::string(ccat);
  name = stringName;
  quantity = desiredQuantity;
  price = desiredPrice;
  category = stringCat;
}

void item::setName(std::string desiredName) { name = desiredName; }
std::string item::getName() { return name; }

void item::setCategory(std::string desiredCategory) {
  category = desiredCategory;
}
std::string item::getCategory() { return category; }

void item::setPrice(float desiredPrice) { price = desiredPrice; }
float item::getPrice() { return price; }

void item::setQuantity(int desiredQuantity) { quantity = desiredQuantity; }
int item::getQuantity() { return quantity; }
void item::setNumSold(int desiredNumSold) { numSold = desiredNumSold; }
int item::getNumSold() { return numSold; }
void item::setId(int num) { id = num; }
int item::getId() { return id; }
