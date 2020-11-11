/** 
 * htable.h
 *
 * The header file for htable.c. 
 *
 * @author Naveen Mathew
 * @author Hugo Baird
 * @author Cedric Stephani
 */

#ifndef HTABLE_H_
#define HTABLE_H_

/**
 * Hash table structure.
 */
typedef struct htablerec *htable;

/**
 * Enumerator to choose collision resolution strategy.
 * LINEAR_P Linear probing
 * DOUBLE_H Double hashing
 */
typedef enum hashing_e { LINEAR_P, DOUBLE_H } hashing_t;

/**
 * Creates an instance of a hash table.
 *
 * @param capacity (int) states how many items the hash table can hold
 * @param method (hashing_t) states what collision resolution strategy to use
 * which can either be linear probing or double hashing
 * @return result the new hash table instance created
 */
extern htable htable_new(int capacity, hashing_t method);

/**
 * Inserts a word (string) into the hash table.
 *
 * @param h the hash table which is used to insert keys into
 * @param str the word to be inserted
 * @return 0 if the htable is full and frequency key occurs with if not
 */
extern int htable_insert(htable h, char *str);

/**
 * Searches through the hash table for specific words.
 *
 * @param h the hash table used to search for keys
 * @param str the word being searched for
 * @return 0 if word does not exist in hastable and frequency of key if not
 */
extern int htable_search(htable h, char *str);

/**
 * Prints out the hash table.
 *
 * @param h the hash table to be printed out
 * @param print_info a function passed in to print frequencies and the word
 */
extern void htable_print(void (*print_info)(int freq, char *words_stdin), 
											htable h);

/**
 * Prints the entire contents of the hash table.
 *
 * @param h the hash table to use to print out the entire contents
 */
extern void htable_print_entire_htable(htable h);

/**
 * Prints out a table reflecting what certain attribute values were at during
 * regular intervals stated by num_stats whilst the hash table is created.
 *
 * @param h the hashtable to use to print the statistics from
 * @param stream the stream to print output to
 * @param num_stats the maximum number of snapshot statistics to print out
 */
extern void htable_print_stats(htable h, FILE *stream, int num_stats);

/**
 * Frees up the memory allocated to the hash table.
 *
 * @param h the hash table to be freed from memory
 */
extern void htable_free(htable h);

/**
 * Converts a word to an integer to use as an index position for searching.
 *
 * @param word a pointer to a word
 * @return result the word that is converted to an int
 */
extern unsigned int htable_word_to_int(char *word);

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h the hash table
 * @param stream a stream to print the data to
 * @param percent_full the point at which to show the data from
 */
void print_stats_line(htable h, FILE *stream, int percent_full);

/**
 * Calculates double hashing step to be applied to the key when a
 * collision occurs in the hash table.
 *
 * @param h the hash table the step is calculated for
 * @param i_key the index of the data the step is calculated for
 * @return the step value to increase the hash
 */
unsigned int htable_step(htable h, unsigned int i_key);

#endif
