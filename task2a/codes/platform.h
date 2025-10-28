#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>
#include "post.h"
#include "comment.h"

typedef struct Platform {
    Post* posts;
    Post* lastViewedPost;
    int postCount;
} Platform;

extern Platform* plat_form;  
Platform* createPlatform();
bool addPost(char* username, char* caption);
bool deletePost(int n);
Post* viewPost(int n);
Post* currPost();
Post* nextPost();
Post* previousPost();
bool addComment(char* username, char* content);
bool deleteComment(int n);
comment* viewComments();
bool addReply(char* username, char* content, int n);
bool deleteReply(int n, int m);
void freePlatform(Platform* platform);

#endif
