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
    else if (input.substr(0, 5) == "echo "){
      std::cout << input.substr(5) << std::endl;
    
    }
    else if (input.substr(0, 5) == "type "){
      std::string cmd = input.substr(5);
      if (cmd == "echo" || cmd == "type" || cmd == "exit"){
        std::cout << cmd << " is a shell builtin" << std::endl;
      }
      else{
        std::cout << cmd << ": command not found\n";

      }

    
    }
    
    else{
      std::cout << input << ": not found\n";
    }

  }
  return 0;
}
