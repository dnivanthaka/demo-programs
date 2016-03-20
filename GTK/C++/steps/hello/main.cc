#include "helloworld.h"
#include <gtkmm/main.h>

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);
  HelloWorld helloWorld;
  Gtk::Main::run(helloWorld);
  
  return 0;
}