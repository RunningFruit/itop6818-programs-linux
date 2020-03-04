#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"
#include "math.h"
#include "string.h"



const int N = 3000;

void Test(void){
    char line[N];
    FILE *fp;
    char *sysCommand;
      
    if ((fp = popen("ls", "r")) == NULL) {
        printf("popen error");
        return;
    }
    while (fgets(line, sizeof(line)-1, fp) != NULL){
	printf("%s",line);        
    }
    pclose(fp);
}

int main(){
    Test();
    return 0;
}
