void cal(DLL *list, ListStack *liststack) {
    DLL *answer = newDLL(); // 답을 저장하기 위한 노드 생성

    DLL *op1 = newDLL(); // 각 연산을 하기 위한 노드 생성
    DLL *op2 = newDLL();
    char tok; // 연산자를 저장하기 위한 char형 tok생성

    int cnt = 0;

    if(list->head->val == '|') {
        deleteAt(list, 0);
    }

    Node *find_op = list->head; // op 찾는 노드

    while(find_op != NULL) { // 이 조건은 바꿔야 함??
        if(find_op->val != '+' && find_op->val != '-' && find_op->val != '*') { // 피연산자일시
            push(liststack, new_stack_node(find_op->val));
            deleteAt(list, 0);
        }

        else { // 연산자일때 스택에서 op1과 op2를 구분짓고, DLL에서 계산을 한다.

            tok = find_op->val; // 연산자 뽑기
            deleteAt(list, 0);

            if(peek(liststack) == '|') { // 만약 스택의 맨위가 구분자라면
                pop(liststack);
            }

            while(!isEmpty(liststack)) { // 스택이 비어있지 않다면 // 이 조건은 다시 고쳐야함??
                char n = pop(liststack);
                if(n != '|' && cnt == 0) { // 구분자가 아니고 cnt가 0일때 op2에 넣는다
                    append(op2, newnode(n));
                }

                else if(n == '|' && cnt == 0) cnt++; // find_op가 구분자를 가리킨다면 cnt를 하나 증가한다.

                if(n != '|' && cnt == 1) { // 구분자가 아니고 cnt가 1일때 op1에 넣는다
                    append(op1, newnode(n));
                }
            }

            int chk = check_num(op1, op2);

            Node* temp1 = op1->head;
            Node* temp2 = op2->head;

            if(tok != '*')
                add_zero(temp1, temp2, op1, op2); // 자릿수를 맞춘다

            if(tok == '-' && chk == 1) { // -A-B
                temp1 = op1->head;
                temp2 = op2->head;

                add(answer, temp1, temp2);
                append(answer, newnode('-'));

                Node *answer_temp = answer->tail->next; // answer노드의 temp
                while(answer_temp != NULL) {
                    push(liststack, new_stack_node(answer_temp->val));
                    answer_temp = answer_temp->prev;
                }

                push(liststack, new_stack_node('|'));

                if(DLL_empty(list)) {
                    printf("final ans: ");
                    reverse_print(answer);
                    // 동적 할당된 모든 메모리 해제
                    free(answer);
                    free(op1);
                    free(op2);

                    exit(1); // main 함수 종료
                }

                else cal(list, liststack); // 재귀
            }

            if(tok == '+' && chk == 0) { // tok가 +일때 A+B
                temp1 = op1->head;
                temp2 = op2->head;

                add(answer, temp1, temp2);

                Node *answer_temp = answer->tail->next; // answer노드의 temp
                while(answer_temp != NULL) {
                    push(liststack, new_stack_node(answer_temp->val));
                    answer_temp = answer_temp->prev;
                }

                push(liststack, new_stack_node('|'));

                if(DLL_empty(list)) {
                    printf("final ans: ");
                    reverse_print(answer);
                    // 동적 할당된 모든 메모리 해제
                    free(answer);
                    free(op1);
                    free(op2);

                    exit(1); // main 함수 종료
                }

                else cal(list, liststack); // 재귀
            } else if(tok == '-' && chk == 0) { // A-B
                temp1 = op1->head;
                temp2 = op2->head;

                Node *temp_tail1 = op1->tail->next;
                Node *temp_tail2 = op2->tail->next;

                minus(answer, temp1, temp2, temp_tail1, temp_tail2);

                Node *answer_temp = answer->tail->next; // answer노드의 temp
                while(answer_temp != NULL) {
                    push(liststack, new_stack_node(answer_temp->val));
                    answer_temp = answer_temp->prev;
                }

                push(liststack, new_stack_node('|'));

                if(DLL_empty(list)) {
                    printf("final ans: ");
                    reverse_print(answer);
                    // 동적 할당된 모든 메모리 해제
                    free(answer);
                    free(op1);
                    free(op2);

                    exit(1); // main 함수 종료
                }

                else cal(list, liststack); // 재귀
            } else if(tok == '*' && chk == 0) {
                temp1 = op1->head;
                temp2 = op2->head;

                Node *temp_tail1 = op1->tail->next;
                Node *temp_tail2 = op2->tail->next;

                multi(answer, temp1, temp2, temp_tail1, temp_tail2, op1, op2);

                Node *answer_temp = answer->tail->next; // answer노드의 temp
                while(answer_temp != NULL) {
                    push(liststack, new_stack_node(answer_temp->val));
                    answer_temp = answer_temp->prev;
                }

                push(liststack, new_stack_node('|'));

                if(DLL_empty(list)) {
                    printf("final ans: ");
                    reverse_print(answer);
                    // 동적 할당된 모든 메모리 해제
                    free(answer);
                    free(op1);
                    free(op2);

                    exit(1); // main 함수 종료
                }

                else cal(list, liststack); // 재귀
            }
        }
        find_op = find_op->next;
    }
}