#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
 int vertex;
 struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
 int V;
 int E;
 ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
 int size;
 QueueNode *head;
 QueueNode *tail;
} Queue;

typedef struct _stack
{
 int size;
 StackNode *head;
} Stack;

void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
int matching(Graph g);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
 int Prj, Std, Mtr; //Project, Student and Mentor;
 int maxMatch;
 scanf("%d %d %d", &Std, &Prj, &Mtr);

 int np,nm; //number of projects and number of mentors

 //build graph
 Graph g;
 //Write your code
 Graph g;
g.V = Std + Prj + Mtr + 2; // +2 for source and sink nodes
g.E = 0;
g.list = (ListNode **) malloc((g.V) * sizeof(ListNode *));
for(int i = 0; i < g.V; i++) {
    g.list[i] = NULL; // initialize adjacency list to NULL
}

// Add edges to the adjacency list
int project, mentor;
for(int i = 1; i <= Std; i++) {
    insertAdjVertex(&g.list[0], i); // edge from source to student
    insertAdjVertex(&g.list[i], 0); // edge from student to source
    for(int j = 0; j < Mtr; j++) {
        scanf("%d", &mentor);
        insertAdjVertex(&g.list[i], Std + Prj + mentor); // edge from student to mentor
        insertAdjVertex(&g.list[Std + Prj + mentor], i); // edge from mentor to student
        g.E++;
    }
}

for(int i = 1; i <= Prj; i++) {
    scanf("%d", &np);
    insertAdjVertex(&g.list[Std + i], g.V - 1); // edge from project to sink
    insertAdjVertex(&g.list[g.V - 1], Std + i); // edge from sink to project
    for(int j = 0; j < np; j++) {
        scanf("%d", &project);
        insertAdjVertex(&g.list[Std + i], project); // edge from project to student
        insertAdjVertex(&g.list[project], Std + i); // edge from student to project
        g.E++;
    }
}

 //apply Ford Fulkerson algorithm
 // use DFS or BFS to find a path
 maxMatch = matching(g);
 printf("%d\n", maxMatch);
 return 0;
}

int matching(Graph g)
{

 //Write your code
 return 0;

}

void removeAdjVertex(ListNode** AdjList,int vertex)
{
 ListNode *temp, *preTemp;
 if(*AdjList != NULL)
 {
    if((*AdjList)->vertex ==vertex){//first node
      temp = *AdjList;
      *AdjList = (*AdjList)->next;
      free(temp);
      return;
    }
    preTemp = *AdjList;
    temp = (*AdjList)->next;
    while(temp!=NULL && temp->vertex != vertex)
    {
      preTemp= temp;
      temp = temp->next;
    }
    preTemp->next = temp->next;
    free(temp);
   }
}

void insertAdjVertex(ListNode** AdjList,int vertex)
{
  ListNode *temp;
  if(*AdjList==NULL)
  {
     *AdjList = (ListNode *)malloc(sizeof(ListNode));
     (*AdjList)->vertex = vertex;
     (*AdjList)->next = NULL;
  }
  else{
     temp = (ListNode *)malloc(sizeof(ListNode));
     temp->vertex = vertex;
     temp->next = *AdjList;
     *AdjList = temp;
  }
}

void enqueue(Queue *qPtr, int vertex) {
  QueueNode *newNode;
  newNode = malloc(sizeof(QueueNode));
  if(newNode==NULL) exit(0);

  newNode->vertex = vertex;
  newNode->next = NULL;

  if(isEmptyQueue(*qPtr))
     qPtr->head=newNode;
  else
     qPtr->tail->next = newNode;

     qPtr->tail = newNode;
     qPtr->size++;
}

int dequeue(Queue *qPtr) {
   if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
     return 0;
   }
   else{
     QueueNode *temp = qPtr->head;
     qPtr->head = qPtr->head->next;
     if(qPtr->head == NULL) //Queue is emptied
       Ptr->tail = NULL;

     free(temp);
     qPtr->size--;
     return 1;
}
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
   if(q.size==0) return 1;
   else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
  while(dequeue(qPtr));
}

void printQ(QueueNode *cur){
 if(cur==NULL) printf("Empty");

 while (cur != NULL){
    printf("%d ", cur->vertex);
    cur = cur->next;
  }
 printf("\n");
}

void push(Stack *sPtr, int vertex)
{
  StackNode *newNode;
  newNode= malloc(sizeof(StackNode));
  newNode->vertex = vertex;
  newNode->next = sPtr->head;
  sPtr->head = newNode;
  sPtr->size++;
}

int pop(Stack *sPtr)
{
  if(sPtr==NULL || sPtr->head==NULL){
     return 0;
  }
  else{
     StackNode *temp = sPtr->head;
     sPtr->head = sPtr->head->next;
     free(temp);
     sPtr->size--;
     return 1;
   }
}

int isEmptyStack(Stack s)
{
    if(s.size==0) return 1;
    else return 0;
}

int peek(Stack s){
   return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
   while(pop(sPtr));
}
