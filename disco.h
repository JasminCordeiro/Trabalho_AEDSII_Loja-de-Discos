
#ifndef disco_H_INCLUDED
#define disco_H_INCLUDED

typedef struct {
    int id;             
    char titulo[100];   
    char artista[100];  
    char genero[50];   
    int ano;            
    float preco;        
    int estoque;       
} Disco;

#endif