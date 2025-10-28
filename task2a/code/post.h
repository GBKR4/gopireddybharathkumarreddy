#ifndef POST_H
#define POST_H

#include "comment.h"

typedef struct post {
    char username[50];
    char caption[200];
    struct comment *comments;
    struct post *next;          
    struct post *prev;         
} post;

post* createpost(char *username,char *caption);

#endif
