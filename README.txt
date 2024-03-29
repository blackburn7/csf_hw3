matthew blackburn
atticus colwell

MS2:

Atticus: focused on main and general design of cache
Matthew: focused on functionality of load and store functions

read01.trace

lru: 
Total loads: 5
Total stores: 0
Load hits: 2
Load misses: 3
Store hits: 0
Store misses: 0
Total cycles: 1202

fifo:
Total loads: 5
Total stores: 0
Load hits: 2
Load misses: 3
Store hits: 0
Store misses: 0
Total cycles: 1202


gcc.trace

lru: 
Total loads: 318197
Total stores: 197486
Load hits: 315715
Load misses: 2482
Store hits: 188595
Store misses: 8891
Total cycles: 5976710

fifo:
Total loads: 318197
Total stores: 197486
Load hits: 315594
Load misses: 2603
Store hits: 188567
Store misses: 8919
Total cycles: 6069761

read02.trace

lru: 
Total loads: 10
Total stores: 0
Load hits: 9
Load misses: 1
Store hits: 0
Store misses: 0
Total cycles: 409

fifo:
Total loads: 10
Total stores: 0
Load hits: 9
Load misses: 1
Store hits: 0
Store misses: 0
Total cycles: 409

read03.trace

lru:
Total loads: 9
Total stores: 0
Load hits: 5
Load misses: 4
Store hits: 0
Store misses: 0
Total cycles: 1605

fifo:
Total loads: 9
Total stores: 0
Load hits: 5
Load misses: 4
Store hits: 0
Store misses: 0
Total cycles: 1605

swim.trace

lru: 
Total loads: 220668
Total stores: 82525
Load hits: 219730
Load misses: 938
Store hits: 72027
Store misses: 10498
Total cycles: 5963357

fifo: 
Total loads: 220668
Total stores: 82525
Load hits: 219677
Load misses: 991
Store hits: 72015
Store misses: 10510
Total cycles: 6009692

write01.trace

lru: 
Total loads: 0
Total stores: 5
Load hits: 0
Load misses: 0
Store hits: 2
Store misses: 3
Total cycles: 1202

fifo:
Total loads: 0
Total stores: 5
Load hits: 0
Load misses: 0
Store hits: 2
Store misses: 3
Total cycles: 1202

write02.trace

lru:
Total loads: 0
Total stores: 10
Load hits: 0
Load misses: 0
Store hits: 9
Store misses: 1
Total cycles: 409

fifo:
Total loads: 0
Total stores: 10
Load hits: 0
Load misses: 0
Store hits: 9
Store misses: 1
Total cycles: 409



Which cache is better: based on these cache simulations and the above inputs and results, the LRU seems
to be slightly better than the fifo, but not significantly. In all input files except for swim.trace and 
gcc.trace, the statistics on hits, misses, and cycles were all identical. For the larger files of swim
and gcc, there are slight differences in store hits/misses, load hits/misses, and cycles. 

For gcc.trace, load hits were at 315715 for LRU and 315594 for fifo, this is a 121 load hit advantage to 
LRU. Additionally, there were 188595 store hits for LRU compared to 188567 store hits for fifo, this is 
a 28 store hit advantage to LRU. Finally, there were 93,051 fewer cycles in LRU in comparison to FIFO. Solely 
based on gcc.trace, LRU has shown to be better as it results in greater hits and fewer cycles.

For swim.trace, load hits were at 219730 for LRU and 219677 store hits for fifo, a 53 hit advantage to LRU. 
There were 72027 store hits for LRU and 72015 store hits for fifo, a 12 hit advantage for LRU. Finally there
were 46,335 fewer cycles in LRU in comparison to FIFO. Solely based on swim.trace, LRU has shown to be better
as it results in greater hits and fewer cycles. 

In conclusion, based on the above two analysises of the two cache simulations on input files gcc.trace and 
swim.trace, LRU is clearly the better cache in comparison to FIFO. 