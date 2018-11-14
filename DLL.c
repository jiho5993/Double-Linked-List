#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} DLL;

Node *newnode(int n) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->val = n;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

DLL *newDLL() {
    DLL *temp = (DLL *)malloc(sizeof(DLL));
    temp->head = NULL;
    temp->size = 0;
    return temp;
}

void append(DLL *list, Node *newnode) {
    if(!list || !newnode) return;

    if(list->size == 0) {
        list->head = newnode;
    } else {
        int cnt = list->size-1;
        Node *tail = list->head;
        while (cnt) {
            tail = tail->next;
            cnt--;
        }
        tail->next = newnode;
        newnode->prev = tail;
    }
    (list->size)++;
}
void insertAt(DLL *list, int index, Node *newnode) {
    int a = 0;
    int cnt = list->size;
    Node *temp = list->head;

    if(index < 0 || index > list->size) {
        printf("INSERT ERROR: Out of Bound.\n");
    }

    else if(index == 0) {
        list->head->prev = newnode;
        newnode->next = list->head;
        list->head = newnode;
        list->size++;
    }

    else if(index == cnt) {
        while(cnt-1) {
            temp = temp->next;
            cnt--;
        }
        temp->next = newnode;
        newnode->prev = temp;
        list->size++;
    }

    else {
        while(a <= cnt) {
            if(a == index) {
                newnode->prev = temp->prev;
                newnode->next = temp;
                temp->prev->next = newnode;
                temp->prev = newnode;
                list->size++;
                break;
            }
            temp = temp->next;
            a++;
        }
    }
}
void deleteAt(DLL *list, int index) {
    int idx = 0;
    int cnt = list->size;
    Node *temp = list->head;

    if(index < 0 || index > cnt-1) {
        printf("DELETE ERROR: Out of Bound.\n");
    }

    else if(index == 0) {
        list->head = temp->next;
        list->head->prev = NULL;
        (list->size)--;
        free(temp);
    }

    else if(index == cnt-1) {
        while (cnt-1) {
            temp = temp->next;
            cnt--;
        }
        temp->prev->next = NULL;
        (list->size)--;
        free(temp);
    }

    else {
        while(idx <= cnt-1) {
            if(idx == index) {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                (list->size)--;
                free(temp);
                break;
            }
            temp = temp->next;
            idx++;
        }
    }
}
void print(DLL *list) {
    Node *n = list->head;
    while(n != NULL) {
        printf("[%d] ", n->val);
        n = n->next;
    }
    printf("\n");
}
void print_reverse(DLL *list) {
    Node *tail = list->head;
    int cnt = list->size;
    while (cnt-1) {
        tail = tail->next;
        cnt--;
    }
    while(tail != NULL) {
        printf("[%d] ", tail->val);
        tail = tail->prev;
    }
    printf("\n");
}

int main() {
    DLL *list = newDLL();
    int i;
    for(i=1; i<6; i++) {
        append(list, newnode(i));
    }
    print(list);

    deleteAt(list, -1);
    deleteAt(list, 5);
    deleteAt(list, 0);
    print(list);
    deleteAt(list, 2);
    print(list);
    deleteAt(list, 2);
    print(list);

    insertAt(list, -1, newnode(6));
    insertAt(list, 3, newnode(6));
    insertAt(list, 0, newnode(7));
    print(list);
    insertAt(list, 1, newnode(8));
    print(list);
    insertAt(list, 4, newnode(9));
    print(list);
    print_reverse(list);

    return 0;
}