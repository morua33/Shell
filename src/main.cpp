
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
std::vector<std::string> split(const std::string& arg){
  std::vector<std::string> words;
  std::string curr_word;
  bool quotes = false;

  for (char c : arg){
    // std::cout << c << std::endl;
    // std::cout << "here3" << std::endl;
    if (c == '\''){
      quotes = !quotes;
    }
    else if (c == ' ' && !quotes){
      if(!curr_word.empty()){
        words.push_back(curr_word);
        curr_word.clear();
      }

    }
    else{
      // std::cout << "here1" << std::endl;
      curr_word += c;

    }   
  }
  
  if (!curr_word.empty()) {
    words.push_back(curr_word);
  }  
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

    std::vector<std::string> line = split(input);
    std::string cmd = line[0];



    if (cmd == "echo"){
      for (int i =1; i < line.size(); i++){
        std::cout << line[i];

        if(i < line.size()-1){
          std::cout << " ";
        }
      }
      std::cout << std::endl;

    }
    else if (cmd == "type"){
      // std::string cmd = input.substr(5);
      if (cmd == "echo" || cmd == "type" || cmd == "exit" || cmd == "pwd"){
        std::cout << cmd << " is a shell builtin" << std::endl;
      }
      else{
        std::string path = get_path(cmd);
        if(path.empty()){
          std::cout << cmd << ": not found" << std::endl;
        }
        
        else{
          std::cout << cmd << " is " << path << std::endl;
        }
      }
    }
    else if(cmd == "pwd"){
      std::cout << std::filesystem::current_path().string() << std::endl;
    }
    else if(cmd == "cd"){
      if (input.substr(3) == "~"){
        std::filesystem::current_path(std::getenv("HOME"));
      }
      else if (std::filesystem::exists(input.substr(3))){
        std::filesystem::current_path(input.substr(3));
      }
      else{
        std::cout << "cd: " << cmd << ": No such file or directory" << std::endl;
      }  
    }
    else{
      
      std::string path = get_path(cmd);
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
