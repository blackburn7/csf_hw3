#include "cache.h"
#include <cmath>
#include <iostream>
#include <cstdint>

using std::cout;
using std::endl;

int Set::getTagIndex(uint32_t tag) {
    // traverse slots
	uint32_t curIndex = 0;
    for (auto it = slots.begin(); it != slots.end(); ++it) {
        // if tags match then tag exists
        if (it->tag == tag) {
            return curIndex;
        }
		curIndex++;
    }
    // no tags matched
    return -1;
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

// write data to the cache
void Cache::write(uint32_t time, uint32_t index, uint32_t tag) {
    // update total store count
	sCount++;

    // find index of slot that tag is located at
	int tagIndex = sets.at(index).getTagIndex(tag);
    
	if (tagIndex != -1) {
        // if tag exists increase hit count and update time
		sHit++;
		sets.at(index).slots.at(tagIndex).access_timestamp = time;
        
		if (isWriteBack) {
            // set tag to dirty and increase cycle
			sets.at(index).slots.at(tagIndex).valid = false;
			cCount += 1;
		} else {
            // set tag to not dirty and increase cycle by 100
			sets.at(index).slots.at(tagIndex).valid = true;
			cCount += 100;
		}

	} else {
		if (isWriteAllocate) {
            // if is writeAllocate and tag DNE then write from mem. to cache
            writeToCache(time, index, tag);
			cCount += (bytes / 4) * 100;
		}
		if (!isWriteBack) cCount += 100;
	}
}

// load data from the cache
void Cache::load(uint32_t time, uint32_t index, uint32_t tag) {
    // update total load count
	lCount++;

    // 
	int tagIndex = sets.at(index).getTagIndex(tag);
	if (tagIndex != -1) {
		cCount++;
		lHit++;
		sets.at(index).slots.at(tagIndex).access_timestamp = time;
	} else {
		cCount += (bytes / 4) * 100;
		writeToCache(time, index, tag);
	}

}

// write from memory to the cache
void Cache::writeToCache(uint32_t time, uint32_t index, uint32_t tag) {

    // clear lru if cache is full
    std::vector<Slot>& setToWrite = sets.at(index).slots;
    Slot newSlot = {tag, true, time, time};

    if ((int)setToWrite.size() == blocks) {
        isLRU ? overrideLRU(setToWrite, newSlot) : overrideFIFO(setToWrite, newSlot);
    } else {
        setToWrite.push_back(newSlot);
    }
}

void Cache::overrideLRU(std::vector<Slot> & setToWrite, Slot newSlot) {
    uint32_t LRU_index = -1;
    uint32_t LRU_timestamp = std::numeric_limits<uint32_t>::max();
    uint32_t curIndex = 0;
    for (auto it = setToWrite.begin(); it != setToWrite.end(); it++) {
        if (it->access_timestamp < LRU_timestamp) {
            LRU_timestamp = it->access_timestamp;
            LRU_index = curIndex;
        }
        curIndex++;
    }
    if (!setToWrite.at(LRU_index).valid) {
        cCount += (bytes / 4) * 100;
    }
    setToWrite.at(LRU_index) = newSlot;
}

void Cache::overrideFIFO(std::vector<Slot> & setToWrite, Slot newSlot) {
    uint32_t FI_index = -1;
    uint32_t FI_timestamp = std::numeric_limits<uint32_t>::max();
    uint32_t curIndex = 0;
    for (auto it = setToWrite.begin(); it != setToWrite.end(); it++) {
        if (it->load_timestamp < FI_timestamp) {
            FI_timestamp = it->load_timestamp;
            FI_index = curIndex;
        }

        curIndex++;
    }
    if (!setToWrite.at(FI_index).valid) {
        cCount += (bytes / 4) * 100;
    }
    setToWrite.at(FI_index) = newSlot;
}

