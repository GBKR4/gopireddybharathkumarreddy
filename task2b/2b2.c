#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 300000 //using it to replace MAXN with 300000
int n;
int level[MAXN];//global array for gettinh level_order
int l,r;
int phone_count = 0;

//code for generating primes
bool isprime(int x) {
    if (x < 2) return false;
    for (int i=2;i*i<=x;i++)
        if (x %i==0) return false;
    return true;
}

void creating_primes(int m,int primes[]) {
    int count=0,num=2;
    while (count<m) {
        if (isprime(num)) primes[count++] = num;
        num++;
    }
}

//code for dfs (for getting number of phones)
int dfs(int i) {
    if (i>=n || level[i]==0) return 2;
    int left=dfs(2*i+1);//left child's index
    int right=dfs(2*i+2);//right child's index
    if (left==0 || right==0) {
        phone_count++;
        return 1; //means this itself has a node
    }
    if (left==1 || right==1) {
        return 2; //means it is covered by child
    }
    return 0; //means it needs to be covered
}

int main() {
    scanf("%d",&n);
    for (int i=0;i<n;i++)
        scanf("%d",&level[i]);
    scanf("%d %d",&l,&r);
    phone_count = 0;
    if (dfs(0)==0) phone_count++; //means to cover the root
    printf("%d\n", phone_count+1);

    //code for doing xor
    int primes[phone_count];
    creating_primes(phone_count,primes);
    long long count=0;
    for (int i=0;i<phone_count;i++) {
        for (int j=i+1;j<phone_count;j++) {
            int x=primes[i]^primes[j];
            if (x<l || x>r) //checking whether it with in bounds or not
                count++;
        }
    }
    printf("%lld\n",count+1);
    return 0;
}
