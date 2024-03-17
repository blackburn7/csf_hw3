#include "cache.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

uint32_t Set::getTagIndex(uint32_t tag) {
    // traverse slots
		uint32_t curIndex = 0;
    for (auto it = slots.begin(); it != slots.end(); ++it) {
        // if tags match then tag exists
        if (it->valid && it->tag == tag) {
            return curIndex;
        }
				curIndex++;
    }
    // no tags matched
    return -1;
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
	int tagIndex = sets.at(index).getTagIndex(tag);
	if (tagIndex != -1) {
		sHit++;
		sets.at(index).slots.at(tag).access_timestamp = time;

		if (isWriteBack) {
			sets.at(index).slots.at(tag).valid = false;
			cCount += 1;
		} else {
			sets.at(index).slots.at(tag).valid = true;
			cCount += 100;
		}

	} else {
		if (isWriteAllocate) {
            writeToCache(time, index, tag);
			cCount += (bytes / 4) * 100;
		}
		if (!isWriteBack) cCount += 100;
	}
}

void Cache::load(uint32_t time, uint32_t index, uint32_t tag) {
	lCount++;
	uint32_t tagIndex = sets.at(index).getTagIndex(tag);
	if (tagIndex != -1) {
		cCount++;
		lHit++;
		sets.at(index).slots.at(tag).load_timestamp = time;
	} else {
		cCount += (bytes / 4) * 100;
		writeToCache(index, tag, time);
	}



}

void Cache::writeToCache(uint32_t time, uint32_t index, uint32_t tag) {

    // clear lru if cache is full
    std::vector<Slot>& setToWrite = sets.at(index).slots;
    Slot newSlot = {tag, true, time, time};

    if ((int)setToWrite.size() == blocks) {
        
        uint32_t LRU_index = -1;
        uint32_t LRU_timestamp = std::numeric_limits<uint32_t>::max();
        uint32_t curIndex = 0;



        for (auto it = setToWrite.begin(); it != setToWrite.end(); it++) {
            if (it->load_timestamp < LRU_timestamp) {
                LRU_timestamp = it->load_timestamp;
                LRU_index = curIndex;
            }

            curIndex++;
        }
        setToWrite.at(LRU_index) = newSlot;
    } else {
        setToWrite.push_back(newSlot);
    }


}