    #include "table.h"
    #include "statement.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // Fonction pour exécuter les commandes méta ( .exit, .help, .status)
    Result do_meta_command(char* input, Table* table) 
    {
        if (strcmp(input, ".exit") == 0)  // Quitter le programme
        {
            save_table(table, "database.db");
            exit(EXIT_SUCCESS);
        } 
        else if (strcmp(input, ".help") == 0)  // Afficher les commandes possibles
        {
            printf("Available commands:\n");
            printf(".exit - Exit the program\n");
            printf(".help - Show this help message\n");
            printf("insert - Insert a new row\n");
            printf("show - Show all rows\n");
            printf("delete - Delete a row by ID\n");
            return META_COMMAND_SUCCESS;
        } 
        else if (strcmp(input, ".status") == 0) 
        {
            // Afficher le nb de ligne de la base de données
            printf("Database status:\n");  
            printf("Number of rows: %zu\n", table->num_rows);
            return META_COMMAND_SUCCESS;
        }
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }

    // Fonction pour insérer une ligne dans la table
    Result execute_insert(Statement* statement, Table* table) 
    {
        if (table->num_rows >= TABLE_MAX_ROWS) return EXECUTE_TABLE_FULL;
        for (size_t i = 0; i < table->num_rows; i++)
        {
            if (table->rows[i].id == statement->row_to_insert.id) return EXECUTE_DUPLICATE_ID;
        }
        table->rows[table->num_rows++] = statement->row_to_insert;
        return EXECUTE_SUCCESS;
    }

    // Fonction pour afficher toutes les lignes de la table
    Result execute_show(Table* table) 
    {
        for (size_t i = 0; i < table->num_rows; i++) 
        {
            Row* row = &table->rows[i];
            printf("(%d, %s, %s)\n", row->id, row->username, row->email);
        }
        return EXECUTE_SUCCESS;
    }

    // Fonction pour supprimer une ligne de la table par ID
    Result execute_delete(Statement* statement, Table* table) 
    {
        for (size_t i = 0; i < table->num_rows; i++) 
        {
            if (table->rows[i].id == statement->id_to_delete) 
            {
                table->rows[i] = table->rows[table->num_rows - 1];
                table->num_rows--;
                return EXECUTE_SUCCESS;
            }
        }
        return EXECUTE_ROW_NOT_FOUND;
    }

    // Fonction pour sauvegarder la table dans un fichier
    void save_table(Table* table, const char* filename) 
    {
        FILE* file = fopen(filename, "wb"); // wb = write binary
        if (file == NULL) 
        {
            printf("Error: Could not open file for writing.\n");
            return;
        }
        fwrite(&table->num_rows, sizeof(size_t), 1, file);
        fwrite(table->rows, sizeof(Row), table->num_rows, file);
        fclose(file);
    }

    // Fonction pour mettre à jour une ligne de la table par ID
    Result execute_update(Statement* statement, Table* table) 
    {
     for (size_t i = 0; i < table->num_rows; i++) 
        {
        if (table->rows[i].id == statement->id_to_update) 
            {
                table->rows[i] = statement->row_to_insert;
                return EXECUTE_SUCCESS;
            }
        }
        return EXECUTE_ROW_NOT_FOUND;
    }


    // Fonction pour charger la table depuis un fichier
    void load_table(Table* table, const char* filename) 
    {
        FILE* file = fopen(filename, "rb"); // read binary
        if (file == NULL) 
        {
            printf("Error: Could not open file for reading.\n");
            return;
        }
        // lecture de la taille de la table
        fread(&table->num_rows, sizeof(size_t), 1, file);       
        fread(table->rows, sizeof(Row), table->num_rows, file);
        fclose(file);
    }