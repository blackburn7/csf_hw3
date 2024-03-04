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
};

struct Cache {
  std::vector<Set> sets;
};