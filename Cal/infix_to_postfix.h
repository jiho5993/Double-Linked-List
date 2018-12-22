void inFix_to_postFix(DLL* list, Node* temp, ListStack* liststack) {
  	char returned_operator; // ()시 연산자를 저장하고 옮기기위한 또하나의 temp
	int size_temp = list->size + 1;//size--로 연산 수를 정하므로 size_temp로 연산
	int initial_size = list->size + 1;//원본의 사이즈를 추후 연산을 위해 저장해놓는다.
  	while (size_temp) {
		if (isdigit(temp->val) || temp->val == '.')//수와 '.'은 operator stack에 쌓지 않고 바로 node로 이동
		{
			append(list, newnode(temp->val));//끝단에 추가해주기.
		}
		else
		{
			switch (temp->val)
			{
			case '(':
				push(liststack, new_stack_node(temp->val));//스택에 '('쌓기
				break;

			case ')':
				while (1) {//'('을 만날동안 스택에 쌓인 연산자를 꺼내서 추가노드에 저장.
					returned_operator = pop(liststack);
					if (returned_operator == '(')
						break;
					append(list, newnode(returned_operator));
				}
				break;

			case '+': case '-':
			case '*': case '/':
				append(list, newnode('|')); //두 인자가 붙었을 때 인자를 구분하기위해 문자 추가해줌
				while (!isEmpty(liststack) && (precedence(temp->val) <= precedence(peek(liststack)))) {
					append(list, newnode(pop(liststack)));
				}
				push(liststack, new_stack_node(temp->val));
				break;
            case '\n': case' ':
  		    case '\0':
  			    break;
  		    default:
  			    printf("ERROR : DO NOT ENTER CHARACTERS\n");
  			    exit(1);
			}
		}
		temp = temp->next;//temp 노드를 한번 앞으로 이동시킴
		size_temp--;
	}
	while (!isEmpty(liststack)) {//스택에 남은 연산자를 전부다 꺼내서 node의 끝에 연결해줌
		append(list, newnode(pop(liststack)));
	}
	while (initial_size--)//앞에 남아있는 중위연산식 노드를 싹다 지워버린다.
	{
		deleteAt(list, initial_size);
	}
	list->tail = list->tail->next;//왠지 모르겠지만 테일이 끝에서 한노드 앞에 있어서 이동한다...
  //-----------------------------------------------------------------
}
