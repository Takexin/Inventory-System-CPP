#include "apiDB.cpp"
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGlobal.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <memory>
#include <string>
#include <vector>

class deleteItemWidget : public Wt::WContainerWidget {
public:
  deleteItemWidget();
  Wt::WLineEdit *ID;
  Wt::WPushButton *button;
};

deleteItemWidget::deleteItemWidget() {
  ID = addWidget(std::make_unique<Wt::WLineEdit>());
  ID->setPlaceholderText("Object ID");
  button = addWidget(std::make_unique<Wt::WPushButton>());
  button->setText("Submit");
}

class createItemWidget : public Wt::WContainerWidget {
public:
  createItemWidget();
  Wt::WLineEdit *name;
  Wt::WLineEdit *quantity;
  Wt::WLineEdit *price;
  Wt::WLineEdit *category;
  Wt::WPushButton *button;
};
createItemWidget::createItemWidget() {
  name = addWidget(std::make_unique<Wt::WLineEdit>());
  name->setPlaceholderText("name");

  quantity = addWidget(std::make_unique<Wt::WLineEdit>());
  quantity->setPlaceholderText("quantity");

  price = addWidget(std::make_unique<Wt::WLineEdit>());
  price->setPlaceholderText("price");

  category = addWidget(std::make_unique<Wt::WLineEdit>());
  category->setPlaceholderText("category");

  button = addWidget(std::make_unique<Wt::WPushButton>());
  button->setText("submit");
};

class itemWidget : public Wt::WContainerWidget {
public:
  itemWidget(item &desiredItem);
  itemWidget();
};

itemWidget::itemWidget(item &desiredItem) {
  addStyleClass("item-container");
  auto id = addWidget(std::make_unique<Wt::WText>(
      Wt::WString("<p>{1}</p>").arg(desiredItem.getId())));
  id->addStyleClass("box");
  id->setId("id");

  auto name = addWidget(std::make_unique<Wt::WText>(
      Wt::WString("<p>{1}</p>").arg(desiredItem.getName())));
  name->addStyleClass("box");
  name->setId("name");

  auto category = addWidget(std::make_unique<Wt::WText>(
      Wt::WString("<p>{1}</p>").arg(desiredItem.getCategory())));
  category->addStyleClass("box");
  category->setId("name");

  auto quantity = addWidget(std::make_unique<Wt::WText>(
      Wt::WString("<p>{1}</p>").arg(desiredItem.getQuantity())));
  quantity->addStyleClass("box");
  quantity->setId("quantity");

  auto price = addWidget(std::make_unique<Wt::WText>(
      Wt::WString("<p>{1}</p>").arg(desiredItem.getPrice())));
  price->addStyleClass("box");
  price->setId("quantity");
}
itemWidget::itemWidget() {
  addStyleClass("item-container");
  auto id = addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>ID</p>")));
  id->addStyleClass("box");
  id->setId("id");

  auto name =
      addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>NAME</p>")));
  name->addStyleClass("box");
  name->setId("name");

  auto category =
      addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>CATEGORY</p>")));
  category->addStyleClass("box");
  category->setId("name");

  auto quantity =
      addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>QUANTITY</p>")));
  quantity->addStyleClass("box");
  quantity->setId("quantity");

  auto price =
      addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>PRICE</p>")));
  price->addStyleClass("box");
  price->setId("quantity");
}

class HelloApplication : public Wt::WApplication {
public:
  HelloApplication(const Wt::WEnvironment &env);

private:
  Wt::WLineEdit *nameEdit_;
  Wt::WText *greeting_;
  createItemWidget *itemCreate;
  deleteItemWidget *itemDelete;
  item desiredItem;
  sqlite3 *DB;
};

HelloApplication::HelloApplication(const Wt::WEnvironment &env)
    : Wt::WApplication(env) {
  setTitle("Hello World");
  int exit = 0;
  exit = sqlite3_open("inventory.db", &DB);
  if (exit) {
    std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl;
  }
  useStyleSheet("style.css");

  std::vector<item> itemVect;
  searchAllItems(DB, itemVect);
  root()->addNew<itemWidget>();
  (*root()).addNew<Wt::WBreak>();
  (*root()).addNew<Wt::WBreak>();

  for (int i = 0; i < itemVect.size(); i++) {
    root()->addNew<itemWidget>(itemVect[i]);
    (*root()).addNew<Wt::WBreak>();
  }

  (*root()).addNew<Wt::WBreak>();

  itemCreate = root()->addWidget(std::make_unique<createItemWidget>());
  itemCreate->button->clicked().connect([&]() {
    desiredItem = item(itemCreate->name->text().toUTF8(),
                       std::stoi((itemCreate->quantity->text().toUTF8())),
                       std::stof(itemCreate->price->text().toUTF8()),
                       (itemCreate->category->text()).toUTF8());
    insertItemObject(DB, desiredItem);
  });

  Wt::WPushButton *button = root()->addNew<Wt::WPushButton>("Select all");
  (*root()).addNew<Wt::WBreak>();
  greeting_ = root()->addNew<Wt::WText>();
  auto greet = [this] {
    std::string returnStr = "";
    greeting_->setText(returnStr);
  };
  root()->addNew<Wt::WBreak>();
  itemDelete = root()->addWidget(std::make_unique<deleteItemWidget>());
  itemDelete->button->clicked().connect([&]() {
    int objectID = std::stoi(itemDelete->ID->text().toUTF8());
    deleteItem(DB, objectID);
  });

  button->clicked().connect(greet);
}

int main(int argc, char **argv) {

  return Wt::WRun(argc, argv, [](const Wt ::WEnvironment &env) {
    return std::make_unique<HelloApplication>(env);
  });
}
