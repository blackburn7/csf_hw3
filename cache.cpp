#include "cache.h"
#include <cmath>


// changed later, these are dependent on make parameters
uint32_t blockSize = 10;
uint32_t numberOfSets = 20;

void chacheOps(Cache& cache, bool isLoad, uint32_t address, uint32_t& current_timestamp) {
    
    // figures out the index and tag values
    uint32_t block_offset_bits = std::log2(blockSize);
    uint32_t set_index_bits = std::log2(numberOfSets);
    uint32_t set_index = (address >> block_offset_bits) & ((1 << set_index_bits) - 1);
    uint32_t tag = address >> (block_offset_bits + set_index_bits);

    Set& set = cache.sets[set_index];
    
    // hit or miss
    bool hit = false;
    for (auto& slot : set.slots) {
        if (slot.valid && slot.tag == tag) { // hit
            hit = true;
            slot.access_timestamp = current_timestamp++; // update
            break;
        }
    }

    if (!hit) { // miss
        Slot* slot_to_replace = nullptr;
        uint32_t oldest_timestamp = UINT32_MAX;

        for (auto& slot : set.slots) {
            if (!slot.valid) { 
                slot_to_replace = &slot;
                break;
            } else if (slot.access_timestamp < oldest_timestamp) { 
                oldest_timestamp = slot.access_timestamp;
                slot_to_replace = &slot;
            }
        }

        // updatee info
        if (slot_to_replace != nullptr) {
            slot_to_replace->tag = tag;
            slot_to_replace->valid = true;
            slot_to_replace->access_timestamp = current_timestamp++;
            if (isLoad) {
                slot_to_replace->load_timestamp = current_timestamp;
            }
        }
    }

    // alot more needs to be added on storing and loading
}