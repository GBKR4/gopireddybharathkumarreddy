#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>
#include "post.h"
#include "comment.h"
#include "reply.h"

post* currpost(post *head);
post* nextpost(post **lastviewedpost);
post* previouspost(post **lastviewedpost);
bool deletepost(post **head, int postindex);
bool addpost(post **head, char *username,char *caption);
bool addcomment(post *head, int postindex,char *username,char *content);
bool addreply(post *head, int postindex,int commentindex,char *username,char *content);
bool deletecomment(post *head,int postindex,int commentindex);
bool deletereply(post *head,int postindex,int commentindex,int replyindex);
void displayplatform(post *head);
void viewpost(post *head, int postindex);
void viewcomments(post *head,int postindex);
void deletereplylist(reply *head);
void freecommentlist(comment *head);
void freepost(post *head);

#endif
