#include <iostream>
#include <vector>
#include <string>
#include "cache.cpp"


















int main (int argc, char* argv[]) {

  /* std::vector<std::string> memory_accesses;
  std::string memory_access;
  while(std::getline(std::cin, memory_access)) {
    memory_accesses.push_back(memory_access);
  }
  
  for (std::string element: memory_accesses) {
    std::cout << element << std::endl;
  } */

  Cache cache(0, 0, 0, 0, 0, 0);

  cache.outputPrint();

  return 0;
}