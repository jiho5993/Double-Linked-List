void push(ListStack *list, Stack_Node *newnode) { // 스택에 집어넣음
//append함수의 == 0에서 가져옴
    newnode->next = list->head;
    list->head->prev = newnode;
    list->head = newnode;
    list->top++;
}

char pop(ListStack *list) {//스택에서 꺼냄

    struct Stack_Node* temp = list->head;

    if (list->top == -1) {
        printf("Stack is sold out!!\n");
        return -1;
    }
    else {
        temp->next->prev = NULL;
        list->head = temp->next;
        list->top--;

        return temp->data;
    }
}

char peek(ListStack *list) {//스택에서 제일 꼭대기 층의 연산자를 꺼내지않고 무엇인지 확인만 한다.
    struct Stack_Node* temp = list->head;
    return temp->data;
}

int isEmpty(ListStack *list) {//스택이 비었다면 0이아닌 수를, 비었다면 0을 반환
    return list->top == -1;
}

int precedence(char operator1) {//연산자들의 우선순위를 반환 (,)는 가장 우선순위가 낮고, +,-가 그다음으로 높고 *,/가 제일 높다. 
    switch (operator1) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

void init_stack(ListStack* liststack) {//append합수의 변용으로 stack의 주소값을 배정

//    liststack->top = -1;
    Stack_Node* newNode = new_stack_node('a');;
    liststack->head = newNode;
    liststack->tail = newNode;
}

void stack_print(ListStack *listStack) {
    Stack_Node *temp = listStack->tail;
    while(temp != NULL) {
        printf("%c", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}