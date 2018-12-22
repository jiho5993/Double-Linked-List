#include "node.h"
#include "node_function.h"
#include "stack_node.h"
#include "stack_function.h"
#include "infix_to_postfix.h"
#include "cal.h"

int main() {

    printf("====== Welcome to infinite calculator! ======\n");
    printf("Enter the expression in infix notation.\n\n");

    FILE *fp;
    fp = fopen("input.txt","r");

    DLL *list = newDLL();
    printf("Input : ");

    char characters = ' ';
    while ((characters = fgetc(fp)) != EOF)
    {
        append(list, newnode(characters));
    }
    fclose(fp);

    erasewhitespace(list);//쓰잘데기 없는 것들 지우기
    print(list);
    //-------------------------------------------------------------------------------------------------------------------
    Node* temp = list->head;//HEAD 이동시 head고유의 주소를 잊어버리므로 temp을 만들어 이동시키며 값을 얻는다..

    ListStack *liststack = new_liststack();//스택리스트 생성 top = -1로
    init_stack(liststack); //스택의 시작 주소를 배정해준다.

    inFix_to_postFix(list, temp, liststack);
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------

    cal(list, liststack);

    return 0;
}