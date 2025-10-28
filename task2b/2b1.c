#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct Node{
    struct Node*left;
    struct Node*right;
}Node;

typedef struct QueueNode{
    Node*node;
    struct QueueNode*next;
}QueueNode;

typedef struct{
    QueueNode*front;
    QueueNode*rear;
}Queue;

Queue*createQueue(){
    Queue*q=(Queue*)malloc(sizeof(Queue));//allocating memory
    q->front=q->rear=NULL;
    return q;
}

//code for checking whether queue is empty or not
int isempty(Queue*q){
    return q->front==NULL;
}

//code for pusing the elements into queue
void enqueue(Queue*q,Node*node){
    QueueNode*temp=(QueueNode*)malloc(sizeof(QueueNode));
    temp->node=node;
    temp->next=NULL;
    if(q->rear==NULL){
        q->front=q->rear=temp;
    }
    else{
        q->rear->next=temp;
        q->rear=temp;
    }
}

//code for poping elements from queue
Node*dequeue(Queue*q){
    if(q->front==NULL)return NULL;
    QueueNode*temp=q->front;
    Node*node=temp->node;
    q->front=q->front->next;
    if(q->front==NULL)
        q->rear=NULL;
    free(temp);//for freeing the temp
    return node;
}

//code for creating the node which will points to NULL(both left and right)
Node*newNode(){
    Node*node=(Node*)malloc(sizeof(Node));//aloocating the memory
    node->left=node->right=NULL;
    return node;
}

//code for building the tree using level order traversal
Node*createtree(int* level,int n){
    if(n==0||level[0]==0)return NULL;
    Queue*q=createQueue();
    Node*root=newNode();
    enqueue(q,root);
    int i=1;
    while(!isempty(q)&&i<n){
        Node*cur=dequeue(q);
        if(i<n && level[i]==1){//for left child
            cur->left=newNode();
            enqueue(q,cur->left);
        }
        i++;
        if(i<n&&level[i]==1){//for right child
            cur->right=newNode();
            enqueue(q,cur->right);
        }
        i++;
    }
    free(q);
    return root;
}

//codee ofr dfs traversal
int dfs(Node*root,int*ans){
    if(root==NULL)return 2;//means no phone is required(covered)
    int left=dfs(root->left,ans);//for traversing to left subtree
    int right=dfs(root->right,ans);//for right subtree
    if(left==0||right==0){
        (*ans)++;
        return 1;//means it only has a phone
    }
    if(left==1||right==1)
        return 2;//means this is covered by childs phone
    return 0;//means this needs a phone
}

int minPhones(Node*root){
    int ans=0;//for counting the number of phones required
    if(dfs(root,&ans)==0)
        ans++;
    return ans;
}

int main(){
    int n;
    scanf("%d",&n);
    int*level=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
        scanf("%d",&level[i]);
    Node*root=createtree(level,n);
    int result=minPhones(root);
    printf("%d\n",result);
    free(level);//removing the space allocated for level array.
    return 0;
}
