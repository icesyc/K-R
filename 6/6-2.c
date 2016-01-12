/**
 * 编写一个程序,用以读入一个C语言程序,并按字母表顺序分组打印变量名,要求每一组内各变量名的前6个字符相同,其余字符不同.
 * 字符串和注释中的单词不予考虑.请将6作为一个可在命令行中设定的参数.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int getword(char *word, int lim);
char getch();
void ungetch(char c);
struct tnode *addTree(struct tnode *parent, char *word, int num, int *found);
void print_tree(struct tnode *root);
int compare(char *s, struct tnode *p, int num, int *found);

struct tnode {
	char *word;
	int count;
	int match;
	struct tnode *left;
	struct tnode *right;
};

int main(int argc, char *argv[]){
	char w[100];
	int found = 0;
	struct tnode *root = NULL;
	int num = argc > 1 ? atoi(*++argv) : 6;
	while(getword(w, 100) != EOF){
		if(isalpha(*w) && strlen(w) >= num){
			root = addTree(root, w, num, &found);
		}
		found = 0;
	}
	print_tree(root);
	return 0;
}
int compare(char *s, struct tnode *p, int num, int *found){
	char *t = p->word;
	int i = 0;
	while(*s == *t){
		if(*s == '\0') return 0;
		s++;
		t++;
		i++;
	}
	if(i >= num){
		p->match = *found = 1;
	}
	return *s - *t;
}

void print_tree(struct tnode *root){
	if(root != NULL){
		print_tree(root->left);
		if(root->match){
			printf("%10s\t%d\t%d\n", root->word, root->count, root->match);
		}
		print_tree(root->right);
	}
}
struct tnode *addTree(struct tnode *node, char *word, int num, int *found){
	if(node == NULL){
		node = (struct tnode *)malloc(sizeof(struct tnode));
		node->word = (char *)malloc(strlen(word) + 1);
		if(node->word != NULL){
			strcpy(node->word, word);
		}
		node->count = 1;
		node->match = *found;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	int ret = compare(word, node, num, found);
	if(ret > 0){
		node->right = addTree(node->right, word, num, found);
	}else if(ret < 0){
		node->left = addTree(node->left, word, num, found);
	}else{
		node->count++;
	}
	return node;
}
int getword(char *word, int lim){
	char *w = word;
	char c, nc;
	while(isspace(c = getch()));
	if(c != EOF){
		*w++ = c;
	}
	if(isalpha(c) || c == '_' || c == '#'){
		while(--lim > 0){
			c = getch();
			if(!isalnum(c) && c != '_'){
				ungetch(c);
				break;
			}
			*w++ = c;
		}
	}else if(c == '\'' || c == '\"'){
		while(--lim > 0){
			nc = getch();
			*w++ = nc;
			if(nc == '\\'){
				*w++ = getch();
				continue;
			}
			if(nc == c || nc == EOF){
				break;
			}
		}
	}else if(c == '/'){
		if((nc = getch()) == '*'){
			while((c = getch())){
				nc = getch();
				if(c == '*' && nc == '/'){
					break;
				}else{
					ungetch(nc);
				}
			}
			c = nc;
		}else{
			ungetch(nc);
		}
	}
	*w = '\0';
	return c;
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
