#include "apiDB.hpp"
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

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
  root()->addNew<Wt::WText>("Type in your name");
  nameEdit_ = root()->addNew<Wt::WLineEdit>();
  Wt::WPushButton *button = root()->addNew<Wt::WPushButton>("Press Me");
  (*root()).addNew<Wt::WBreak>();
  greeting_ = root()->addNew<Wt::WText>();
  auto greet = [this] {
    sqlite3 *DB;
    int exit = 0;
    exit = sqlite3_open("inventory.db", &DB);
    if (exit) {
      std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl;
    }

    std::string returnStr = "";
    searchAllItems(DB, returnStr);
    greeting_->setText(returnStr);
  };
  button->clicked().connect(greet);
}

int main(int argc, char **argv) {

  return Wt::WRun(argc, argv, [](const Wt ::WEnvironment &env) {
    return std::make_unique<HelloApplication>(env);
  });
}
