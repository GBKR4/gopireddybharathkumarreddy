#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "post.h"
#include "comment.h"

Post* createPost(char* username, char* caption) {
    Post* newPost = (Post*)malloc(sizeof(Post));
    if (newPost == NULL) return NULL;   
    newPost->username = (char*)malloc(strlen(username) + 1);
    if (newPost->username == NULL) {    
        free(newPost);
        return NULL;
    }
    strcpy(newPost->username, username);//string copying from one to other
    newPost->caption = (char*)malloc(strlen(caption) + 1);
    if (newPost->caption == NULL) { 
        free(newPost->username);
        free(newPost);
        return NULL;
    }
    strcpy(newPost->caption, caption);
    newPost->comments = NULL;
    newPost->next = NULL;
    newPost->prev = NULL;

    return newPost;
}

//removes allocated space
void freePost(Post* post) {
    if (post == NULL) return;   
    comment* current = post->comments;
    while (current != NULL) {  
        comment* temp = current;
        current = current->next;
        freeComment(temp);
    }
    free(post->username);
    free(post->caption);
    free(post);
}
