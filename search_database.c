#include <stdio.h>
#include <string.h>
#include "inverted_search.h"

int search_database(main_node *hash_table[], char *word)
{
    /* Calculate hash index */
    int index = get_index(word);

    /* Start from that bucket */
    main_node *main_temp = hash_table[index];

    /* Search the word */
    while (main_temp != NULL)
    {
        if (strcmp(main_temp->word, word) == 0)
        {
            printf("\nWord \"%s\" found\n", word);
            printf("File count: %d\n", main_temp->file_count);

            /* Traverse sub nodes */
            sub_node *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                printf("%s -> %d\n", sub_temp->file_name, sub_temp->word_count);
                sub_temp = sub_temp->link;
            }
            return SUCCESS;
        }
        main_temp = main_temp->link;
    }

    /* Word not found */
    printf("\nWord \"%s\" not found\n", word);

    return FAILURE;
}