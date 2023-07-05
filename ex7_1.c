#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_st{
    char fullname[30];
    struct node_st *next;
} node_t;

int add_node(node_t **head, char *str);

int main(void){
    node_t *head = NULL;
    char name[30];
    int flag = 2;

    for(int i=0;i<3;i++){
        printf("Input : ");
        scanf("%s", name);
        flag = add_node(&head, name);
        if(flag!=0){
            printf("Error!");
        }
    }

    for(node_t *node=head;node!=NULL;node=node->next){
        printf("%s\n", node->fullname);
    }

    while(head != NULL){
        node_t *node = head->next;
        free(head);
        head = node; 
    }

    return 0;
}

int add_node(node_t **head, char *str){
    node_t *newnode = (node_t *)malloc(sizeof(node_t));
    strcpy((*newnode).fullname, str);
    (*newnode).next = *head;
    if(newnode == NULL){
        return 1;
    }
    *head = newnode;
    return 0;
}