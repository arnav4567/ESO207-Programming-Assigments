// Final Submission- Adding two polynomials
//     Arnav Gupta: 200186
//     Kushagra Sharma: 200539

#include <bits/stdc++.h>
using namespace std;

const int M = 1e9+7;

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

void insert(long long a,long long b,node * head){
    node *newnode = (node *)malloc(sizeof(node));
    newnode->coeff = a;
    newnode->exp = b;
    newnode->next = head;
    newnode->prev = head->prev;
    (newnode->prev)->next = newnode;
    head->prev = newnode;
}

void init_list(node * h,int n){
    for(int i=0;i<n;i++){
        long long exp,coeff;
        cin>>coeff>>exp;
        insert(coeff,exp,h);
    }
}

void printList(node* h){
    node* ptr = h->next;
    while(ptr->exp!=M){
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
    while(!(ptr1->exp==M && ptr2->exp==M)){
        if(ptr1->exp>ptr2->exp){
            insert(ptr2->coeff,ptr2->exp,head_res);
            ptr2 = ptr2->next;
        }
        else if(ptr1->exp<ptr2->exp){
            insert(ptr1->coeff,ptr1->exp,head_res);
            ptr1 = ptr1->next;
        }
        else{
            if(ptr1->coeff+ptr2->coeff!=0)
                insert(ptr1->coeff+ ptr2->coeff,ptr1->exp,head_res);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    printList(head_res);
    return 0;
}