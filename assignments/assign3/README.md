****************************************************
```
Kanoa Haley                             0956712
CIS*2520                                Assignment 3
khaley@mail.uoguelph.ca                 July 19, 2017
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
Use `make` or `make program` to compile the main application. It will create an executable in the `bin/` directory called `program`. This executable can be ran using it's name followed by either `preserve` (for non-addition mode of the program) or `random` (for random arrival time addition) then an argument which points to an input data file.

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
### The Big O notation for each PriorityQueueADT function. ###

createPriorityQueue: O(1)
- This function allocates a heap and a priority queue.

createPriorityQueueNode: O(1)
- Only performs allocation.

pushPriorityQueue: O(log n)
- Performs allocation then uses insertHeapNode to add the new item.
- This function makes use of the anti-starvation algorithm during the compare process.

popPriorityQueue: O(n log n)
- Uses the heap's getMinOrMax and deleteMinOrMax functions to grab the top item from the heap.
- This function makes use of the anti-starvation algorithm during the compare process.

peakPriorityQueue: O(1)
- Would ideally use the heap's getMinOrMax function to retrieve the top item.
- Since the heap has an error with getMinOrMax and heapifyDown, it would cause this function to have O(n log n), hence why this function manually retrieves the top item of the heap.

tickPriorityQueue: O(1)
- Increase the queues tick counter.

isEmptyPriorityQueue: O(1)
- Only checks the heap size.

destroyPriorityQueue: O(n)
- Uses the heap's deleteHeap function to deallocate the items, the heap, and the queue.

### The Big O notation for each HeapADT function. ###

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
To test my algorithm effectively, I created the required four seperate sample data files each with a unique characteristic to target an aspect of the algorithm. Each data file (except for the fourth) contains 20 patients with the same IDs and symptoms, this is because these parameters of the simulation are entirely irrelevent to the algorithms success and are just forwarded through the program and only used again at the output.

Some of the files contain trailing newlines and others do not contain the newlines, this is to model the expectation that it could be used either way.

#### testSample1.txt ####
This file was the base file, designed to appear as any real-world (or as real-world as we'll get) file would. It's meant to check the algoritms robustness against normal data.

When the non-addition program is ran using this file, the report is as expected. Everything is ordered by priority.

When the full program (with random arrival time addition) is ran, the report produced includes wait times and ordered based on original priority as well as arrival time. When using the program default total time of 50, the average wait time tends to be in the range of 4 to 7, this seems resonable considering the 20 patients that are simulated.

Some notable results include seeing patients with a priority of 1 so close to the top, this occurs whenever a priority 1 patient arrives much earlier than the majority of the patients. For example, the following priority 1 patient was well above the majority of the others as a result of its arrival time being quite a bit above the average arrival time (especially for higher priority patients): `iv5, SK, 1, 7, 39`.

#### testSample2.txt ####
This file was designed with all patients having the same priority to test how well the aging algorithm worked when there wasn't a given difference in priority ever.

When the non-addition program is ran using this file, the report is unordered since there exists no logical priority.

When the full program is ran, the report shows that the patients are ordered in roughly their arrival time.

Notably, the arrival time is not the exact ordering, which means that there is a fault somewhere in the algorithm.

#### testSample3.txt ####
This file was designed with all patients having one of two priorities to test the aging algorithm with priorities playing a role.

As previously, the non-addition program performed as expected.

The full program performed exactly as expected as well, except for the minor issue found for the previous file.

This wasn't anything of note when testing this file.

#### testSample4.txt ####
This file was designed to test the program with a smaller set of patients than would normally be expected.

The non-addition program behaved exactly as expected everytime, always outputting the following:
```
vv3s, NV, 5
b40dlxoex, GI, 4
xh2, TR, 3
nh4d, HN, 2
3n244uy, CV, 1
```

The full program also always behaved exactly as expected.

### Testing Note ###
To gather my conclusions, I ran the full program over each testSample file over 20 times and inspected the produced `report.txt`. The commands I used are listed below.
```
./bin/program preserve assets/testSample1.txt
./bin/program random assets/testSample1.txt

./bin/program preserve assets/testSample2.txt
./bin/program random assets/testSample2.txt

./bin/program preserve assets/testSample3.txt
./bin/program random assets/testSample3.txt

./bin/program preserve assets/testSample4.txt
./bin/program random assets/testSample4.txt
```

******
Design
******
## Anti-Starvation Algorithm ##
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

## Additions Implemented ##
I decied to implement the addition to add time to the simulation described below as found on the assignment page:
> Change the simulation so that each client has an arrival time that is randomly generated as the data is read in from the file. Add a clock to the simulation and add the clients to the priority queue at their arrival time rather than all at once at the beginning of the simulation. The final report will include the total time spent as well as the time/per client and average time/client in addition to the order of processing. Run the simulation on all four of your data files both with and without the arrival time being used. In your README compare the results of the two different simulation approaches.

I chose this addition since my program is using the aging anti-starvation algorithm and I felt that this would help really showcase that ability of my priority queue. Without this addition, there really wouldn't be much demostration of the starvation prevention implemented. But, this provides a great ability to showcase the algorithm as well as make the simulation seem more realistic.

******
Output
******
The output will be saved as a report in a `.txt` file called `report.txt` (unless you ran the testing program, in which case it'll give you the output file names). This will will be in descending order with the first served patients at the top.

Depending on if the algorithm was run using randomly generated arrival times or assuming arrival all at the same time, the report will look different. 

For both types, each row of the report will start with the same original client data. The format `patient-id, patient-symptom, patient-priority` will be used.

### Random Arrival Time Report ###
For this style of simulation, the data file will end with a single line defining the total time of the simulation in addition to the average time each client spends waiting.

Each patient data line will be prepended by the patients time waiting. The line will end up look like this: `patient-id, patient-symptom, patient-priority, arrival-time, wait-time`

The time for this simulation is based on minutes since the start of the simulation (you could pick any abritrary start time).

### All-At-Once Arrival Time Report ###
When the simulation assumes that all the patients in the sample file arrived at the same time, it does not need to output any extra data. Each line will be as mentioned above in the beginning of the output section.
