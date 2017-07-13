****************************************************
```
Kanoa Haley                             0956712
CIS*2520                                Assignment 3
khaley@mail.uoguelph.ca                 July 17, 2017
```
****************************************************

*******************
Program Description
*******************
This program behaves as a simple triage simulator using a priority queue. It takes in data from a text based file and simulates the triaging of the patients after which it provides a report on the ideal order for the patients to been seen. 

The input data is in the form of new line seperated entries with the format: `[client ID] [priority] [symtom code]` where the symtom code will be a two upper case letter code based on the symtoms found [here](http://caep.ca/sites/caep.ca/files/caep/files/cedis2008.pdf).

#### Sample of the input data ####
```
sal45  2  EC
bob52e  1 HN
23 5 TR
```

***********
Compilation
***********
Use `make` or `make program` to compile the main application. It will create an executable in the `bin/` directory called `program`. This executable can be ran with a single argument which points to an input data file.

Use `make test` to compile the tests for this program. It will create an executable in the `bin/` directory called `test` which can then be ran without any arguments to run the triage program on the sample data in the assets folder.

Use `make cppcheck` to run the C style checker over every `.c` file in the project.

Use `make doxy` to run doxygen based on the Doxyfile and generate documentation for the project.

Use `make clean` to remove all built binary files and remove unnecessary files from the project.

************************************
Known Limitations, Issues and Errors
************************************
For the priority queue ADT, the anti-starvation algorithm isn't fool proof, if you do not pick an appropriate age to priority scale factor, the queue may behave in an unexpected manner to your goals. 

**********
Complexity
**********
#### The Big O notation for each PriorityQueueADT function. ####

createPriorityQueue: O(1)
- This function allocates a heap and a priority queue.

createPriorityQueueNode: O(1)
- Only performs allocation.

pushPriorityQueue: O(log n)
- Performs allocation then uses insertHeapNode to add the new item.

popPriorityQueue: O(n log n)
- Uses the heap's getMinOrMax and deleteMinOrMax functions to grab the top item from the heap.

peakPriorityQueue: O(1)
- Would ideally use the heap's getMinOrMax function to retrieve the top item.
- Since the heap has an error with getMinOrMax and heapifyDown, it would cause this function to have O(n log n), hence why this function manually retrieves the top item of the heap.

tickPriorityQueue: O(1)
- Increase the queues tick counter.

isEmptyPriorityQueue: O(1)
- Only checks the heap size.

destroyPriorityQueue: O(n)
- Uses the heap's deleteHeap function to deallocate the items, the heap, and the queue.

#### The Big O notation for each HeapADT function. ####

createHeap: O(1)
- The creation function only allocates space and initlizes variables which is a constant time process.

createHeapNode: O(1)
- Because I used an array implementation of the heap, the createHeapNode function does not perform any tasks.

insertHeapNode: O(log n)
- Since this function only checks the size, allocates, and finally runs heapifyUp, it has the same O as heapifyUp.

deleteMinOrMax: O(n log n)
- This function deallocates the data for the min/max then heapifies downwards.

getMinOrMax: O(n log n)
- This function will ensure its results are correct by first heapifying downwards, but in nearly all situations will have a constant runtime.

changeHeapType:: O(n log n)
- This function will nearly always run at a full n log n time since it must rearrange the entire heap for its new type.

deleteHeap: O(n)
- Since I used an array implementation, this function simply iterates over every heap item and deallocates it.

heapifyUp: O(log n)
- This function will potentially traverse all levels of the heap but not all items, since the levels contain expoentially more items each, this function performs in logerithmic time.

heapifyDown: O(n log n)
- This function simply performs heapifyUp on each element in the heap which gives it a max potintial time of n times the time for heapifyUp.
- Note: This is not an ideal implementation and instead should run in O(log n) time, I was simply unable to get it to function ideally.

checkSize: O(1)
- This function reallocates space for the array if nesscessary for the entire heap.

isBelow: O(1)
- This is a utility function to compares a node to another node.

*******
Testing
*******
TODO: Create >=4 input data files to test all possibilities for my priority queue

******
Design
******
#### Anti-Starvation Algorithm ####
When using a priority queue in a real world situation, it is necessary to prevent starvation. Starvation occurs when a low priority item in the queue is ignored constantly in favour of high priority items.

The chosen algorithm for my priority queue is the aging technique. This will allow the queue to take time into account and slowly increase the priority of all items as they "age" or get older. This will ensure that low priority items will eventually rise up to a high priority if they are forced to stay in the queue for a lengthy amount of time.

To implement aging in an effective fashion, it can calculate an age factor which will get applied during the heap's compare routine to effectively increase the priority of older items in the queue compared to more recent entries. For my implemention, time is considered in "ticks", typically each insertion or set of insertions will cause the queue to tick in turn increasing the age on the items in the queue.

For a given item's effective priority, `E(item)` (the priority considered by the heap and comparision routines), the age factor, `A(item)`, and original priority, `P(item)`, must be considered. The original priority is simple enough to find, it is the given priority when the item is inserted. On the other hand, the age factor must be calculated taking into consideration the time in ticks, `T(item)`, an item has been in the queue. To ease this calculation, an age to priority scale factor, `S(queue)`, must be assumed which will be taken when a priority queue is constructed. My chosen formula for calculation of the age factor is simply `A(item) = T(item)`. 

Therefore, the cumulative calcuation for the effective priority of an item is:
```
E(item) = P(item) + A(item) * S(queue)
```
When using my chosen formula, I recommend that the age to priority scale factor be somewhere in the range of `[0.0, 1.0]`, with 0 being age has no effect to 1 being that each tick of the system increases an item's priority by one level.

Sources:
 - https://www.ibm.com/support/knowledgecenter/SSEPGG_9.7.0/com.ibm.db2.luw.admin.wlm.doc/doc/c0051423.html
 - https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.iata700/iata70047.htm
 - https://en.wikipedia.org/wiki/Aging_(scheduling)

******
Output
******
TODO: How to read my report.txt
