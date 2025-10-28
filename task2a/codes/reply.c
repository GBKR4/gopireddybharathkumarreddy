#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reply.h"

Reply* createReply(char* username, char* content) {
    Reply* newReply = (Reply*)malloc(sizeof(Reply));
    if (newReply == NULL) return NULL;  
    newReply->username = (char*)malloc(strlen(username) + 1);
    if (newReply->username == NULL) {  
        free(newReply);
        return NULL;
    }
    strcpy(newReply->username, username);//string copying from one to other
    newReply->content = (char*)malloc(strlen(content) + 1);
    if (newReply->content == NULL) { 
        free(newReply->username);
        free(newReply);
        return NULL;
    }
    strcpy(newReply->content,content);
    newReply->next = NULL;
    newReply->prev = NULL;
    return newReply;
}
 //deleting the space
void freeReply(Reply* reply) {
    if (reply == NULL) return;
    free(reply->username);
    free(reply->content);
    free(reply);
}
