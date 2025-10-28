#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"

#define Max_INPUT 400//it replaces every MAX_INPUT with 400

void printPost(Post* post) {
    if (post == NULL) {
        return;
    }
    printf("%s %s\n", post->username, post->caption);
}

//prints all comments
void print_all_Comments(comment* commentHead) {
    if (commentHead == NULL) {
        return;
    }
    comment* current = commentHead;
    while (current != NULL) {
        printf("%s %s\n", current->username, current->content);
        Reply* replyPtr = current->replies; 
        while (replyPtr != NULL) {
            printf("%s %s\n", replyPtr->username, replyPtr->content);
            replyPtr = replyPtr->next;
        }

        current = current->next;
    }
}

int main() {
    char command[Max_INPUT];
    while (1) {
        if (scanf("%s", command) != 1) {
            break;
        }

        if (strcmp(command, "create_platform") == 0) {
            plat_form= createPlatform();
            if (plat_form==NULL) {
                printf("Failed to create platform\n");
            }
        }
        else if (strcmp(command, "add_post") == 0) {
            char username[Max_INPUT], caption[Max_INPUT];
            scanf("%s %s", username, caption);

            if (!addPost(username, caption)) {
                printf("Failed to add post\n");
            }
        }
        else if (strcmp(command, "delete_post") == 0) {
            int n;
            scanf("%d", &n);

            if (!deletePost(n)) {
                printf("Failed to delete post\n");
            }
        }
        else if (strcmp(command, "view_post") == 0) {
            int n;
            scanf("%d", &n);
            Post* post = viewPost(n);
            if (post != NULL) {
                printPost(post);
            } else {
                printf("Post does not exist\n");
            }
        }
        else if (strcmp(command, "current_post") == 0) {
            Post* post = currPost();
            if (post != NULL) {
                printPost(post);
            } else {
                printf("No current post\n");
            }
        }
        else if (strcmp(command, "next_post") == 0) {
            Post* post = nextPost();
            if (post != NULL) {
                printPost(post);
            } else {
                printf("Next post does not exist\n");
            }
        }
        else if (strcmp(command, "previous_post") == 0) {
            Post* post = previousPost();
            if (post != NULL) {
                printPost(post);
            } else {
                printf("Previous post does not exist\n");
            }
        }
        else if (strcmp(command, "add_comment") == 0) {
            char username[Max_INPUT], content[Max_INPUT];
            scanf("%s %s", username, content);

            if (!addComment(username, content)) {
                printf("Failed to add comment\n");
            }
        }
        else if (strcmp(command, "delete_comment") == 0) {
            int n;
            scanf("%d", &n);

            if (!deleteComment(n)) {
                printf("Failed to delete comment\n");
            }
        }
        else if (strcmp(command, "view_comments") == 0) {
            comment* comments = viewComments();
            if (comments != NULL) {
                print_all_Comments(comments);
            }
        }
        else if (strcmp(command, "view_all_comments") == 0) {
            comment* comments = viewComments();
            if (comments != NULL) {
                print_all_Comments(comments);
            }
        }
        else if (strcmp(command, "add_reply") == 0) {
            char username[Max_INPUT], content[Max_INPUT];
            int n;
            scanf("%s %s %d", username, content, &n);

            if (!addReply(username, content, n)) {
                printf("Failed to add reply\n");
            }
        }
        else if (strcmp(command, "delete_reply") == 0) {
            int n, m;
            scanf("%d %d", &n, &m);

            if (!deleteReply(n, m)) {
                printf("Failed to delete reply\n");
            }
        }
        else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
            break;
        }
    }

    if (plat_form!=NULL) {
        freePlatform(plat_form);
    }

    return 0;
}
