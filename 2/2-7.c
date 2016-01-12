/**
 * 编写一个函数invert(x,p,n),该函数返回对x执行下列操作后的结果值
 * 将x中从第p位开始的n个二进制位求反(即,1变成0,0变成1), x的其余各位不变
 */
#include <stdio.h>
int invert(int x, int p, int n);
int main(){
    int r = invert(0177, 3, 2);
    printf("%d\n", r);
}
int invert(int x, int p, int n){
    int tmp, tmp2;

	//先将x取反，再取区间的bit
	tmp = ~x;
	tmp = tmp & ((~(~0 << n)) << (p - n + 1));

    //获取右边n位1并向左移动到p的位置,再取反，获得p至n区间全是0的屏蔽码
    tmp2 = ~((~(~0 << n)) << (p - n + 1));
    //将x的p至n区间至为0
    tmp2 = x & tmp2;
    return tmp2 | tmp;
}
