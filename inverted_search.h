#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#define SUCCESS 0
#define FAILURE -1

#define WORD_SIZE 50
#define FNAME_SIZE 50
#define HASH_SIZE 27

typedef struct sub_node
{
    int word_count;
    char file_name[FNAME_SIZE];
    struct sub_node *link;

} sub_node;

typedef struct main_node
{
    int file_count;
    char word[WORD_SIZE];

    sub_node *sub_link;
    struct main_node *link;

} main_node;


int get_index(char *word);
int create_database(main_node *hash_table[], char *file_names[], int file_count);
int display_database(main_node *hash_table[]);
int search_database(main_node *hash_table[], char *word);
int save_database(main_node *hash_table[], char *file_name);
int update_database(main_node *hash_table[], char *file_name);

#endif