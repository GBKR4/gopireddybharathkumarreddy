#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"

Platform* plat_form = NULL;

Platform* createPlatform() {
    Platform* platform = (Platform*)malloc(sizeof(Platform));
    if (platform == NULL) return NULL;
    platform->posts = NULL;
    platform->lastViewedPost = NULL;
    platform->postCount = 0;
    plat_form = platform;
    return platform;
}

bool addPost(char* username, char* caption) {
    if (plat_form == NULL) return false;
    Post* newPost = createPost(username, caption);
    if (newPost == NULL) return false;

    if (plat_form->posts == NULL) {
        plat_form->posts = newPost;
        plat_form->lastViewedPost = newPost;
    } else {
        newPost->next = plat_form->posts;
        plat_form->posts->prev = newPost;
        plat_form->posts = newPost;
    }

    plat_form->postCount++;
    return true;
}

//code to delpost
bool deletePost(int n) {
    if (plat_form == NULL || plat_form->posts == NULL || n <= 0)
        return false;
    Post* current = plat_form->posts;
    int count = 1;
    while (current != NULL && count < n) {
        current = current->next;
        count++;
    }
    if (current == NULL) return false;
    if (plat_form->lastViewedPost == current) {
        if (current->next != NULL)
            plat_form->lastViewedPost = current->next;
        else if (current->prev != NULL)
            plat_form->lastViewedPost = current->prev;
        else
            plat_form->lastViewedPost = NULL;
    }
    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        plat_form->posts = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    freePost(current);
    plat_form->postCount--;

    return true;
}

//code to view post
Post* viewPost(int n) {
    if (plat_form == NULL || plat_form->posts == NULL || n <= 0)
        return NULL;

    Post* current = plat_form->posts;
    int count = 1;

    while (current != NULL && count < n) {
        current = current->next;
        count++;
    }

    if (current != NULL)
        plat_form->lastViewedPost = current;

    return current;
}

//code ot currpist
Post* currPost() {
    if (plat_form == NULL) return NULL;
    return plat_form->lastViewedPost;
}

//code to next post
Post* nextPost() {
    if (plat_form == NULL || plat_form->lastViewedPost == NULL) return NULL;
    if (plat_form->lastViewedPost->next != NULL)
        plat_form->lastViewedPost = plat_form->lastViewedPost->next;

    return plat_form->lastViewedPost;
}

//code to previous post
Post* previousPost() {
    if (plat_form == NULL || plat_form->lastViewedPost == NULL) return NULL;
    if (plat_form->lastViewedPost->prev != NULL) {
        plat_form->lastViewedPost = plat_form->lastViewedPost->prev;
    }

    return plat_form->lastViewedPost;
}

bool addComment(char* username, char* content) {
    if (plat_form == NULL || plat_form->lastViewedPost == NULL) {
        return false;
    }

    comment* newComment = createcomment(username, content);
    if (newComment == NULL) return false;

    if (plat_form->lastViewedPost->comments == NULL) {
        plat_form->lastViewedPost->comments = newComment;
    } else {
        comment* tail = plat_form->lastViewedPost->comments;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newComment;
        newComment->prev = tail;
    }

    return true;
}

bool deleteComment(int n) {
    if (plat_form == NULL || plat_form->lastViewedPost == NULL ||
        plat_form->lastViewedPost->comments == NULL || n <= 0) {
        return false;
    }

    int total = 0;
    comment* temp = plat_form->lastViewedPost->comments;
    while (temp != NULL) {
        total++;
        temp = temp->next;
    }

    int targetPos = total - n + 1;
    if (targetPos <= 0) {
        return false;
    }

    comment* current = plat_form->lastViewedPost->comments;
    for (int i = 1; i < targetPos && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        plat_form->lastViewedPost->comments = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    freeComment(current);
    return true;
}

comment* viewComments() {
    if (plat_form == NULL || plat_form->lastViewedPost == NULL) {
        return NULL;
    }

    return plat_form->lastViewedPost->comments;
}

bool addReply(char* username, char* content, int n) {
    if (plat_form == NULL || plat_form->lastViewedPost == NULL ||
        plat_form->lastViewedPost->comments == NULL || n <= 0) {
        return false;
    }

    int total = 0;
    comment* temp = plat_form->lastViewedPost->comments;
    while (temp != NULL) {
        total++;
        temp = temp->next;
    }

    int targetPos = total - n + 1;
    if (targetPos <= 0) {
        return false;
    }

    comment* current = plat_form->lastViewedPost->comments;
    for (int i = 1; i < targetPos && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    Reply* newReply = createReply(username, content);
    if (newReply == NULL) {
        return false;
    }

    if (current->replies == NULL) {
        current->replies = newReply;
    } else {
        Reply* tail = current->replies;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newReply;
        newReply->prev = tail;
    }

    return true;
}

//code to del_reply
bool deleteReply(int n, int m) {
    if (plat_form == NULL || plat_form->lastViewedPost == NULL ||
        plat_form->lastViewedPost->comments == NULL || n <= 0 || m <= 0) {
        return false;
    }

    int totalComments = 0;
    comment* tempComment = plat_form->lastViewedPost->comments;
    while (tempComment != NULL) {
        totalComments++;
        tempComment = tempComment->next;
    }

    int targetCommentPos = totalComments - n + 1;
    if (targetCommentPos <= 0) {
        return false;
    }

    comment* comment = plat_form->lastViewedPost->comments;
    for (int i = 1; i < targetCommentPos && comment != NULL; i++) {
        comment = comment->next;
    }

    if (comment == NULL || comment->replies == NULL) {
        return false;
    }

    int totalReplies = 0;
    Reply* tempReply = comment->replies;
    while (tempReply != NULL) {
        totalReplies++;
        tempReply = tempReply->next;
    }

    int targetReplyPos = totalReplies - m + 1;
    if (targetReplyPos <= 0) {
        return false;
    }

    Reply* reply = comment->replies;
    for (int i = 1; i < targetReplyPos && reply != NULL; i++) {
        reply = reply->next;
    }

    if (reply == NULL) {
        return false;
    }

    if (reply->prev != NULL) {
        reply->prev->next = reply->next;
    } else {
        comment->replies = reply->next;
    }

    if (reply->next != NULL) {
        reply->next->prev = reply->prev;
    }

    freeReply(reply);
    return true;
}

//code to_free_platform
void freePlatform(Platform* platform) {
    if (platform == NULL) return;

    Post* current = platform->posts;
    while (current != NULL) {
        Post* temp = current;
        current = current->next;
        freePost(temp);
    }

    free(platform);
}