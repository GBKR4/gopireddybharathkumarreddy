#ifndef COMMENT_H
#define COMMENT_H

#include "reply.h"

typedef struct comment {
    char username[50];
    char content[200];
    struct reply *replies;       
    struct comment *next;       
    struct comment *prev;        
} comment;
comment* createcomment(char *username,char *content);
#endif
