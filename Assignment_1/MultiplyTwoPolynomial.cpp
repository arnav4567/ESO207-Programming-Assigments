#include <bits/stdc++.h>
using namespace std;

const long long M = 1e18;

typedef struct Node{
    long long coeff;
    long long exp;
    Node * next;
    Node * prev;
}node;

void make_sentinel(node * h){
    h->coeff = 0;
    h->exp = M;//since M>max value of exp, we assign this value to indicate the end.
    h->next = h;
    h->prev = h;
}

void insertBefore(long long a,long long b,node * ptr){
    node *newnode = (node *)malloc(sizeof(node));
    newnode->coeff = a;
    newnode->exp = b;
    newnode->next = ptr;
    newnode->prev = ptr->prev;
    (newnode->prev)->next = newnode;
    ptr->prev = newnode;
}

void init_list(node * h,int n){
    for(int i=0;i<n;i++){
        long long exp,coeff;
        cin>>coeff>>exp;
        insertBefore(coeff,exp,h);
    }
}

void printList(node* h){
    node* ptr = h->next;
    while(ptr->exp!=M){
        if(ptr->coeff!=0)
        cout << ptr-> coeff << " " << ptr->exp <<" ";
        ptr = ptr->next;
    }
    cout << endl;
}

node * head1 = (node *)malloc(sizeof(node));//first polynomial
node * head2 = (node *)malloc(sizeof(node));//second polynomial
node * head_res = (node *)malloc(sizeof(node));//their sum

int main(){
    long long n,m;
    cin>>n>>m;

    make_sentinel(head1);
    make_sentinel(head2);

    init_list(head1,n);//taking the input
    init_list(head2,m);

    make_sentinel(head_res);
    node * ptr1 = head1->next;
    node * ptr2 = head2->next;
    node * ptr3 = head_res;
    while(ptr1->exp!=M){
        ptr2 = head2->next;
        ptr3 = head_res->next;
        while(ptr2->exp!=M){
            if(ptr3->exp==M)ptr3=head_res->next;
            long long p = (ptr1->exp)+(ptr2->exp);
            long long c = (ptr1->coeff)*(ptr2->coeff);
            while(!(ptr3->next->exp>p)){
                ptr3=ptr3->next;
            }
            if(ptr3->exp==p){
                ptr3->coeff+=c;
            }else insertBefore(c,p,ptr3->next);
            ptr2=ptr2->next;
        }
        ptr1=ptr1->next;
    }
    printList(head_res);
    return 0;
}