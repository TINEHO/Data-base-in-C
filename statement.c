#include "statement.h"
#include <stdio.h>
#include <string.h>

// Fonction pour préparer une déclaration à partir de l'entrée utilisateur
Result prepare_statement(char* input, Statement* statement) 
{
    if (strncmp(input, "insert", 6) == 0) 
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(input, "show") == 0) 
    {
        statement->type = STATEMENT_SHOW;
        return PREPARE_SUCCESS;
    }
    if (strncmp(input, "delete", 6) == 0) 
    {
        statement->type = STATEMENT_DELETE;
        return PREPARE_SUCCESS;
    }
     if (strncmp(input, "update", 6) == 0) 
    {
        statement->type = STATEMENT_UPDATE;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

// Fonction pour exécuter les déclarations
Result execute_statement(Statement* statement, Table* table) 
{
    switch (statement->type)
    {
        case STATEMENT_INSERT: return execute_insert(statement, table);
        case STATEMENT_SHOW: return execute_show(table);
        case STATEMENT_DELETE: return execute_delete(statement, table);
        case STATEMENT_UPDATE: return execute_update(statement, table);
    }
    return EXECUTE_SUCCESS;
}