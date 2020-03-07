#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"
#include "math.h"
#include "string.h"

const int N = 300;

void Test(void){
    char line[N];
    FILE *fp;
    char *sysCommand;
      
    if ((fp = popen("cat /sys/devices/platform/cpu/uuid", "r")) == NULL) {
        printf("popen error");
        return;
    }
	printf("uuid:");
    while (fgets(line, sizeof(line)-1, fp) != NULL){
		printf("%s",line);        
    }
    pclose(fp);
    
    if ((fp = popen("cat /sys/devices/platform/cpu/guid", "r")) == NULL) {
        printf("popen error");
        return;
    }
	printf("guid:");
    while (fgets(line, sizeof(line)-1, fp) != NULL){
        printf("%s",line);
    }
    pclose(fp);
}

int main(){
    Test();
    return 0;
}
