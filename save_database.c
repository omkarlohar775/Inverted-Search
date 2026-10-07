#include <stdio.h>
#include <string.h>
#include "inverted_search.h"

int save_database(main_node *hash_table[], char *file_name)
{
    FILE *fptr;

    /* Open file in write mode */
    fptr = fopen(file_name, "w");

    if (fptr == NULL)
    {
        printf("ERROR: Cannot open file %s\n", file_name);
        return FAILURE;
    }

    /* Traverse hash table */
    for (int i = 0; i < HASH_SIZE; i++)
    {
        main_node *main_temp = hash_table[i];

        while (main_temp != NULL)
        {
            /*
             * Write hash index and main node information
             */
            fprintf(fptr, "#%d;%s;%d;", i, main_temp->word, main_temp->file_count);

            /* Traverse sub nodes */
            sub_node *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                fprintf(fptr, "%s;%d;", sub_temp->file_name, sub_temp->word_count);

                sub_temp = sub_temp->link;
            }

            fprintf(fptr, "#\n");

            main_temp = main_temp->link;
        }
    }

    fclose(fptr);

    printf("Database saved successfully in %s\n", file_name);

    return SUCCESS;
}