#include "main.h"
#include "connection.h"
int User_Set_GPIO;
int main(int argc, char const *argv[]) {
  std::cout << "Setting up..." << std::endl;

  /*if (SetupConnection() == -1) {
    std::cout << "ERROR with connection" << std::endl;
    return 0;
  }
  else{
    std::cout << "Connection established to server!" << std::endl;

  }*/
  SetupConnection();
  std::cout << "Please input GPIO pin" << std::endl;
  std::string User_Set_GPIO_Str;
  getline(std::cin, User_Set_GPIO_Str);
  std::cout << "Setting up GPIO on..." << std::endl;
  User_Set_GPIO = stoi(User_Set_GPIO_Str);

  if (CreateGPIO(User_Set_GPIO)) {
    std::cout << "Setup Complete" << std::endl;
    Question();
  }else{
    std::cout << "Setup not complete \n Exiting program..." << std::endl;
  }
  turnOffLight(User_Set_GPIO);
  std::cout << "Turning off light" << std::endl;
  //std::thread t1(SetupConnection);
  //t1.join();
  return 0;
}
void Question(){
  bool quit;
  quit = 0;
  std::string User_Responce;
  while (quit != 1){
    std::cout << ">";
    std::getline(std::cin, User_Responce);
    Options(User_Responce);
  }
}
void Options(std::string option) {
  if (option == "light on") {
    if (turnOnLight(User_Set_GPIO)==0) {
      std::cout << "Error turning on light" << std::endl;
    }
  }
  else if (option == "light off") {
    std::cout << "Turning off light" << std::endl;
    if (turnOffLight(User_Set_GPIO)==0) {
      std::cout << "Error turning on light" << std::endl;
    }
  }
  else{
    std::cout << "Unknown command :(" << std::endl;
  }
}
int CreateGPIO(int GPIO){
  std::ofstream myfile ("/sys/class/gpio/export");
  if (myfile.is_open()){
    myfile << GPIO;
    myfile.close();
    return 1;
  }
  else{
    std::cout << "Unable to open file" << std::endl;
    return 0;
  }
}
int turnOnLight(int GPIO){
  std::cout << "Turning on light..." << std::endl;
  std::string Light_GPIO_Direction = "/sys/class/gpio/gpio" + std::to_string(GPIO) + "/direction";
  std::ofstream myfile (Light_GPIO_Direction);
  if (myfile.is_open()){
    myfile << "in";
    myfile.close();
    std::cout << "Success!" << std::endl;
    return 1;
  }else{
    std::cout << "Error opening file" << std::endl;
    return 0;
  }
}
int turnOffLight(int GPIO){
  std::cout << "Turning off light..." << std::endl;
  std::string Light_GPIO_Direction = "/sys/class/gpio/gpio" + std::to_string(GPIO) + "/direction";
  std::ofstream myfile (Light_GPIO_Direction);
  if (myfile.is_open()){
    myfile << "out";
    myfile.close();
    std::cout << "Success!" << std::endl;
    return 1;
  }else{
    std::cout << "Error opening file" << std::endl;
    return 0;
  }
}
