#define _POSIX_C_SOURCE 200809L   // strdup(), stpcpy()
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "strutil.h"

char *substr(const char *str, size_t n){
    size_t largo = strlen(str);
    size_t hasta = n;
    char *new_str = malloc(sizeof(char) * (largo + 1));
    if(!new_str) return NULL;

    if(n > largo)
        hasta = largo;
    
    size_t i = 0;
    for(i = 0; i < hasta; i++){
        new_str[i] = str[i];
    }

    new_str[i] = '\0';
    return new_str;
}

char **split(const char *str, char sep){
    int cantidad_sep = 0;
    for(size_t i = 0; str[i] != '\0'; i++){
        if(str[i] == sep)
            cantidad_sep++;
    }

    //Pido memoria para dos más, la palabra que viene despues de la ultima coma y para el NULL
    char **str_array = malloc((cantidad_sep + 2) * sizeof(char*));
    if(!str_array) return NULL;

    size_t i = 0, pos_sep = 0, j = 0;

    for(i = 0; str[i] != '\0'; i++){
        if(str[i] == sep){
            str_array[j++] = substr(str + pos_sep, i - pos_sep);
            pos_sep = i + 1;
        }
    }
    
    str_array[cantidad_sep] = substr(str + pos_sep,i );

    str_array[cantidad_sep+1] = NULL;
    return str_array;
}

void free_strv(char *strv[]){
    for(size_t i = 0; strv[i] != NULL; i++)
        free(strv[i]);
    
    free(strv);
}

char *join(char **strs, char sep){
    if(strs[0] == NULL){
        char *str = malloc(sizeof(char) * 1);
        if(!str)    return NULL;
        str[0] = '\0';
        return str;
    }
    
    size_t n = 0, i;
    for(i = 0; strs[i] != NULL; i++)
        n += strlen(strs[i]);

    char * str = malloc(sizeof(char) * (n+i));
    if(!str)    return NULL;

    size_t pos = 0;

    for(i = 0; strs[i] != NULL; i++){
        strcpy(str + pos,strs[i]);
        pos += strlen(strs[i]);
        str[pos++] = sep;
        if(sep == '\0'){
            pos--;
        }
    }

    if(sep == '\0')
        str[pos] = '\0';
    else
        str[pos-1] = '\0';

    return str;
}


        // char *puntero_a_final =  stpcpy(str,strs[0]);
    // puntero_a_final = stpcpy(puntero_a_final,&sep);
        // puntero_a_final = stpcpy(puntero_a_final,strs[i]);
        // puntero_a_final = stpcpy(puntero_a_final,&sep);
            // puntero_a_final--;
    // puntero_a_final = '\0';

        // if(sep != '\0')
        //     str[pos++] = sep;
        // else{
        //     printf("Entre\n");
        //     pos--;
        // }

