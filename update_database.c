#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverted_search.h"

int update_database(main_node *hash_table[], char *file_name)
{
    FILE *fptr;
    char line[500];

    /* Open backup file */
    fptr = fopen(file_name, "r");

    if (fptr == NULL)
    {
        printf("ERROR: Cannot open file %s\n", file_name);
        return FAILURE;
    }

    /* Read one database entry at a time */
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        int index;
        int file_count;

        char word[WORD_SIZE];

        char *token;

        /* Remove newline */
        line[strcspn(line, "\n")] = '\0';

        /* Validate database format */
        if (line[0] != '#')
        {
            printf("ERROR: Invalid database file\n");
            fclose(fptr);
            return FAILURE;
        }

        /* First token = hash index */
        token = strtok(line, ";");

        if (token == NULL)
            continue;

        index = atoi(token + 1);

        if (index < 0 || index >= HASH_SIZE)
        {
            printf("ERROR: Invalid hash index\n");
            fclose(fptr);
            return FAILURE;
        }

        /* Second token = word */
        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        strcpy(word, token);


        /* Third token = file count */
        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        file_count = atoi(token);


        /* Create main node */
        main_node *new_main =
            malloc(sizeof(main_node));

        if (new_main == NULL)
        {
            fclose(fptr);
            return FAILURE;
        }

        strcpy(new_main->word, word);
        new_main->file_count = file_count;
        new_main->link = NULL;
        new_main->sub_link = NULL;


        /* Create sub nodes */
        sub_node *sub_tail = NULL;

        for (int i = 0; i < file_count; i++)
        {
            /* File name */
            token = strtok(NULL, ";");

            if (token == NULL)
            {
                free(new_main);
                fclose(fptr);
                return FAILURE;
            }

            sub_node *new_sub =
                malloc(sizeof(sub_node));

            if (new_sub == NULL)
            {
                fclose(fptr);
                return FAILURE;
            }

            strcpy(new_sub->file_name, token);


            /* Word count */
            token = strtok(NULL, ";");

            if (token == NULL)
            {
                free(new_sub);
                free(new_main);
                fclose(fptr);
                return FAILURE;
            }

            new_sub->word_count = atoi(token);
            new_sub->link = NULL;


            /* Insert sub node */
            if (new_main->sub_link == NULL)
            {
                new_main->sub_link = new_sub;
                sub_tail = new_sub;
            }
            else
            {
                sub_tail->link = new_sub;
                sub_tail = new_sub;
            }
        }


        /* Insert main node into hash table */
        if (hash_table[index] == NULL)
        {
            hash_table[index] = new_main;
        }
        else
        {
            main_node *main_temp = hash_table[index];

            while (main_temp->link != NULL)
            {
                main_temp = main_temp->link;
            }

            main_temp->link = new_main;
        }
    }

    fclose(fptr);

    return SUCCESS;
}