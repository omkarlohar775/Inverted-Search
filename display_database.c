#include <stdio.h>
#include "inverted_search.h"

int display_database(main_node *hash_table[])
{
    int flag = 0;

    printf("\n");
    printf("===============================================================================\n");
    printf("%-8s %-20s %-12s %-25s %-12s\n","Index","Word","File Count","File Name","Word Count");
    printf("===============================================================================\n");

    for (int i = 0; i < HASH_SIZE; i++)
    {
        main_node *main_temp = hash_table[i];

        while (main_temp != NULL)
        {
            flag = 1;

            sub_node *sub_temp = main_temp->sub_link;

            int first_file = 1;

            while (sub_temp != NULL)
            {
                if (first_file)
                {
                    printf("%-8d %-20s %-12d %-25s %-12d\n",
                           i,
                           main_temp->word,
                           main_temp->file_count,
                           sub_temp->file_name,
                           sub_temp->word_count);

                    first_file = 0;
                }
                else
                {
                    printf("%-8s %-20s %-12s %-25s %-12d\n",
                           "",
                           "",
                           "",
                           sub_temp->file_name,
                           sub_temp->word_count);
                }

                sub_temp = sub_temp->link;
            }

            printf("-------------------------------------------------------------------------------\n");

            main_temp = main_temp->link;
        }
    }

    if (flag == 0)
    {
        printf("                         Database is empty\n");
        printf("===============================================================================\n");
        return SUCCESS;
    }

    return SUCCESS;
}