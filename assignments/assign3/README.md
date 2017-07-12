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

***********
Compilation
***********
Use `make` or `make program` to compile the main application. It will create an executable in the `bin/` directory called program.

Use `make test` to compile the unit tests for this program. It will create an executable in the `bin/` directory called `test` which can then be ran without any arguments to run unit tests over the code.

Use `make cppcheck` to run the C style checker over every `.c` file in the project.

Use `make doxy` to run doxygen based on the Doxyfile and generate documentation for the project.

Use `make clean` to remove all built binary files and remove unnecessary files from the project.

************************************
Known Limitations, Issues and Errors
************************************

**********
Complexity
**********

*********
Algorithm
*********
When using a priority queue in a real world situation, it is necessary to prevent stravation. Stravation occurs when a low-priority item in the queue is ignored constantly in favour of high priority items.

The chosen algoritm for my priority queue is the aging technique. This will allow the queue to take time into account and slowly increase the priority of all items as they "age" or get older. This will ensure that low-priority items will eventually rise up to a high priority if they are forced to stay in the queue for a lengthy amount of time.

To implement aging in an effective fashion, the priority queue must know the range of the priority for the items in it. Using this, it can calculate an age factor which will get applied during the heap's compare routine to effectively increase the priority of older items in the queue compared to more recent entries. For my implemention, time is considered in "ticks", typically each insertion or set of insertions will cause the queue to tick in turn increasing the age on the items in the queue.

For a given items effective priority, `E(item)` (the priority considered by the heap and comparision routines), the age factor, `A(item)`, and original priority, `P(item)`, must be considered. The original priority is simple enough to find, it is the given priority when the item is inserted. On the other hand, the age factor must be calculated taking into consideration the time in ticks, `T(item)`, an item has been in the queue. To ease this calculation an age to priority scale factor, `S(queue)`, must be assumed which will be taken when a priority queue is constructed. My chosen formula for calculation of the age factor is simply `A(item) = T(item)`. 

Therefore, the cumulative calcuation for the effective priority of an item is:
```
E(item) = P(item) + A(item) * S(queue)
```
When using my chosen formula, I recommend that the age to priority scale factor be somewhere in the range of `[0.0, 1.0]`, with 0 being age has no effect to 1 being that each tick of the system increases an items priority by one level.

Sources:
 - https://www.ibm.com/support/knowledgecenter/SSEPGG_9.7.0/com.ibm.db2.luw.admin.wlm.doc/doc/c0051423.html
 - https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.iata700/iata70047.htm
 - https://en.wikipedia.org/wiki/Aging_(scheduling)
