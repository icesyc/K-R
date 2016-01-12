/**
 * 标准库函数calloc(n,size)返回一个指针，它指向n个长度为size的对象，且所有分配的存储空间都被初始化为0。
 * 通过调用或修改malloc函数来实现calloc函数。
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define NALLOC 16

typedef double Align;
union header{
	struct s{
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};
typedef union header Header;
void *malloc(unsigned bytes);
void free(void *);
static Header *morecore(unsigned nu);
void *calloc(int n, int size);

int main(int argc, char **argv){
	Header *p = (Header *)calloc(1, 10);
	printf("applied=%d allocated=%d\n", 10, (p-1)->s.size * NALLOC);
	return 0;
}

void *calloc(int n, int size){
	char *p, *q;
	p = q = (char *)malloc(n * size);
	int i;
	for(i = 0; i < n * size; i++){
		*p++ = 0; 
	}
	return (void *)q;
}

static Header base;
static Header *freep = NULL;
void *malloc(unsigned bytes){
	Header *p, *prevp;
	if(freep == NULL){
		prevp = p = freep = &base;
	}
	int nunits = (bytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	for(p = prevp;; prevp = p, p = p->s.ptr){
		if(p->s.size >= nunits){
			if(p->s.size == nunits){ //正好
				prevp->s.ptr = p->s.ptr;
			}else{
				p->s.size -= nunits;
				p += nunits;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}
		if(p == freep){
			if((p = morecore(nunits)) == NULL){
				return NULL;
			}
		}
	}
}
Header *morecore(unsigned nu){
	Header *up;
	char *cp;
	if(nu < NALLOC){
		nu = NALLOC;
	}
	cp = (char *)sbrk(nu * sizeof(Header));
	if(cp == (char *) -1){
		return NULL;
	}
	up = (Header *)cp;
	up->s.size = nu;
	free((void *)(up + 1));
	return freep;
}

void free(void *ap){
	Header *bp, *p;
	bp = (Header *)ap - 1;
	for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr){
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr)){
			break;
		}
	}
	if(bp + bp->s.size == p->s.ptr){
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}else{
		bp->s.ptr = p->s.ptr;
	}
	if(p + p->s.size == bp){
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}else{
		p->s.ptr = bp;
	}
	freep = p;
}