#ifndef TABLE_H
#define TABLE_H

#include <stddef.h>

#define COLUMN_USERNAME_SIZE 32 // 32 caractères pour le nom d'utilisateur
#define COLUMN_EMAIL_SIZE 255 // 255 caractères pour l'email
#define TABLE_MAX_ROWS 1000 // 1000 lignes maximum dans la table

// Structure pour les lignes dans la table
typedef struct 
{
    int id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

// Structure de la table
typedef struct 
{
    Row rows[TABLE_MAX_ROWS];
    size_t num_rows;
} Table;

//Résultats possibles des commandes
typedef enum 
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR,
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_ID,
    EXECUTE_ROW_NOT_FOUND
} Result;

struct Statement;

// Fonctions pour exécuter les commandes
Result execute_insert(struct Statement* statement, Table* table);
Result execute_show(Table* table);
Result execute_delete(struct Statement* statement, Table* table);
Result execute_update(struct Statement* statement, Table* table); 
Result do_meta_command(char* input, Table* table);
void save_table(Table* table, const char* filename);
void load_table(Table* table, const char* filename);

#endif