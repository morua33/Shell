#include <iostream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  
  std::cout << "$ ";
  while (1)
  {
  
  std::string input;
  std::getline(std::cin, input);

  std::cout << input << ": command not found\n";
  
  }
  return 0;
}
