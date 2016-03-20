// Brian Malloy        September, 2006

#include "manager.h"

IOSingleton* IOSingleton::instance = NULL;
Manager* Manager::instance = NULL;

int main() {
   try {
      Manager* game_manager = Manager::getInstance();
      game_manager->play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
