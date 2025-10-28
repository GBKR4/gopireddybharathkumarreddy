#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"platform.h"
#include"post.h"
#include"comment.h"
#include"reply.h"

post* currpost(post* lastviewedpost){
    if(lastviewedpost==NULL){
        printf("nocurrentpost\n");
        return NULL;
    }
    printf("currentpostby%s:%s\n",lastviewedpost->username,lastviewedpost->caption);
    return lastviewedpost;
}

post* nextpost(post** lastviewedpost){
    if(lastviewedpost==NULL||*lastviewedpost==NULL){
        printf("nopostexists\n");
        return NULL;
    }
    if((*lastviewedpost)->next==NULL){
        printf("nextpostdoesnotexist\n");
        return *lastviewedpost;
    }
    *lastviewedpost=(*lastviewedpost)->next;
    printf("nextpostby%s:%s\n",(*lastviewedpost)->username,(*lastviewedpost)->caption);
    return *lastviewedpost;
}

post* previouspost(post** lastviewedpost){
    if(lastviewedpost==NULL||*lastviewedpost==NULL){
        printf("nopostexists\n");
        return NULL;
    }
    if((*lastviewedpost)->prev==NULL){
        printf("previouspostdoesnotexist\n");
        return *lastviewedpost;
    }
    *lastviewedpost=(*lastviewedpost)->prev;
    printf("previouspostby%s:%s\n",(*lastviewedpost)->username,(*lastviewedpost)->caption);
    return *lastviewedpost;
}

bool addpost(post** head,char* username,char* caption){
    if(username==NULL||caption==NULL)return false;
    post* newpost=createpost(username,caption);
    if(newpost==NULL)return false;
    if(*head==NULL){
        *head=newpost;
        return true;
    }
    post* temp=*head;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=newpost;
    newpost->prev=temp;
    return true;
}

bool addcomment(post* head,int postindex,char* username,char* content){
    if(head==NULL||username==NULL||content==NULL)return false;
    post* temp=head;
    for(int i=1;temp!=NULL&&i<postindex;i++)
        temp=temp->next;
    if(temp==NULL)return false;
    comment* newcomment=createcomment(username,content);
    if(newcomment==NULL)return false;
    if(temp->comments==NULL)
        temp->comments=newcomment;
    else{
        comment* c=temp->comments;
        while(c->next!=NULL)
            c=c->next;
        c->next=newcomment;
        newcomment->prev=c;
    }
    return true;
}

bool addreply(post* head,int postindex,int commentindex,char* username,char* content){
    if(head==NULL||username==NULL||content==NULL)return false;
    post* p=head;
    for(int i=1;p!=NULL&&i<postindex;i++)
        p=p->next;
    if(p==NULL)return false;
    comment* c=p->comments;
    for(int j=1;c!=NULL&&j<commentindex;j++)
        c=c->next;
    if(c==NULL)return false;
    reply* newreply=createreply(username,content);
    if(newreply==NULL)return false;
    if(c->replies==NULL)
        c->replies=newreply;
    else{
        reply* r=c->replies;
        while(r->next!=NULL)
            r=r->next;
        r->next=newreply;
        newreply->prev=r;
    }
    return true;
}

bool deletecomment(post* head,int postindex,int commentindex){
    if(head==NULL)return false;
    post* p=head;
    for(int i=1;p!=NULL&&i<postindex;i++)
        p=p->next;
    if(p==NULL)return false;
    comment* c=p->comments;
    for(int j=1;c!=NULL&&j<commentindex;j++)
        c=c->next;
    if(c==NULL)return false;
    deletereplylist(c->replies);
    if(c->prev)
        c->prev->next=c->next;
    else
        p->comments=c->next;
    if(c->next)
        c->next->prev=c->prev;
    free(c);
    return true;
}

bool deletereply(post* head,int postindex,int commentindex,int replyindex){
    if(head==NULL)return false;
    post* p=head;
    for(int i=1;p!=NULL&&i<postindex;i++)
        p=p->next;
    if(p==NULL)return false;
    comment* c=p->comments;
    for(int j=1;c!=NULL&&j<commentindex;j++)
        c=c->next;
    if(c==NULL)return false;
    reply* r=c->replies;
    for(int k=1;r!=NULL&&k<replyindex;k++)
        r=r->next;
    if(r==NULL)return false;
    if(r->prev)
        r->prev->next=r->next;
    else
        c->replies=r->next;
    if(r->next)
        r->next->prev=r->prev;
    free(r);
    return true;
}

bool deletepost(post** head,int postindex){
    if(*head==NULL)return false;
    post* p=*head;
    for(int i=1;p!=NULL&&i<postindex;i++)
        p=p->next;
    if(p==NULL)return false;
    freecommentlist(p->comments);
    if(p->prev)
        p->prev->next=p->next;
    else
        *head=p->next;
    if(p->next)
        p->next->prev=p->prev;
    free(p);
    return true;
}

void displayplatform(post* head){
    if(head==NULL){
        printf("nopoststodisplay\n");
        return;
    }
    post* p=head;
    int postnum=1;
    while(p!=NULL){
        printf("post#%dby%s\n",postnum,p->username);
        printf("caption:%s\n",p->caption);
        comment* c=p->comments;
        int commentnum=1;
        while(c!=NULL){
            printf("comment#%dby%s:%s\n",commentnum,c->username,c->content);
            reply* r=c->replies;
            int replynum=1;
            while(r!=NULL){
                printf("reply#%dby%s:%s\n",replynum,r->username,r->content);
                r=r->next;
                replynum++;
            }
            c=c->next;
            commentnum++;
        }
        p=p->next;
        postnum++;
    }
}

void viewpost(post *head, int postindex) {
    if (head == NULL) {
        printf("nopostsavailable\n");
        return;
    }
    post *temp=head;
    for (int i=1;temp!=NULL && i<postindex;i++)
        temp=temp->next;
    if (temp==NULL) {
        printf("postnotfound\n");
        return;
    }
    printf("viewpostby%s %s\n", temp->username, temp->caption);
    comment *c = temp->comments;
    int commentnum = 1;
    while (c != NULL) {
        printf("  comment#%dby%s %s\n", commentnum, c->username, c->content);
        reply *r=c->replies;
        int replynum = 1;
        while (r != NULL) {
            printf("    reply#%dby%s %s\n", replynum, r->username, r->content);
            r = r->next;
            replynum++;
        }
        c = c->next;
        commentnum++;
    }
}


void viewcomments(post* head,int postindex){
    if(head==NULL){
        printf("nopostsavailable\n");
        return;
    }
    post* temp=head;
    for(int i=1;temp!=NULL&&i<postindex;i++)
        temp=temp->next;
    if(temp==NULL){
        printf("postnotfound\n");
        return;
    }
    printf("commentsforpost#%dby%s:\n",postindex,temp->username);
    comment* c=temp->comments;
    if(c==NULL){
        printf("nocommentsforthispost\n");
        return;
    }
    int commentnum=1;
    while(c!=NULL){
        printf("comment#%dby%s:%s\n",commentnum,c->username,c->content);
        reply* r=c->replies;
        int replynum=1;
        while(r!=NULL){
            printf("reply#%dby%s:%s\n",replynum,r->username,r->content);
            r=r->next;
            replynum++;
        }
        c=c->next;
        commentnum++;
    }
}

void deletereplylist(reply* head){
    while(head!=NULL){
        reply* temp=head;
        head=head->next;
        free(temp);
    }
}

void freecommentlist(comment* head){
    while(head!=NULL){
        comment* temp=head;
        deletereplylist(head->replies);
        head=head->next;
        free(temp);
    }
}

void freepost(post* head){
    while(head!=NULL){
        post* temp=head;
        freecommentlist(head->comments);
        head=head->next;
        free(temp);
    }
}
