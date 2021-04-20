/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);
int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);
void printList(listNode* h);

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	h=h->rlink;//h가 처음 노드를 가르키게한다.
	while(h->key!=-9999){//원래 헤드노드의 키값은 -9999이기때문에 h가 앞노드를 해제하면서 key값이 -9999라면 반복을 종료한다.
		h=h->rlink;
		free(h->llink);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) {//연결리스트의 마지막에 노드 삽입
	listNode* node=(listNode*)malloc(sizeof(listNode));//삽입할 노드
	node->key=key;//삽입할 노드의 key값
	node->rlink=h;//마지막 노드이기 rlink가 때문에 헤드 노드 h를 가르킨다.

	if(h->rlink==h){//연결리스트가 비었다면 첫번째노드=마지막노드 이기 때문
		h->rlink=node;//해드노드의 llink와 rlink가 삽입할 노드를 가르킨다.
		h->llink=node;
		node->llink=h;//삽입할 노드의 llink도 해드노드를 가르킨다.
	}
	else{//연결리스트가 비어있지 않다면
		node->llink=h->llink;//삽입할 노드의 llink가 본래의 마지막 노드를 가르키게한다.
		h->llink->rlink=node;//본래의 마지막노드의 rlink가 삽입할 노드를 가르키게한다.
		h->llink=node;//해드노드의 llink를 바뀐 마지막노드를 가르키게한다.
	}

	return 1;
}

int deleteLast(listNode* h) {//연결리스트의 마지막 노드삭제
	if(h->rlink==h){//연결리스트가 비었다면 함수를 종료한다.
		printf("연결리스트가 비었습니다.\n");
		return 0;
	}
	else{//연결리스트가 비어있지않다면
		h->llink=h->llink->llink;//해드노드의 llink를 마지막노드의 전노드로 바꾼다.
		free(h->llink->rlink);//바꾼 마지막노드의 rlink를 이용해서 본래의 마지막노드를 해제한다.
		h->llink->rlink=h;//바꾼 마지막노드의 rlink가 해드노드를 가르키게 만든다.
	}
	return 1;
}

int insertFirst(listNode* h, int key) {//연결리스트의 처음에 노드삽입
	listNode* node=(listNode*)malloc(sizeof(listNode));//삽입할 노드
	node->key=key;//삽입할 노드의 key값
	node->llink=h;//처음 노드이기 때문에 llink가 헤드 노드 h를 가르킨다.

	if(h->rlink==h){//연결리스트가 비었다면 첫번째노드 = 마지막노드 이기 때문
		h->rlink=node;//해드노드의 rlink와 llink가 삽입할 노드를 가르키게 한다.
		h->llink=node;
		node->rlink=h;//삽입할 노드의 rlink가 해드노드를 가르키게한다.
	}
	else{//연결리스트가 비어있지않다면
		node->rlink=h->rlink;//삽입할 노드의 rlink가 본래의 첫번째 노드를 가르키게한다.
		h->rlink->llink=node;//본래 첫번째 노드의 llink가 삽입할 노드를 가르키게한다.
		h->rlink=node;//해드노드의 rlink를 삽입할 노드를 가르키게한다.
	}
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {


	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	return 0;
}


