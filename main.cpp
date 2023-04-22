#include "student.hpp"
#include "hashT.hpp"
#include "menu.hpp"

using namespace std;

int main() {
  HashT<Student> myTable;
  Menu myMenu;

  myMenu.mainMenu(myTable);
  return 0;
  }
