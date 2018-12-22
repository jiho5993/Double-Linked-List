typedef struct Stack_Node//연산자를 쌓을 하나의 스택
{
	char data;//하나의 노드에서 들어간 연산자나 수의 변수
	struct Stack_Node* next;
	struct Stack_Node* prev;
} Stack_Node;

typedef struct ListStack //스택의 head주소와 tail과 top 값.
{
	int top;
	Stack_Node* head;
	Stack_Node* tail;
}ListStack;
//-----------------------------------------------------------------------
Stack_Node *new_stack_node(char n) //새 스택 리스트 노드에 데이터를 집어넣을 때함수
{
	Stack_Node *temp = (Stack_Node *)malloc(sizeof(Stack_Node));
	temp->data = n;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

ListStack *new_liststack() { //새 리스트를 만들 때의 함수
	ListStack *temp = (ListStack *)malloc(sizeof(ListStack));
	temp->head = NULL;
	temp->tail = NULL;//----------
	temp->top = -1;
	return temp;
}