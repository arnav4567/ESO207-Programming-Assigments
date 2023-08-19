// Final Submission- ESO207 Programming Assignment 2.1
// Merging two 2-3 Trees
//     Arnav Gupta: 200186
//     Kushagra Sharma: 200539
#include <bits/stdc++.h>
using namespace std;

typedef struct twothreeNode{
    long long z;//min value in the right subtree
    long long y;//min value in the middle subtree
    
    twothreeNode * left;
    twothreeNode * middle;
    twothreeNode * right;
    twothreeNode * parent;
}node;

typedef struct returnfrominsert{
    node * n1 = NULL;
    node * n2 = NULL;
    long long m = 0;
}ret_type;

node* MakeSingleton(long long data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->z=0;
    newnode->y=data;
    
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->middle=NULL;
    newnode->parent=NULL;
    return newnode;
}

int getHeight(node * T){
    int height=0;
    node* ptr=T;
    while(ptr->left!=NULL){
        height++;
        ptr=ptr->left;
    }
    return height;
}

node* makeTwoNode(long long v, node*l,node*mid){
    node* n1 = (node*)malloc(sizeof(node));
    n1->y=v;
    n1->z=0;
    n1->left=l;
    n1->middle=mid;
    n1->right=NULL;
    n1->parent=NULL;
    l->parent=n1;
    mid->parent=n1;
    return n1;
}
//U is smaller in value.
node* makeRoot(node*U,node*T,long long rightMin){
    node* newRoot = MakeSingleton(rightMin);
    newRoot->left=U;
    newRoot->right=NULL;
    newRoot->parent=NULL;
    newRoot->middle=T;
    newRoot->z=0;
    newRoot->left->parent=newRoot;
    newRoot->middle->parent=newRoot;
    return newRoot;
}
// T has higher value and will be added to the right. // UtoT means adding U to T, 1 when it is true.
ret_type * InsertNode(node * U, node * T, long long Tmin, long long Umin, int uToT){
    ret_type *args = (ret_type*)malloc(sizeof(ret_type));
    if(uToT==0)//U is threeNode and we have to add T to its right.
    {
        if(U->right!=NULL){
            node* n = makeTwoNode(Tmin,U->right,T);
            long long val = U->z;
            U->z=0;
            U->right=NULL;
            if(U->parent==NULL)//root node
            {
                args->n1 = U;
                args->n2 = n;
                args->m = val;
                return args;
            }else{
                InsertNode(U->parent,n,val,Umin,0);
            }
        }else{
            U->right = T;
            T->parent=U;
            U->z = Tmin;
            args->n1=U;
            args->n2=NULL;
            args->m=0;
            return args;
        }
    }else//add U to the leftmost of T
    {
        if(T->right!=NULL){
            node* n = makeTwoNode(Tmin,U,T->left);
            T->middle=T->left;
            T->middle=T->right;
            T->right=NULL;
            long long val = T->y;
            T->y=T->z;
            T->z=0;//remove right subtree of t
            if(T->parent==NULL)//root node
            {
                args->n1=n;
                args->n2=T;
                args->m = val;
                return args;
            }else{
                InsertNode(n,T->parent,val,Umin,1);
            }
        }else{
            T->right=T->middle;
            T->z=T->y;
            T->y=Tmin;
            T->middle=T->left;
            T->left=U;
            U->parent=T;
            args->n1=T;
            args->n2=NULL;
            args->m=0;
            return args;
        }
    }

}

// U is tree with lower values
node* Merge(node* U,node* T){
    //calculating the heights of U and T, if we need to find which node to add the other node to.
    int h1=getHeight(U);
    int h2=getHeight(T);//U and T will basically be the root nodes.
    //Getting the minimum value in tree T.
    node* ptr = T;
    while(ptr->left!=NULL)ptr=ptr->left;
    long long valueT = ptr->y;
    //Getting the minimum value in tree U.
    ptr = U;
    while(ptr->left!=NULL)ptr=ptr->left;
    long long valueU=ptr->y;
    if(h1==h2){
        //making a new node and adding root nodes U and T as its children
        node* newRoot = makeRoot(U,T,valueT);
        return newRoot;
    }else if(h1>h2){
        //Going right by h1-h2-1 and adding T as its child
        ptr = U;
        int i=0;
        while(i++<h1-h2-1){if (ptr->right!=NULL)ptr=ptr->right;else ptr=ptr->middle;}
        ret_type *ret = (ret_type*)malloc(sizeof(ret_type));
        ret = InsertNode(ptr,T,valueT,valueU,0);
        if(ret->n2==NULL){
            return U;
        }else{
            node* newRoot = makeRoot(ret->n1,ret->n2,ret->m);
            return newRoot;
        }
    }else{
        //Going left by h2-h1-1 and adding U as its child
        ptr=T;
        int i=0;
        while(i++<h2-h1-1)ptr=ptr->left;
        ret_type *ret = (ret_type*)malloc(sizeof(ret_type));
        ret = InsertNode(U,ptr,valueT,valueU,1);
        if(ret->n2==NULL){
            return T;
        }else{
            node* newRoot = makeRoot(ret->n1,ret->n2,ret->m);
            return newRoot;
        }
    }
}

void Extract(node* T){
    queue<node*> q;
    q.push(T);
    while(!q.empty()){
        node* ptr = q.front();
        // cout << "ptr value " <<ptr->y <<" " <<ptr->z<<endl;
        q.pop();
        if(ptr->left!=NULL)q.push(ptr->left);
        if(ptr->middle!=NULL)q.push(ptr->middle);
        if(ptr->right!=NULL)q.push(ptr->right);
        if(ptr->left==NULL)cout << ptr->y <<" ";//prints data if it is a leaf node.
    }
    cout << endl;
}

void Test(){
    node* T = MakeSingleton(1);
    for(int i=2;i<=500;i++){
        T= Merge(T,MakeSingleton(i));
    }
    node* U = MakeSingleton(777);
    for(int i=778;i<=1000;i++){
        U= Merge(U,MakeSingleton(i));
    }
    //We have to make the tree U with lower values.
    if(U->y>T->y){
        node* exchange = T;
        T=U;
        U=exchange;
    }
    node* V=Merge(U,T);
    Extract(V);
}

int main(){
    Test();
    return 0;
}

