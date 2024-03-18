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


void Cache::write(uint32_t time, uint32_t index, uint32_t tag) {
	sCount++;
	int tagIndex = sets.at(index).getTagIndex(tag);
	if (tagIndex != -1) {
		sHit++;
		sets.at(index).slots.at(tagIndex).access_timestamp = time;

		if (isWriteBack) {
			sets.at(index).slots.at(tagIndex).valid = false;
			cCount += 1;
		} else {
			sets.at(index).slots.at(tagIndex).valid = true;
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
	int tagIndex = sets.at(index).getTagIndex(tag);
	if (tagIndex != -1) {
		cCount++;
		lHit++;
		sets.at(index).slots.at(tagIndex).load_timestamp = time;
	} else {
		cCount += (bytes / 4) * 100;
		writeToCache(time, index, tag);
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
        if (!setToWrite.at(LRU_index).valid) {
            cCount += (bytes / 4) * 100; 
        }
        setToWrite.at(LRU_index) = newSlot;
    } else {
        setToWrite.push_back(newSlot);
    }


}