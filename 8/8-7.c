/**
 * malloc接收对存储空间的请注时，并不检查请求长度的合理性；而free则认为被释放的块包含一个有效的长度字段，
 * 改进这些函数，使它们具有错误检查的功能。
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define NALLOC 10 
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
static Header *morecore(unsigned nu);
void *calloc(int n, int size);

static unsigned maxalloc = 0;

int main(int argc, char **argv){
	Header *p = (Header *)malloc(1);
	Header *h = p - 1;
	printf("alloced units=%d\n", h->s.size);
	printf("maxalloc=%d", maxalloc);
	h->s.size = 100;
	free(p);
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