#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comment.h"
#include "reply.h"

comment* createcomment(char* username, char* content) {
    comment* newComment = (comment*)malloc(sizeof(comment));//allocate space
    if (!newComment) return NULL;  
    newComment->username = (char*)malloc(strlen(username) + 1);
    if (newComment->username == NULL) { 
        free(newComment);
        return NULL;
    }
    strcpy(newComment->username, username);//string copying from one to other
    newComment->content = (char*)malloc(strlen(content) + 1);
    if (newComment->content == NULL) { 
        free(newComment->username);
        free(newComment);
        return NULL;
    }
    strcpy(newComment->content, content);
    newComment->replies = NULL;
    newComment->next = NULL;
    newComment->prev = NULL;

    return newComment;
}

//removes allocated space
void freeComment(comment* comment) {
    if (comment == NULL) return;  

    Reply* current = comment->replies;
    while (current != NULL) {      
        Reply* temp = current;
        current = current->next;
        freeReply(temp);
    }
    free(comment->username);
    free(comment->content);
    free(comment);
}
