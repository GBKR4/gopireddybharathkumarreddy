#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "post.h"

post* createpost(char *username,char *caption) {
    if (username==NULL || caption==NULL)
        return NULL;
    post *newpost=(post*)malloc(sizeof(post));
    if (newpost==NULL)
        return NULL;
    strcpy(newpost->username, username);
    strcpy(newpost->caption, caption);
    newpost->comments = NULL;
    newpost->next = NULL;
    newpost->prev = NULL;

    return newpost;
}
