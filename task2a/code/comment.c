#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comment.h"

comment* createcomment(char *username,char *content) {
    if (username==NULL || content==NULL)
        return NULL;
    comment *newcomment=(comment*)malloc(sizeof(comment));
    if (newcomment==NULL){
        return NULL;
    }
    strcpy(newcomment->username,username);
    strcpy(newcomment->content,content);
    newcomment->replies = NULL;
    newcomment->next = NULL;
    newcomment->prev = NULL;
    return newcomment;
}
