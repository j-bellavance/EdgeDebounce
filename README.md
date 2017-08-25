# EdgeDebounce

Version 1.2 : August 25, 2017 (See tutorial for changes)

EdgeDebounce is a lightweight yet capable switch debouncer.

The algorithm was inpired by an article that can be found at: http://www.ganssle.com/debouncing.htm

Step 1 : Read the pin n times (n is between 1 and 32, defaults to 16)

Step 2 : If all the reads are identical return what has been read

Step 3 : If not, go back to step 1
