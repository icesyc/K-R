/**
 * 用read，write,open和close系统调用代替标准库中功能等价的函数，重写第7章的cat程序，并通过实验比较两个版本的相对执行速度。
 * 
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char buf[BUFSIZ];
	while(--argc > 0){
		int fd = open(*++argv, O_RDONLY, 0);
		if(fd < 0){
			printf("can not open file:%s\n", *argv);
			continue;
		}
		int n;
		while((n = read(fd, buf, BUFSIZ)) > 0){
			if(write(1, buf, n) != n){
				printf("write error on file: %s\n", *argv);
			}
		}
		close(fd);

	}
	return 0;
}
