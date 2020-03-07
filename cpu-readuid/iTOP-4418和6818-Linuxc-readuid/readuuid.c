#include <stdio.h>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <math.h>  
#include <string.h>

     
int main(int argc, char** argv) 
{ 
	int ret = 0,i; 
	int value; 
	FILE *fp;
 	char buf[50];
    			
	if((fp = fopen("/sys/devices/platform/cpu/uuid", "rt"))==NULL){
		perror("fopen");
		return 0;
	
	}
	if(ret = fread( buf, 1, sizeof(buf), fp)<0){ 			
		perror("fread");
		return 0;
	}		
	fclose(fp);
	printf("uuid : %s\n",buf);
	
	
	if((fp = fopen("/sys/devices/platform/cpu/guid", "rt"))==NULL){
		perror("fopen");
		return 0;
	}
	if(ret = fread( buf, 1, sizeof(buf), fp)<0){ 			
		perror("fread");
		return 0;
	}	
	fclose(fp);
	printf("guid : %s\n",buf);
	
	return 1; 
}
