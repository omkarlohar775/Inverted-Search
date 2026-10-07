#include <stdio.h>
#include <string.h>
#include "inverted_search.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("ERROR: No input files passed\n");
        printf("Usage: ./a.out file1.txt file2.txt ...\n");
        return FAILURE;
    }

    // hash table
    main_node *hash_table[HASH_SIZE];

    // Intialize hash table
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    int choice;

    while (1)
    {
        printf("Select your choice among following options:\n");
        printf("1. Create DATABASE\n");
        printf("2. Display Database\n");
        printf("3. Serach Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Create database..\n");

            if (create_database(hash_table, &argv[1], argc - 1) == SUCCESS)
                printf("Database created successfully\n");
            else
                printf("Database creation failed\n");

            break;

        case 2:
            display_database(hash_table);
            break;

        case 3:
        {
            char word[WORD_SIZE];

            printf("Enter the word you want to search: ");
            scanf("%s", word);

            search_database(hash_table, word);
            break;
        }

        case 4:
        {
            char file_name[FNAME_SIZE];

            printf("Enter the file name to save database: ");
            scanf("%s", file_name);

            save_database(hash_table, file_name);
            break;
        }

        case 5:
        {
            char file_name[FNAME_SIZE];

            printf("Enter the file name to update data: ");
            scanf("%s", file_name);

            if (update_database(hash_table, file_name) == SUCCESS)
            {
                printf("Database updated successfully\n");
            }
            else
            {
                printf("Database update failed\n");
            }
            break;
        }

        case 6:
        {
            printf("Exiting...\n");
            return SUCCESS;
        }

        default:
            printf("Invalid choice");
        }

        char option;

        /* Continue or discontinue */
        printf("\nDo you want to continue ?\n");
        printf("Enter y/Y to continue and n/N to discontinue: ");

        scanf(" %c", &option);

        if (option == 'n' || option == 'N')
        {
            break;
        }
        else if (option != 'y' && option != 'Y')
        {
            printf("Invalid option\n");
            break;
        }
    }
    return SUCCESS;
}