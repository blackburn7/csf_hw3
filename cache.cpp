#include "cache.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

bool Set::doesTagExist(uint32_t tag) {
    // traverse slots
    for (auto it = slots.begin(); it != slots.end(); ++it) {
        // if tags match then tag exists
        if (it->valid && it->tag == tag) {
            return true;
        }
    }
    // no tags matched
    return false;
}

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

void Cache::outputPrint() {
  cout << "Total loads: " << lCount << endl; 
  cout << "Total stores: " << sCount << endl;
  cout << "Load hits: " << lHit << endl;
  int diff = lCount - lHit;
  cout << "Load misses: " << diff << endl;
  cout << "Store hits: " << sHit << endl;
  diff = sCount - sHit;
  cout << "Store misses: " << diff << endl;
  cout << "Total cycles: " << cCount << endl;
}


void Cache::write(uint32_t time, uint32_t index, uint32_t tag) {
	sCount++;
	if (sets.at(index).doesTagExist(tag)) {
		sHit++;
		sets.at(index).slots.at(tag).load_timestamp = time;

	} else {

	}
}

void Cache::load(uint32_t time, uint32_t index, uint32_t tag) {
	lCount++;
	if (sets.at(index).doesTagExist(tag)) {

	}



}