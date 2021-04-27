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
	int check=0;//�ʱ�ȭ�� ����ƴ��� Ȯ���Ѵ�.
	listNode* headnode=NULL;

	printf("[----- [������] [2018038031] -----]\n");
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
			check++;
			break;
		case 'p': case 'P':
			if(check)
				printList(headnode);
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'i': case 'I':
			if(check){
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				insertNode(headnode, key);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'd': case 'D':
			if(check){
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				deleteNode(headnode, key);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'n': case 'N':
			if(check){
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				insertLast(headnode, key);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'e': case 'E':
			if(check)
				deleteLast(headnode);
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'f': case 'F':
			if(check){
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				insertFirst(headnode, key);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 't': case 'T':
			if(check)
				deleteFirst(headnode);
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'r': case 'R':
			if(check)
				invertList(headnode);
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'q': case 'Q':
			if(check)
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){
	listNode* node = h->rlink;//ó����带 ����Ű���Ѵ�.
	while(h!=node){//��������带 �����ߴٸ� node==�ص���(h) �� ������ �ݺ��� ����ȴ�.
		node=node->rlink;
		free(node->llink);
	}
	free(h);//���������� �ص��带 �����Ѵ�.
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
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//��� ����� �ּҰ� rlink, llink�� �����ش�.

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {//���Ḯ��Ʈ�� ���������� ������ ������ �ּҰ�, rlink, llink���� �����ش�.
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

int insertLast(listNode* h, int key) {//���Ḯ��Ʈ�� �������� ��� ����
	listNode* node=(listNode*)malloc(sizeof(listNode));//������ ���
	node->key=key;//������ ����� key��
	node->rlink=h;//������ ����̱� rlink�� ������ ��� ��� h�� ����Ų��.

	if(h->rlink==h){//���Ḯ��Ʈ�� ����ٸ� ù��°���=��������� �̱� ����
		h->rlink=node;//�ص����� llink�� rlink�� ������ ��带 ����Ų��.
		h->llink=node;
		node->llink=h;//������ ����� llink�� �ص��带 ����Ų��.
	}
	else{//���Ḯ��Ʈ�� ������� �ʴٸ�
		node->llink=h->llink;//������ ����� llink�� ������ ������ ��带 ����Ű���Ѵ�.
		h->llink->rlink=node;//������ ����������� rlink�� ������ ��带 ����Ű���Ѵ�.
		h->llink=node;//�ص����� llink�� �ٲ� ��������带 ����Ű���Ѵ�.
	}

	return 1;
}

int deleteLast(listNode* h) {//���Ḯ��Ʈ�� ������ ������
	if(h->rlink==h){//���Ḯ��Ʈ�� ����ٸ� �Լ��� �����Ѵ�.
		printf("���Ḯ��Ʈ�� ������ϴ�.\n");
		return 0;
	}
	else{//���Ḯ��Ʈ�� ��������ʴٸ�
		h->llink=h->llink->llink;//�ص����� llink�� ����������� ������ �ٲ۴�.
		free(h->llink->rlink);//�ٲ� ����������� rlink�� �̿��ؼ� ������ ��������带 �����Ѵ�.
		h->llink->rlink=h;//�ٲ� ����������� rlink�� �ص��带 ����Ű�� �����.
	}
	return 1;
}

int insertFirst(listNode* h, int key) {//���Ḯ��Ʈ�� ó���� ������
	listNode* node=(listNode*)malloc(sizeof(listNode));//������ ���
	node->key=key;//������ ����� key��
	node->llink=h;//ó�� ����̱� ������ llink�� ��� ��� h�� ����Ų��.

	if(h->rlink==h){//���Ḯ��Ʈ�� ����ٸ� ù��°��� = ��������� �̱� ����
		h->rlink=node;//�ص����� rlink�� llink�� ������ ��带 ����Ű�� �Ѵ�.
		h->llink=node;
		node->rlink=h;//������ ����� rlink�� �ص��带 ����Ű���Ѵ�.
	}
	else{//���Ḯ��Ʈ�� ��������ʴٸ�
		node->rlink=h->rlink;//������ ����� rlink�� ������ ù��° ��带 ����Ű���Ѵ�.
		h->rlink->llink=node;//���� ù��° ����� llink�� ������ ��带 ����Ű���Ѵ�.
		h->rlink=node;//�ص����� rlink�� ������ ��带 ����Ű���Ѵ�.
	}
	return 1;
}

int deleteFirst(listNode* h) {//���Ḯ��Ʈ�� ó�� ��� ����
	if(h->rlink==h){//���Ḯ��Ʈ�� ����ٸ� �Լ��� �����Ѵ�.
		printf("���Ḯ��Ʈ�� ������ϴ�.\n");
		return 0;
	}
	else{//���Ḯ��Ʈ�� ��������ʴٸ�
		h->rlink=h->rlink->rlink;//�ص����� rlink�� ó������� �������� �ٲ۴�.
		free(h->rlink->llink);//�ٲ� ó������� llink�� �̿��ؼ� ������ ó����带 �����Ѵ�.
		h->rlink->llink=h;//�ٲ� ó������� llink�� �ص��带 ����Ű�� �����.
	}
	return 1;
}

int invertList(listNode* h) {//����Ʈ�� ��ũ�� �������� �� ��ġ
	listNode* tmp=NULL;//�ӽ÷� �ּҰ��� �����Ѵ�.
	listNode* node=h;//�ּҰ��� �������� �ٲ� ��带 �����Ѵ�.
	if(h->rlink==h||h->rlink->rlink==h)//���Ḯ��Ʈ�� ��尡 ���ų� �Ѱ���� �Լ��� �����Ѵ�.
		return 0;
	else{//��尡 2�� �̻��̶��
		do{
			tmp=node->rlink;//rlink�� �ӽ÷� �����Ѵ�.
			node->rlink=node->llink;//rlink�� llink�� �ٲ۴�.
			node->llink=tmp;//llink�� �ӽ÷� ������ rlink�� �ִ´�.
			node=node->rlink;//���� ���� ����.
		}while(node!=h);//�ٽ� �ص���� �����ߴٸ� �����Ѵ�.
	}
	return 0;
}

int insertNode(listNode* h, int key) {//����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
	listNode* node=NULL;//������ ���
	listNode* search=h->rlink;
	if(h->rlink==h){//���� ���Ḯ��Ʈ�� ����ִٸ� ó���� ��带 �����ϰ� �Լ��� �����Ѵ�.
		insertFirst(h, key);
		return 0;
	}
	else{//���Ḯ��Ʈ�� ��������ʴٸ�
		while(search!=h){//���Ḯ��Ʈ�� ���������� �˻��Ѵ�.
			if(search->key>key){//�Է¹��� key������ ū key�� ������ ��带 �߰��ߴٸ�
				node=(listNode*)malloc(sizeof(listNode));//������ ����� ������ �Ҵ��Ѵ�.
				node->key=key;//key�� ����
				node->rlink=search;//rlink�� ã�� ��带 ����Ű���Ѵ�.
				node->llink=search->llink;//llink�� ã�� ����� ����带 ����Ű���Ѵ�.
				search->llink->rlink=node;//ã�� ����� ������� rlink�� ������ ��带 ����Ű���Ѵ�.
				search->llink=node;//ã�� ����� llink�� ������ ��带 ����Ű���Ѵ�.
				return 0;//�Լ��� �����Ѵ�.
			}
			search=search->rlink;//���� ��带 �˻��Ѵ�.
		}
	}
	insertLast(h,key);//���Ḯ��Ʈ�� ���������� �˻��ߴµ��� �Է¹��� key������ ū key�� ������ ��尡 ���ٸ� �� ���� �������� ���Եȴ�.

	return 0;
}

int deleteNode(listNode* h, int key) {//����Ʈ�� �˻��Ͽ�, �Է¹��� key�� ������ ��带 ����
	listNode* search=h->rlink;//������ ��带 ã�� ������
	if(h->rlink==h){//���Ḯ��Ʈ�� ����ٸ� �Լ��� �����Ѵ�.
		printf("���Ḯ��Ʈ�� ������ϴ�\n");
		return 0;
	}
	else{//��������ʴٸ�
		while(search!=h){//���Ḯ��Ʈ�� ���������� �˻��Ѵ�.
			if(search->key==key){//������ ��带 ã�Ҵٸ�
				search->rlink->llink=search->llink;//������ ����� �ճ���� llink�� ������ ����� ������ �ٲ۴�.
				search->llink->rlink=search->rlink;//������ ����� ������� rlink�� ������ ����� �ճ��� �ٲ۴�.
				free(search);//��带 �����Ѵ�.
				return 0;
			}
			search=search->rlink;//�ճ��� �̵��Ѵ�.
		}
	}
	printf("ã�� key�� ������ ��尡 �����ϴ�.\n");
	return 0;
}


