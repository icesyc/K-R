/**
 * 编写函数bfree(p, n)，释放一个包含n个字符的任意块p，并将它放入由malloc和free维护的空闲块链表中。
 * 通过使用bfree，用户可以在在任意时刻向空闲块链表中添加一个静态或外部数组。
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define NALLOC 1 
#define MAXBYTES 10240
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
unsigned bfree(void *p, int n);
static Header *morecore(unsigned nu);

static unsigned maxalloc = 0;

int main(int argc, char **argv){
	char *p = (char *)malloc(100);
	printf("allocted %u\n", ((Header *)p-1)->s.size * sizeof(Header));
	int n = bfree(p, 128);
	printf("%u bytes freed\n", n);
	return 0;
}

static Header base;
static Header *freep = NULL;
void *malloc(unsigned bytes){
	Header *p, *prevp;
	if(bytes > MAXBYTES){
		fprintf(stderr, "alloc: can't allocate more than %u bytes\n", MAXBYTES);
		return NULL;
	}
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
	maxalloc = nu > maxalloc ? nu : maxalloc;
	free((void *)(up + 1));
	return freep;
}

void free(void *ap){
	Header *bp, *p;
	bp = (Header *)ap - 1;
	if(bp->s.size == 0 || bp->s.size > maxalloc){
		fprintf(stderr, "free: can't free %u units\n", bp->s.size);
		return;
	}
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
unsigned bfree(void *p, int n){
	if(n < sizeof(Header)){
		return 0;
	}
	Header *hp = (Header *)p;
	hp->s.size = n /sizeof(Header);
	free((void *)(hp+1));
	return (hp->s.size -1) * sizeof(Header);
}
