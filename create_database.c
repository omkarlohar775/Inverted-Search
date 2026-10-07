#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverted_search.h"


/* Hash function */
int get_index(char *word)
{
    if (word[0] >= 'a' && word[0] <= 'z')
        return word[0] - 'a';

    if (word[0] >= 'A' && word[0] <= 'Z')
        return word[0] - 'A';

    return 26;
}


/* Create database */
int create_database(main_node *hash_table[], char *file_names[], int file_count)
{
    FILE *fptr;
    char word[WORD_SIZE];

    for (int i = 0; i < file_count; i++)
    {
        fptr = fopen(file_names[i], "r");

        if (fptr == NULL)
        {
            printf("ERROR: Cannot open %s\n", file_names[i]);
            continue;
        }

        while (fscanf(fptr, "%49s", word) != EOF)
        {
            int index = get_index(word);

            /* Search main node */
            main_node *main_temp = hash_table[index];

            while (main_temp != NULL && strcmp(main_temp->word, word) != 0)
            {
                main_temp = main_temp->link;
            }


            /* =================================================
               CASE 1: WORD DOES NOT EXIST
               ================================================= */

            if (main_temp == NULL)
            {
                main_node *new_main = malloc(sizeof(main_node));

                if (new_main == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->link = NULL;


                /* Create first sub node */
                sub_node *new_sub = malloc(sizeof(sub_node));

                if (new_sub == NULL)
                {
                    free(new_main);
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(new_sub->file_name, file_names[i]);
                new_sub->word_count = 1;
                new_sub->link = NULL;

                new_main->sub_link = new_sub;


                /* Insert main node */
                if (hash_table[index] == NULL)
                {
                    hash_table[index] = new_main;
                }
                else
                {
                    main_node *temp = hash_table[index];

                    while (temp->link != NULL)
                    {
                        temp = temp->link;
                    }
                    temp->link = new_main;
                }
            }


            /* =================================================
               CASE 2: WORD ALREADY EXISTS
               ================================================= */

            else
            {
                sub_node *sub_temp = main_temp->sub_link;

                /* Search whether current file already exists */
                while (sub_temp != NULL && strcmp(sub_temp->file_name, file_names[i]) != 0)
                {
                    sub_temp = sub_temp->link;
                }


                /* Same word + same file */
                if (sub_temp != NULL)
                {
                    sub_temp->word_count++;
                }


                /* Same word + different file */
                else
                {
                    sub_node *new_sub = malloc(sizeof(sub_node));

                    if (new_sub == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }

                    strcpy(new_sub->file_name, file_names[i]);

                    new_sub->word_count = 1;
                    new_sub->link = NULL;


                    /* Insert sub node */
                    sub_temp = main_temp->sub_link;

                    while (sub_temp->link != NULL)
                    {
                        sub_temp = sub_temp->link;
                    }

                    sub_temp->link = new_sub;

                    /* Increase file count */
                    main_temp->file_count++;
                }
            }
        }

        fclose(fptr);
    }

    return SUCCESS;
}