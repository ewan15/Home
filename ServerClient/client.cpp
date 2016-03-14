#include "client.h"
#include "connection.h"
using namespace std;

int main (int argc, char* argv[])
{
    if (SetupConnection() == 0) {
      std::cerr << "Error establishing connection with server" << std::endl;
      return 0;
    }
}
