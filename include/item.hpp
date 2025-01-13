//TODO:
//nome
//categoria: bebida, higiene, limpeza, etc..;
//identificador;
//quantidade;
//num de prod vendidos;
//preco


class item {
public:
  item();
  item(std::string name, int quantity, float price) : name(name), quantity(quantity), price(price);
  item(std::string name, int quantity, float price, std::string cat) : name(name), quantity(quantity), price(price), category(cat);

  setName(std::string desiredName);
  getName();

  getId();

  setCategory(std::string desiredCategory);
  getCategory();

  setPrice(int desiredPrice);
  getPrice();

  setNumSold(int desiredNumSold);
  getNumSold();

  item(item &&) = default;
  item(const item &) = default;
  item &operator=(item &&) = default;
  item &operator=(const item &) = default;
  ~item();

private:
  int id;
  std::string name;
  std::string category;
  float price;
  int numSold;
};

item::setName(std::string desiredName){
  name = desiredName;
}
item::getName(){
  return name;
}


