#ifndef REPLY_H
#define REPLY_H

typedef struct reply {
    char username[50];
    char content[200];
    struct reply *next;      
    struct reply *prev;      
} reply;
reply* createreply(char *username,char *content);
#endif
