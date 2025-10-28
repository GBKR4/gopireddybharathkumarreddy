#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"platform.h"

int main(){
    post *platform=NULL;
    char command[50],username[50],caption[200],content[200];
    int postindex,commentindex,replyindex;

    while(scanf("%49s",command)!=EOF){

        if(strcmp(command,"create_platform")==0){
            platform=NULL;
        }

        else if(strcmp(command,"add_post")==0){
            scanf("%49s",username);
            getchar();
            fgets(caption,sizeof(caption),stdin);
            caption[strcspn(caption,"\n")]=0;
            addpost(&platform,username,caption);
        }

        else if(strcmp(command,"add_comment")==0){
            scanf("%d %49s",&postindex,username);
            getchar();
            fgets(content,sizeof(content),stdin);
            content[strcspn(content,"\n")]=0;
            addcomment(platform,postindex,username,content);
        }

        else if(strcmp(command,"add_reply")==0){
            scanf("%d %d %49s",&postindex,&commentindex,username);
            getchar();
            fgets(content,sizeof(content),stdin);
            content[strcspn(content,"\n")]=0;
            addreply(platform,postindex,commentindex,username,content);
        }

        else if(strcmp(command,"delete_comment")==0){
            scanf("%d %d",&postindex,&commentindex);
            deletecomment(platform,postindex,commentindex);
        }

        else if(strcmp(command,"delete_reply")==0){
            scanf("%d %d %d",&postindex,&commentindex,&replyindex);
            deletereply(platform,postindex,commentindex,replyindex);
        }

        else if(strcmp(command,"view_platform")==0){
            displayplatform(platform);
        }

        else if(strcmp(command,"current_post")==0){
            currpost(platform);
        }

        else if(strcmp(command,"next_post")==0){
            nextpost(&platform);
        }

        else if(strcmp(command,"previous_post")==0){
            previouspost(&platform);
        }

        else if(strcmp(command,"view_comments")==0){
            scanf("%d",&postindex);
            viewcomments(platform,postindex);
        }

        else if(strcmp(command,"view_post")==0){
            scanf("%d",&postindex);
            viewpost(platform,postindex);
        }

        else if(strcmp(command,"delete_post")==0){
            scanf("%d",&postindex);
            deletepost(&platform,postindex);
        }

        else if(strcmp(command,"exit")==0){
            break;
        }

        else{
            // ignore invalid commands
        }
    }

    return 0;
}
