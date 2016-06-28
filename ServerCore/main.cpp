#include "main.h"
#include "network_setup.h"
#include "configSetup.h"

int main(int argc, char const *argv[]) {
  configSetup();
  setup_Network();
  return 0;
}
