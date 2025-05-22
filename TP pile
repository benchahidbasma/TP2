#include <stdio.h>
#include <stdlib.h>

typedef struct pile {
    int val;
    struct noeud * next;
}pile;

void push(pile**top,int v){
    pile* newE=(pile*)malloc(sizeof(pile));
    if(newE==NULL){
        printf("echec d allocation.\n");
        return;
    }
    newE->val=v;
    newE->next=*top;
    *top=newE;
    printf("element %d empile .\n",v);
}

void pop (pile**top){
   if(top==NULL){
    printf("la pile est vide.\n");
    return;
   }
   pile *tmp=*top;
   *top=(*top)->next;
   printf("element %d depile.\n",tmp->val);
   free(tmp);
   }

void peek(pile**top){
    if(*top==NULL){
        printf("la pile est vide.\n");
    }
    else{
        printf("\nle sommet de la pile : %d\n",(*top)->val);
    }
}

void display(pile**top){
    if(*top==NULL){
        pile*tmp=top;
        printf("elements de pile :");
        while(tmp!=NULL){
            printf("%d",tmp->val);
            tmp =tmp->next;
        }
        printf("\n");
    }
}


int main()
{
   pile *top=NULL;
   push(&top,10);
   push(&top,20);
   push(&top,30);
   display(&top);
   peek(&top);

   pop(&top);
   display(&top);
   peek(&top);


    return 0;
}
