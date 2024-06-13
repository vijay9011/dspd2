#include<stdio.h>
#include<stdlib.h>

struct node{
int data;
struct node* left;
struct node* right;
};

struct node* newnode(int data){
struct node* node = (struct Node*)malloc(sizeof(struct node));
node->data=data;
node->left=NULL;
node->right=NULL;
return node;
}

void Inorder(struct node* node){
if(node==NULL){
return;
}
else{

Inorder(node->left);
printf("%d->", node->data);
		Inorder(node->right);
		}

	}
	

void Preorder(struct node* node){
	if(node==NULL){
		return;
		}
		else{
			printf("%d->", node->data);
			Inorder(node->left);
		Inorder(node->right);
		}

	}
	
// Post-Order Traversal
void Postorder(struct node* node){
	if(node==NULL){
		return;
		}
		else{
			
		Inorder(node->left);
		Inorder(node->right);
		printf("%d->", node->data);
		}

	}

int main (){
	struct node* Root = newnode(10);
	Root->left = newnode(20);
	Root->right = newnode(30);
	Root->left->left=newnode(40);
	Root->right->left=newnode(50);
	printf("Inorder treversal \n");
	Inorder(Root);
	printf("\n\nPreorder treversal \n");
	Preorder(Root);
	printf("\n\nPostorder treversal \n");
	Preorder(Root);
	
}