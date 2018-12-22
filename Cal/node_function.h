void append(DLL *list, Node *newnode) {
    struct Node* temp = list->head;
    struct Node* newNode = newnode;
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;//---------------------
        list->size++;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    list->size++;
    temp->next = newNode;
    list->tail = temp;//------------------
    newNode->prev = temp;
}

void insertAt(DLL *list, int index, Node *newnode) {

    struct Node* temp = list->head;

    if (index < 0 || index > list->size) {
        printf("INSERT ERROR: Out of Bound\n");
    }
    else if (index == 0) {
        newnode->next = list->head;
        list->head->prev = newnode;
        list->head = newnode;
        list->size++;
    }
    else if (index == list->size) {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        newnode->prev = temp;
        newnode->next = NULL;
        temp->next = newnode;
        list->size++;
    }
    else {
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        list->tail = temp;//----------------------------
        newnode->prev = temp;
        newnode->next = temp->next;
        temp->next->prev = newnode;
        temp->next = newnode;
        list->size++;
    }
}

void deleteAt(DLL *list, int index) {

    struct Node* temp = list->head;

    if (index < 0 || index >= list->size) {
        printf("");
//        printf("DELETE ERROR: Out of Bound\n");
    }
    else if (index == 0) {
        temp->next->prev = NULL;
        list->head = temp->next;
        list->size--;
    }
    else if (index + 1 == list->size) {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->prev->next = NULL;
        free(temp);

        list->size--;
    }

    else {
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);

        list->size--;
    }
}

void print(DLL *list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%c", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void reverse_print(DLL *list) {
    Node *temp = list->tail->next;
    while(temp != NULL) {
        printf("%c", temp->val);
        temp = temp->prev;
    }
    printf("\n");
}

int DLL_empty(DLL *list) {
    return list->size == 0;
}

void erasewhitespace(DLL *list) {//공백 문자 제거하는 함수
    int i = 0;

    struct Node* temp = list->head;
    while (temp == NULL) {
        if (isspace(temp->val)) {
            deleteAt(list, i);
            i--; //한 노드가 지워질 때마다 size가 줄어듬으로 index에서 1을 줄여준다.
            list->size--;//list에서 size도 줄어듬
        }
        temp = temp->next;
        i++;
    }
    list->size--;
}

void add_zero(Node *temp1, Node *temp2, DLL *op1, DLL *op2) { // 자릿수 맞추기
    int cnt1 = 0, cnt2 = 0; // 소수점이 있으면 cnt증가
    int size1 = 0, size2 = 0;

    while(temp1 != NULL) { // op1
        if(temp1->val == '.')
            cnt1++;
        temp1 = temp1->next;
    }

    while(temp2 != NULL) { // op2
        if(temp2->val == '.')
            cnt2++;
        temp2 = temp2->next;
    }

    temp1 = op1->head;
    temp2 = op2->head;
    //-----------------------------------------
    //cnt = 1이면 실수, 0이면 정수

    //--------------------------------------
    //소수일때 자릿수 맞추기
    if(cnt1 == 1 && cnt2 == 1) {
        while(temp1->val != '.'){
            size1++;
            temp1 = temp1->next;
        }
        while(temp2->val != '.'){
            size2++;
            temp2 = temp2->next;
        }
        if (size1<size2){
            for(int i=0; i<size2-size1; i++)
                insertAt(op1, 0, newnode('0'));
        }
        else {
            for(int i=0; i<size1-size2; i++)
                insertAt(op2, 0, newnode('0'));
        }
    }

    if(cnt1 == 1 && cnt2 == 0) { // op1만 실수일때
        printf("success!!\n");
        while(temp1->val != '.') {
            size1++;
            temp1 = temp1->next;
        }
        for(int i=0; i<size1; i++)
            insertAt(op2, 0, newnode('0'));
        insertAt(op2, size1, newnode('.'));
    }

    if(cnt1 == 0 && cnt2 == 1) { // op2만 실수일때
        while(temp2->val != '.') {
            size2++;
            temp2 = temp2->next;
        }
        for(int i=0; i<size2; i++)
            insertAt(op1, 0, newnode('0'));
        insertAt(op1, size2, newnode('.'));
    }

    //---------------------------------------
    //정수일때 자릿수 맞추기
    if(cnt1 == 0 && cnt2 == 1) {
        size1 = 1;
        size2 = 0;
    } else if(cnt1 == 1 && cnt2 == 0) {
        size1 = 0;
        size2 = 1;
    } else if(cnt1 == 1 && cnt2 == 1) {
        size1 = 0;
        size2 = 0;
    }

    while (temp1 != NULL) {
        size1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        size2++;
        temp2 = temp2->next;
    }
    //----------------------------------------

    if(size1>size2) {
        for(int i=0; i<size1-size2; i++)
            append(op2, newnode('0'));
    }

    else if(size1<size2) {
        for(int i=0; i<size2-size1; i++)
            append(op1, newnode('0'));
    }
}

void add(DLL *answer, Node *temp1, Node *temp2) {
    int ans;

    while(temp1 != NULL) {
        if(temp1->val =='.' && temp2->val == '.') { // 둘다 소수점을 가지고 있을때
            append(answer, newnode('.'));
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else { // 숫자일때
            ans = (temp1->val - '0') + (temp2->val - '0');
            if (ans >= 10) {
                if (temp1->next != NULL) {
                    append(answer, newnode(ans % 10 + '0'));
                    if(temp1->next->val == '.')
                        temp1->next->next->val++;
                    else
                        temp1->next->val++;
                } else {
                    append(answer, newnode(ans % 10 + '0'));
                    append(answer, newnode('1'));
                }
            } else append(answer, newnode(ans + '0'));

            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
}

void minus(DLL *answer, Node *temp1, Node *temp2, Node *temp_tail1, Node *temp_tail2) {
    int ans;
    int cnt1, cnt2;

    while(temp_tail1 != NULL && temp_tail2 != NULL) { // op1과 op2 크기 비교
        if(temp_tail1->val > temp_tail2->val) {
            cnt1 = 1;
            cnt2 = 0;
            break;
        } else if(temp_tail1->val < temp_tail2->val) {
            cnt1 = 0;
            cnt2 = 1;
            break;
        }
        cnt1 = 0;
        cnt2 = 0;
        temp_tail1 = temp_tail1->prev;
        temp_tail2 = temp_tail2->prev;
    }

    if(cnt1 < cnt2) {
        while(temp1 != NULL) {

            if(temp1->val == '.' && temp2->val == '.') {
                append(answer, newnode('.'));
                temp1 = temp1->next;
                temp2 = temp2->next;
            } else {
                ans = (temp2->val-'0') - (temp1->val-'0');
                if(ans < 0) {
                    if(temp2->next->val == '.')
                        temp2->next->next->val--;
                    else
                        temp2->next->val--;
                    append(answer, newnode((ans+10)+'0'));
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                } else {
                    append(answer, newnode(ans+'0'));
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
            }
        }
        append(answer, newnode('-'));
    } else {
        while(temp1 != NULL) {

            if(temp1->val == '.' && temp2->val == '.') {
                append(answer, newnode('.'));
                temp1 = temp1->next;
                temp2 = temp2->next;
            } else {
                ans = (temp1->val - '0') - (temp2->val - '0');
                printf("\nans: %d\n\n", ans);
                if (ans < 0){
                    if(temp1->next->val == '.')
                        temp1->next->next->val--;
                    else
                        temp1->next->val--;
                    append(answer, newnode(ans + 10 + '0'));
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
                else{
                    append(answer, newnode(ans+ '0'));
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
            }
        }
    }
}

int check_num(DLL *op1, DLL *op2) {
    int check = 0;
    if(!DLL_empty(op1)) {
        if (op1->tail->next->val == '-') {
            deleteAt(op1, op1->size-1);
            check++;
        }
    }
    if(!DLL_empty(op2)) {
        if (op2->tail->next->val == '-') {
            deleteAt(op2, op2->size-1);
            check++;
        }
    }

    return check;
}

void multi(DLL *answer, Node *temp1, Node *temp2, Node *temp_tail1, Node *temp_tail2, DLL *op1, DLL *op2){
    int len1 = -1;
    int len2 = -1;
    int point_idx1 = 0;
    int point_idx2 = 0;

    // 소수점의 인덱스를 찾기
    while(temp_tail1 != NULL) {
        if(temp_tail1->val == '.') break;
        point_idx1++;
        temp_tail1 = temp_tail1->prev;
    }

    while(temp_tail2 != NULL) {
        if(temp_tail2->val == '.') break;
        point_idx2++;
        temp_tail2 = temp_tail2->prev;
    }

    // 피연산자의 길이 찾기
    while(temp1 != NULL) {
        len1++;
        temp1 = temp1->next;
    }
    while(temp2 != NULL) {
        len2++;
        temp2 = temp2->next;
    }

    //소수점 제거, 제거를 하는 이유는 계산의 편리성을 위해
    deleteAt(op1, len1-point_idx1);
    deleteAt(op2, len2-point_idx2);

    temp1 = op1->head;
    temp2 = op2->head;

    int ans, cnt=0, zr = 0, cal_count = 0;
    int a, b, save_num=0, add_num=0, save_len;

    DLL *A = newDLL();
    DLL *B = newDLL();
    DLL *save = newDLL();

    while(temp2 != NULL) {

        //zr 이 증가하는 만큼 0을 추가해준다. 예: 123*백의자리 = 000321
        for(int i=0; i<zr; i++) append(B, newnode('0'));

        save_num = 0;
        add_num = 0;
        while(temp1 != NULL) {
            ans = (temp1->val-'0') * (temp2->val-'0');
            a = ans/10; // 십의자리
            b = ans%10; // 일의자리
            if(save_num > 0) {
                add_num = save_num + b;
                b = add_num%10;
                if(add_num > 0) {
                    a += add_num/10;
                }
            }
            if(a > 0) save_num = a;

            if(cnt == 0) append(A, newnode(b+'0'));
            else if(cnt == 1) append(B, newnode(b+'0'));

            if(a > 0 && cnt == 0 && temp1 == op1->tail->next) append(A, newnode(a+'0'));
            else if(a > 0 && cnt == 1 && temp1 == op1->tail->next) append(B, newnode(a+'0'));

            temp1 = temp1->next;
        }

        //A를 담아냈으면 B로 이동
        temp1 = op1->head;
        cnt = 1;

        zr++;

        if(cal_count == 1) {
            deleteAt(B, 0); // B의 첫번째 값을 지워준다.

            Node *save_temp = save->head;
            Node *B_temp = B->head;

            add_zero(save_temp, B_temp, save, B);

            save_temp = save->head;
            B_temp = B->head;

            Node *save_tail = save->tail->next;
            int zero_cnt = 0;
            while(save_tail->val == '0') {
                zero_cnt++;
                save_tail = save_tail->prev;
            }

            add(save, B_temp, save_temp);

            for(int i=0; i<save_len+zero_cnt; i++) {
                deleteAt(save, 0);
            }

            save_len = save->size;

            int B_size = B->size;
            for(int i=0; i<B_size-1; i++) {
                deleteAt(B, 0);
            }
        }
        if(!DLL_empty(A) && !DLL_empty(B) && cal_count == 0) {

            Node *A_temp = A->head;
            Node *B_temp = B->head;

            add_zero(A_temp, B_temp, A, B); // 자릿수를 맞춰준다.

            add(save, A_temp, B_temp); // 더해준다

            int B_size = B->size;

            for(int i=0; i<B_size-1; i++) {
                deleteAt(B, 0);
            }

            cal_count = 1;
            save_len = save->size;
        }

        temp2 = temp2->next;
    }

    printf("?? %d %d\n\n", point_idx1, point_idx2);

    if(point_idx1 != 0 && point_idx2 != 0) insertAt(save, save->size-point_idx1-point_idx2+1, newnode('.'));
    if(point_idx1 == 0 && point_idx2 != 0) insertAt(save, save->size-point_idx2+1, newnode('.'));
    if(point_idx1 != 0 && point_idx2 == 0) insertAt(save, save->size-point_idx1+1, newnode('.'));

    Node *save_temp = save->head;
    while(save_temp != NULL) {
        append(answer, newnode(save_temp->val));
        save_temp = save_temp->next;
    }

    if(answer->head->val == '.') deleteAt(answer, 0);

    print(answer);
}