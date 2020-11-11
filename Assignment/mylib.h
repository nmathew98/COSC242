/**
 * mylib.h
 *
 * Header file for declaring methods. 
 *
 * @author Naveen Mathew
 * @author Hugo Baird
 * @author Cedric Stephani
 */

#ifndef MYLIB_H_
#define MYLIB_H_

/**
 * emalloc function which allocates a block of memory.
 * 
 * @param s the size of memory needed to be allocated
 * @return a the memory address where the data has been allocated to
 */
extern void *emalloc(size_t);

/**
 * getword function which reads in a word from a stream until limit is reached.
 * 
 * @param s the char pointer to array s
 * @param limit the length of array s
 * @param stream the source of the words
 * @return EOF if we have reached the end
 */
extern int getword(char *s, int limit, FILE *stream);

/**
 * Checks if a number is a prime number.
 *
 * @param  n The number to check
 * @return 0 For False and 1 for True
 */
extern int is_prime(int n);

#endif
