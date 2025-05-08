
#include <iostream>
#include <sstream>
#include <filesystem>
#include <vector>

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
std::vector<std::string> echo_cmd(std::string arg){
  std::vector<std::string> words;
  std::string curr_word;
  bool quotes = false;

  for (char c : arg){
    // std::cout << c << std::endl;
    // std::cout << "here3" << std::endl;
    if (c == '\''){
      quotes = true;
    }
    else if (c == ' ' && !quotes){
      if(!curr_word.empty()){
        // std::cout << "here2" << std::endl;
        words.push_back(curr_word);
        curr_word.clear();
      }

    }
    else{
      // std::cout << "here1" << std::endl;
      curr_word += c;

    }
    
    
  }
  std::cout << words[1] << std::endl;
  return words;

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
  

      std::vector<std::string> arg = echo_cmd(input.substr(5));
      std::cout << arg[0] << std::endl;

    }
    else if (input.substr(0, 5) == "type "){
      // std::string cmd = input.substr(5);
      if (input.substr(5) == "echo" || input.substr(5) == "type" || input.substr(5) == "exit" || input.substr(5) == "pwd"){
        std::cout << input.substr(5) << " is a shell builtin" << std::endl;
      }
      else{
        std::string path = get_path(input.substr(5));
        if(path.empty()){
          std::cout << input.substr(5) << ": not found" << std::endl;
        }
        
        else{
          std::cout << input.substr(5) << " is " << path << std::endl;
        }
      }
    }
    else if(input == "pwd"){
      std::cout << std::filesystem::current_path().string() << std::endl;
    }
    else if(input.substr(0,3) == "cd "){
      if (input.substr(3) == "~"){
        std::filesystem::current_path(std::getenv("HOME"));
      }
      else if (std::filesystem::exists(input.substr(3))){
        std::filesystem::current_path(input.substr(3));
      }
      else{
        std::cout << "cd: " << input.substr(3) << ": No such file or directory" << std::endl;
      }  
    }
    else{
      int end = input.find(" ");
      std::string path = get_path(input.substr(0,end));
      if(path.empty()){
        std::cout << input << ": not found" << std::endl;
      }
      else{
        const char *input_ptr = input.c_str();
        system(input_ptr);  
      }
    }
  }
  return 0;
}
