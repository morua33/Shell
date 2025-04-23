#include <iostream>
#include <sstream>
#include <filesystem>

std::string get_path(std::string command){
  std::string path_env = std::getenv("PATH");
  std::stringstream ss(path_env);
  std::string path;
  while(!ss.eof()) {
      getline(ss, path, ':');
      std::string abs_path = path + "/" + command;
      if (std::filesystem::exists(abs_path)) {
          return abs_path;
      }
  }
  return "";
}

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
      // std::string cmd = input.substr(5);
      if (input.substr(5) == "echo" || input.substr(5) == "type" || input.substr(5) == "exit" || input.substr(4) == "pwd"){
        std::cout << input.substr(5) << " is a shell builtin" << std::endl;
      }
      else{
        std::string path = get_path(input.substr(5));
        if(path.empty()){
          std::cout << input.substr(5) << ": not found\n";
        }
        
        else{
          std::cout << input.substr(5) << " is " << path << std::endl;
        }
      }
    }
    else if(input.substr(0,3) == "pwd"){
      std::cout << std::filesystem::current_path() << std::endl;

    }
    else{
      int end = input.find(" ");
      std::string path = get_path(input.substr(0,end));

      if(path.empty()){
        std::cout << input << ": not found\n";
      }
      else{
        const char *input_ptr = input.c_str();


        system(input_ptr);
        
      }
      
    }

  }
  return 0;
}
