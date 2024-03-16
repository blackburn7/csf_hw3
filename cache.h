#include <vector>
#include <cstdint>

struct Slot {
  uint32_t tag;
  bool valid;
  uint32_t access_timestamp;
  uint32_t load_timestamp;
};

struct Set {
  std::vector<Slot> slots;

  bool doesTagExist(uint32_t tag);
};

struct Cache {
  private:
    int totalSets;
    int blocks;
    int bytes;
    bool isWriteAllocate;
    bool isWriteBack;
    bool isLRU;


    int lCount = 0;
    int sCount = 0;
    int lHit = 0;
    int sHit = 0;
    int cCount = 0;

    


  public:
    std::vector<Set> sets;
    void outputPrint();


};

void chacheOps(Cache& cache, bool isLoad, uint32_t address, uint32_t& current_timestamp);