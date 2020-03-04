#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main(int argc,char *argv[])
{
	int fd;
	char *relay_ctl = "/dev/relay_ctl";
	
	if(argc < 2){
		printf ("input argv[1] 0 or 1!\n");
		exit(1);
	}
	if(atoi(argv[1]) >= 2){
		printf ("argv[1] is 0 or 1\n");
		exit(1);
	}
	
	if((fd = open(relay_ctl,O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s failed\n",relay_ctl);
		exit(1);
	}
	printf("open %s sucess\n",relay_ctl);
	ioctl(fd,atoi(argv[1]));
	
	
	close(fd);
	return(0);
}
