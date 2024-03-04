#include <iostream>
#include <vector>
#include <string>


















int main (int argc, char* argv[]) {

  std::vector<std::string> memory_accesses;
  std::string memory_access;
  while(std::getline(std::cin, memory_access)) {
    memory_accesses.push_back(memory_access);
  }
  
  for (std::string element: memory_accesses) {
    std::cout << element << std::endl;
  }

  return 0;
}