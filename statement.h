#ifndef STATEMENT_H
#define STATEMENT_H

#include "table.h"

// Enumération des types de déclarations
typedef enum { STATEMENT_INSERT, STATEMENT_SHOW, STATEMENT_DELETE,STATEMENT_UPDATE } 
StatementType;

typedef struct Statement 
{
    StatementType type;
    Row row_to_insert;
    int id_to_delete;
    int id_to_update; 
} 

Statement;

// Fonctions pour préparer et exécuter les déclarations
Result prepare_statement(char* input, Statement* statement);
Result execute_statement(Statement* statement, Table* table);

#endif