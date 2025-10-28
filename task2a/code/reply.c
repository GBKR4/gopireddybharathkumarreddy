#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reply.h"

reply* createreply(char *username,char *content) {
    if (username==NULL || content==NULL)return NULL;
    reply *newreply=(reply*)malloc(sizeof(reply));
    if (newreply==NULL)
        return NULL;
    strcpy(newreply->username, username);
    strcpy(newreply->content, content);
    newreply->next = NULL;
    newreply->prev = NULL;
    return newreply;
}
