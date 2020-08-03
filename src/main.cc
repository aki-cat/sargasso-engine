
#include <iostream>

#include "glfw.h"

using std::cout;
using std::endl;
using std::time;

const int DELAY_SECONDS = 5;

int main() {
  cout << "Hello world" << endl;

  if (!CoffeeEngine::GLFW::init()) {
    return -1;
  }

  time_t start_time = time(nullptr);
  cout << "Start!" << endl;

  time_t current_time = start_time;

  time_t now = time(nullptr);
  while (now - start_time <= DELAY_SECONDS) {
    if (now > current_time) {
      current_time = now;
      cout << current_time - start_time << endl;
    }
    now = time(nullptr);
  }

  cout << "Done!" << endl;
  CoffeeEngine::GLFW::terminate();

  return 0;
}
