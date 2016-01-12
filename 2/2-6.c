#include <stdio.h>
/**
 * 编写一个函数setbits(x,p,n,y),该函数返回对x执行下列操作
 * 将x中从第p位开始的n个位设置为y中最右边n位的值, x的其余位不变
 * 这里假设最右边是第0位,保持与书一致
 */
int setbits(int x, int p, int n, int y);
int main(){
	int r = setbits(0177, 5, 2, 0100);
	printf("%d\n", r);
}
int setbits(int x, int p, int n, int y){
	int tmp, tmp2;
	//向左移动n位,右边补0,再取反,可获得右边n位的1
	tmp = ~(~0 << n);
	//获得y的右边n位
	tmp = y & tmp;
	//将y的右边n位向左移到p的位置
	tmp = tmp << (p - n + 1);

    //获取右边n位1并向左移动到p的位置,再取反，获得p至n区间全是0的屏蔽码
    tmp2 = ~((~(~0 << n)) << (p - n + 1));
    //将x的p至n区间至为0
    tmp2 = x & tmp2;
    //将区间置为y的右边n位
    return tmp2 | tmp;
}
