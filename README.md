# EdgeDebounce

EdgeDebounce is a lightweight yet capable switch debouncer.

The algorithm was inpired by an article that can be found at: http://www.ganssle.com/debouncing.htm

Step 1 : Read the pin 16 times

Step 2 : If all the reads are identical return what has been read

Step 3 : If not, go back to step 1

The number of times the pin is read in step 1 can be adjusted between 1 and 32
