#include <iostream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  
  while (1)
  {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "exit 0"){
      return 0;
    }
    else if (input.substr(0, 4) == "echo "){
      std::cout << input.substr(6);
    
    }
    
    else{
      std::cout << input << ": command not found\n";
    }

  }
  return 0;
}
