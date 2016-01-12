/**
 * 编写一个交叉引用程序,打印文档中所有单词的列表,并且每个单词还有一个列表,记录出现过该单词的行号.
 * 对the, and等非实义单词不予考虑.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int getword(char *word, int *line, int lim);
char getch();
void ungetch(char c);
struct tnode *addTree(struct tnode *parent, char *word, int line);
void print_tree(struct tnode *root);
struct tnode *searchTree(struct tnode *node, char *word);
struct tnode *buildTree();
char *lower(char *s){
	char *p = (char *)malloc(strlen(s) + 1);
	char *t = p;
	while((*t++ = tolower(*s++)));
	return p;
}

struct tnode {
	char *word;
	int count;
	int lines[100];
	struct tnode *left;
	struct tnode *right;
};
int main(int argc, char *argv[]){
	struct tnode *tree = buildTree();
	char w[100];
	int line = 1;
	struct tnode *root = NULL;
	while(getword(w, &line, 100) > 0){
		if(searchTree(tree, lower(w)) == NULL){
			root = addTree(root, w, line);
		}
	}
	print_tree(root);
	return 0;
}
struct tnode *stopWordTree = NULL;
struct tnode *buildTree(){
	char *words[] = {"the", "which", "were", "who", "where", "while", "not", "is", "then", "and", "it", "that", "to", "not", "a", "be", "of", "him", "he", "her", "they", "was", "if", "in", "so", "for", "by", "as", "at"};
	int cnt = sizeof(words) / sizeof(char *);
	for(int i = 0; i < cnt; i++){
		stopWordTree = addTree(stopWordTree, words[i], 0);
	}
	return stopWordTree;
}
struct tnode *searchTree(struct tnode *node, char *word){
	if(node == NULL){
		return NULL;
	}	
	int ret = strcmp(word, node->word);
	if(ret == 0){
		return node;
	}else if(ret > 0){
		return searchTree(node->right, word);
	}else{
		return searchTree(node->left, word);
	}
}

void print_tree(struct tnode *root){
	int i;
	if(root != NULL){
		print_tree(root->left);
		printf("%s ", root->word);
		for(i = 0; i < root->count; i++){
			printf("%d%c", root->lines[i], i == root->count - 1 ? '\n' : ',');
		}
		print_tree(root->right);
	}
}

struct tnode *addTree(struct tnode *node, char *word, int line){
	if(node == NULL){
		node = (struct tnode *)malloc(sizeof(struct tnode));
		node->word = (char *)malloc(strlen(word) + 1);
		if(node->word != NULL){
			strcpy(node->word, word);
		}
		node->count = 1;
		node->lines[0] = line;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	int ret = strcmp(word, node->word);
	if(ret > 0){
		node->right = addTree(node->right, word, line);
	}else if(ret < 0){
		node->left = addTree(node->left, word, line);
	}else{
		node->count++;
		if(node->count <= 100){
			node->lines[node->count - 1] = line;
		}
	}
	return node;
}

int getword(char *word, int *line, int lim){
	char *w = word;
	char c, nc;
	while(!isalpha(c = getch()) && c != EOF){
		if(c == '\n') (*line)++;
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
