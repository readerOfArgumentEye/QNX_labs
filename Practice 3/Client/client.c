#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h>

int main(){
    char smsg[20];
    char rmsg[200];
    int coid;
    long serv_pid;
    printf("Program client, input PID server:\n");
    scanf("%ld", &serv_pid);
    printf("Input value is %ld\n", serv_pid);
    coid = ConnectAttach(0, serv_pid, 1, 0, 0);
    printf("Result of connection is %d \nInput message: ", coid);
    scanf("%s", &smsg);
    printf("Input %s \n", smsg);
    if(MsgSend(coid, smsgm, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1)
        printf("Error MsgSend \n");
    printf("Response: \"%s\"\n", rmsg);
    ConnectDetach(coid);
    return 1;
}
