#include <bits/stdc++.h>
using namespace std;

const int _vmax = 1e5+3;

class Queue{//implemented using array
    private:
        int arr[_vmax]={};
        int front = 0,rear = 0;
    public:
        void Push(int x){
            arr[rear++]=x;//size taken so that it can accommodate all elements in the worst case. We need not do rear = (rear+1)%_vmax
        }
        void Pop(){
            front++;
        }
        bool Empty(){
            return front==rear;
        }
        int Front(){
            if(!Empty())
                return arr[front];
            else
                return -1;
        }
};

class Node{
    public:
        int data;
        Node *next = NULL;
        Node *prev = NULL; //not required, kept for the sake of completeness
};

class LinkedList{
    public:
        Node *head;
        LinkedList(){
            head = (Node *)malloc(sizeof(Node));//sentinel node
            head->next = head;
            head->prev = head;
        }
        void pushback(int x){
            Node *newnode = (Node *)malloc(sizeof(Node));
            newnode->data = x;
            newnode->next = head;
            newnode->prev = head->prev;
            (newnode->prev)->next = newnode;
            head->prev = newnode;
        }
};

int main(){
    int v,e;
    cin>>v>>e;
    LinkedList adj[v];//adjacency list
    for(int i=0;i<e;i++){
        int a,b;
        cin>>a>>b;
        adj[a].pushback(b);//insert b at the end of adj[a]
        adj[b].pushback(a);
    }
    int valid=1;
    int col[v]; //to store colours

    for(int i=0;i<v;i++)//if col[i]=-1, it implies that the node is not coloured yet
        col[i]=-1;

    Queue q;
    q.Push(0); //arbitrarily colour 0 first.
    col[0]=1;
    while(!q.Empty()){
        int temp = q.Front();
        q.Pop();
            
        Node * ptr=adj[temp].head->next;//traversing over edges of temp
            
        while(ptr!=adj[temp].head){
            int x = ptr->data;
            if(col[x]==-1){
                col[x]=3-col[temp];//endpoints of an edge should have different colour({1:2, 2:1})
                q.Push(x);
            }
            else{ 
                if(col[x]==col[temp]){//if already coloured with an invalid colour, the graph is not bipartite
                    valid=0;
                    break;
                }
            }
            ptr=ptr->next;
        }
    }
    if(valid){ 
        cout<<"YES"<<'\n';
        for(int i=0;i<v;i++)
            cout<<col[i]<<'\n';
    }
    else 
        cout<<"NO"<<'\n';
    return 0;
}