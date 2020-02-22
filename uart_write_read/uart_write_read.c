#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <poll.h>
#include <sys/prctl.h>
#include <signal.h>

//���ڽ��յ��ַ�z�������
#define EXIT_CHAR 'z'

//�ӽ������еı�־λ��child_signal=0�ӽ���ѭ��ͨ�����ڷ��ͣ�=1�ӽ��̽���
static int child_signal;
void handle_signal(int signo){
	if (signo == SIGHUP){                 
        printf("child recv SIGHUP..\n");
        child_signal = 1;
    }
}

//���ڳ�ʼ������
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);

int main(int argc,char **argv)
{
	int fd,ret,nread,count=0;
	char *uart_innode;
	char *buffer = "hello world!\n";
	char buff[8];
	struct pollfd fds[1];
	child_signal = 0;
	
	printf("\r\n uart_write_read_test start\r\n");
	if(2 != argc){
		printf("Usage:	uart_write_read [uart port]\r\n");	
		return 1;
	}
	printf("TestDemon input char 'z',TestDemon exit!\n");
	
	uart_innode = argv[1];
	if((fd = open(uart_innode, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s is failed",uart_innode);
		return 1;
	}	
	else {
		printf("open %s is success\n",uart_innode);
		//���ڲ�������
		set_opt(fd, 115200, 8, 'N', 1);
		fds[0].fd = fd;
		fds[0].events = POLLIN;
	}
	
	pid_t pid;
	//��������	
	pid = fork();
	//�������̳���
	if(pid == -1){
		printf("fork failed\n");
		return 1;
	}
	//�ӽ���
	else if(!pid){
		//��ʼ���źź������������̽�������ִ���źź������޸�child_signal��ֵΪ1
		//��child_signal=1�����ӽ��̽���
		signal(SIGHUP, handle_signal);
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		while(!child_signal){
			//���ڷ��ͺ�����û��1�뷢��һ���ַ���
			write(fd,buffer, strlen(buffer));
			sleep(1);
		}
		printf("child fork exit ...!\n");
		return 0;
	}
	//������
	else{
		while(1){
			//��ѯ�ķ�ʽ��ȷ�ϴ����Ƿ���յ�����
			ret = poll(fds,1, 5000);
			if(ret == -1){
				printf("poll error!\n");
				return 1;
			}
			else if(!ret){
				printf("Time out!\n");
				printf("fds[0].revents is %d!\n",(char)(fds[0].revents));
				printf("recev all count = %d!\n",count);
			}
			else if(fds[0].revents & POLLIN){
				//���ڽ��պ���
				while((nread = read(fd,buff,1))>0){
					count+=nread;
					printf("get data count = %d!\n",count);
					//����յ��ַ�z�����˳�����
					if(EXIT_CHAR==buff[0]){
						printf("parent fork exit ...!\n");					
						close(fd);
						return 0;
					}
				}
			}		
	    }
    }	
	close(fd);
	return 0;
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 )
		newtio.c_cflag |=  CSTOPB;
		newtio.c_cc[VTIME]  = 0;
		newtio.c_cc[VMIN] = 0;
		tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	
	//	printf("set done!\n\r");
	return 0;
}
