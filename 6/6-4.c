/**
 * 编写一个程序，根据单词的出现频率按降序打印输入的各个不同单词，并在每个单词的前面标上它的出现次数。
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int getword(char *word, int lim);
char getch();
void ungetch(char c);
struct tnode *addTree(struct tnode *parent, char *word);
void print_tree(struct tnode *root);
void tree_store(struct tnode *root);
void sort_list(struct tnode *list[]);
void qsort(struct tnode *list[], int left, int right);
void swap(struct tnode *list[], int i, int j);
struct tnode *list[1000];
int node_count = 0;

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};
int main(int argc, char *argv[]){
	char w[100];
	struct tnode *root = NULL;
	while(getword(w, 100) > 0){
		root = addTree(root, w);
	}
	tree_store(root);
	sort_list(list);
	for(int i = 0; i < node_count; i++){
		printf("%d\t%s\n", list[i]->count, list[i]->word);
	}
	return 0;
}

void sort_list(struct tnode *list[]){
	return qsort(list, 0, node_count-1);
}
void qsort(struct tnode *list[], int left, int right){
	if(left < right){
		struct tnode *mid = list[left];
		struct tnode *tmp;
		int last = left;
		for(int i = left + 1; i <= right; i++){
			if(list[i]->count > mid->count){
				swap(list, i, ++last);
			}
		}
		swap(list, left, last);
		qsort(list, left, last - 1);
		qsort(list, last + 1, right);
	}
}

void swap(struct tnode *list[], int i, int j){
	struct tnode *tmp;
	tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
}
void tree_store(struct tnode *p){
	if(p != NULL){
		tree_store(p->left);
		list[node_count++] = p;
		tree_store(p->right);
	}
}
void print_tree(struct tnode *root){
	if(root != NULL){
		print_tree(root->left);
		printf("%10d %s\n", root->count, root->word);
		print_tree(root->right);
	}
}

struct tnode *addTree(struct tnode *node, char *word){
	if(node == NULL){
		node = (struct tnode *)malloc(sizeof(struct tnode));
		node->word = (char *)malloc(strlen(word) + 1);
		if(node->word != NULL){
			strcpy(node->word, word);
		}
		node->count = 1;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	int ret = strcmp(word, node->word);
	if(ret > 0){
		node->right = addTree(node->right, word);
	}else if(ret < 0){
		node->left = addTree(node->left, word);
	}else{
		node->count++;
	}
	return node;
}

int getword(char *word, int lim){
	char *w = word;
	char c, nc;
	while(!isalpha(c = getch()) && c != EOF){
	}
	if(c != EOF){
		*w++ = c;
	}
	while(--lim > 0){
		c = getch();
		if(!isalpha(c)){
			ungetch(c);
			break;
		}
		*w++ = c;
	}
	*w = '\0';
	return w - word;
}

 char buff[100];
 int bp = 0;
 char getch(){
     return bp > 0 ? buff[--bp] : getchar();
 }
 void ungetch(char c){
     if(bp < 100){
         buff[bp++] = c;
     }
 }
