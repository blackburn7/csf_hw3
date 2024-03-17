#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::string;


int main (int argc, char* argv[]) {
  if (argc > 7 || argc < 7) {
    std::cerr << "Incorrect number of parameters";
    return 1;
  }

  // Parse cache setts
  bool isWriteAllocate;
  
  if (std::string(argv[4]) == "write-allocate") {
    isWriteAllocate = true;
  } else if (std::string(argv[4]) == "no-write-allocate") {
    isWriteAllocate = false;
  } else {
    std::cerr << "incorrect cache settings";
    return 2;
  }

  bool isWriteBack;
  
  if (std::string(argv[5]) == "write-back") {
    isWriteBack = true;
  } else if (std::string(argv[5]) == "write-through") {
    isWriteBack = false;
  } else {
    std::cerr << "incorrect cache settings";
    return 2;
  }
  
  bool isLRU;
  
  if (std::string(argv[6]) == "lru") {
    isLRU = true;
  } else {
    isLRU = false;
  }

  if (!isWriteAllocate && isWriteBack) {
    std::cerr << "No write allocate cannot be paired with write back";
    return 3;
  }

  // set values for key numbers of cache
  uint32_t totalSets = std::stoi(argv[1]);
  uint32_t blocks = std::stoi(argv[2]);
  uint32_t bytes = std::stoi(argv[3]);

  // determine if rules are broken with power of 2 numbers
  if ((totalSets & (totalSets - 1)) || (totalSets & (blocks - 1)) || (bytes & (bytes - 1)) || bytes < 4) {
    std::cerr << "Failed to have power of 2 numbers or other number policies";
    return 4;
  }

  // creates cache sim
  Cache cache(totalSets, blocks, bytes, isWriteAllocate, isWriteBack, isLRU);

  // for input lines
  string line;

  // to represent time passing and record time stamps
  uint32_t timeRepresentationCounter = 0;

  while (std::getline(cin, line)) {
    char cmd = line[0];
    uint32_t address = std::stoul(line.substr(2, 10), nullptr, 16);
    
    // calc index and tag
    uint32_t blockAdd = address / bytes;
    uint32_t index = blockAdd % totalSets;
    uint32_t tag = blockAdd / totalSets;

    if (cmd == 'l') {
      cache.load(timeRepresentationCounter, index, tag);
    } else if (cmd == 's') {
      cache.write(timeRepresentationCounter, index, tag);
    } else {
      std::cerr << "command is not s or l";
    }
    timeRepresentationCounter+=1; // increases time stamp for the next iteration
  }

  cache.outputPrint();

  return 0;
}