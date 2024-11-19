#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "statement.h"

// Fonction pour afficher db dans l'invite de commande
void print_prompt() 
{
    printf("db > ");
}

// Fonction pour afficher le résultat de l'exécution d'une commande
void print_execution_result(Result result) 
{
    switch (result) 
    {
        case EXECUTE_SUCCESS: printf("Executed.\n"); break;
        case EXECUTE_TABLE_FULL: printf("Error: Table is full.\n"); break;
        case EXECUTE_DUPLICATE_ID: printf("Error: ID already exists.\n"); break;
        case EXECUTE_ROW_NOT_FOUND: printf("Error: Row not found.\n"); break;
        case PREPARE_SYNTAX_ERROR: printf("Syntax error. Could not parse statement.\n"); break;
        case PREPARE_UNRECOGNIZED_STATEMENT: printf("Unrecognized keyword at start of statement.\n"); break;
        case META_COMMAND_UNRECOGNIZED_COMMAND: printf("Unrecognized command.\n"); break;
        default: break;
    }
}

// Fonction pour la boucle REPL (Read-Eval-Print Loop) (Fonction python de base)
void repl(Table* table) 
{
    char input[256];
    while (1) 
    {
        print_prompt();
        if (fgets(input, sizeof(input), stdin) == NULL) 
        {
            printf("Error reading input.\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '.') 
        {
            Result meta_result = do_meta_command(input, table);
            if (meta_result == META_COMMAND_UNRECOGNIZED_COMMAND) 
            {
                print_execution_result(meta_result);
            }
            continue;
        }

        Statement statement;
        Result prepare_result = prepare_statement(input, &statement);
        if (prepare_result != PREPARE_SUCCESS) 
        {
            print_execution_result(prepare_result);
            continue;
        }

         if (statement.type == STATEMENT_INSERT || statement.type == STATEMENT_UPDATE) // si la commande est insert ou update
        {
            if (statement.type == STATEMENT_UPDATE) 
            {
                printf("Enter ID to update: ");
                if (scanf("%d", &statement.id_to_update) != 1) 
                {
                    printf("Invalid input for ID.\n");
                    while (getchar() != '\n'); // Clear the input buffer
                    continue;
                }
                getchar(); // Pour consommer le caractère de nouvelle ligne restant
            }
            printf("Enter ID: ");
            if (scanf("%d", &statement.row_to_insert.id) != 1) 
            {
                printf("Invalid input for ID.\n");
                while (getchar() != '\n'); // Clear the input buffer
                continue;
            }
            getchar(); // Pour consommer le caractère de nouvelle ligne restant

            printf("Enter username: ");
            if (fgets(statement.row_to_insert.username, COLUMN_USERNAME_SIZE, stdin) == NULL) 
            {
                printf("Error reading username.\n");
                continue;
            }
            statement.row_to_insert.username[strcspn(statement.row_to_insert.username, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

            printf("Enter email: ");
            if (fgets(statement.row_to_insert.email, COLUMN_EMAIL_SIZE, stdin) == NULL) 
            {
                printf("Error reading email.\n");
                continue;
            }
            statement.row_to_insert.email[strcspn(statement.row_to_insert.email, "\n")] = '\0'; 

            if (strchr(statement.row_to_insert.email, '@') == NULL)  // Vérifier si l'email contient '@'
            {
                printf("Invalid email format. Missing '@'.\n");
                continue;
            }
        } 
        else if (statement.type == STATEMENT_DELETE) // si la commande est delete
        {
            printf("Enter ID to delete: ");
            if (scanf("%d", &statement.id_to_delete) != 1) 
            {
                printf("Invalid input for ID.\n");
                while (getchar() != '\n'); 
                continue;
            }
            getchar(); 
        }

        Result execute_result = execute_statement(&statement, table); 
        print_execution_result(execute_result);
    }
}

// Fonction principale
int main() 
{
    Table table = {.num_rows = 0};
    load_table(&table, "database.db");
    repl(&table);
    save_table(&table, "database.db");
    return 0;
}