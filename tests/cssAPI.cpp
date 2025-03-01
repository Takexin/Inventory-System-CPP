#include "apiDB.hpp"
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <memory>
#include <vector>

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
};

HelloApplication::HelloApplication(const Wt::WEnvironment &env)
    : Wt::WApplication(env) {
  setTitle("Hello World");
  sqlite3 *DB;
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
  Wt::WPushButton *button = root()->addNew<Wt::WPushButton>("Select all");
  (*root()).addNew<Wt::WBreak>();
  greeting_ = root()->addNew<Wt::WText>();
  auto greet = [this] {
    std::string returnStr = "";
    greeting_->setText(returnStr);
  };
  button->clicked().connect(greet);
}

int main(int argc, char **argv) {

  return Wt::WRun(argc, argv, [](const Wt ::WEnvironment &env) {
    return std::make_unique<HelloApplication>(env);
  });
}
