#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h>

void registerSwap(char* message, char* reply){
    int i = 0;
    strcpy(reply, message);
    for (i = 0; reply[i] != '\0'; i++){
        if(isupper(reply[i]))
            reply[i] = tolower(reply[i]);
        else if (islower(reply[i]))
            reply[i] = toupper(reply[i]);
    }
}

void server(void){
    int rcvid;
    int child;
    char message[512];
    char reply[512];
    printf("Server start working \n");
    child = ChannelCreate(0);
    printf("Channel id: %d \n", child);
    printf("Pid: %d \n", getpid());
    while(1){
        rcvid = MsgReceive(child, message, sizeof(message), NULL);
        printf("Message was received succsessfully, rcvid %X \n", rcvid);
        printf("The content is \"%s\".\n", message);
        registerSwap(message, reply);
        MsgReply(rcvid, EOK, reply, sizeof(reply));
    }
}

int main(void){
    printf("Program server \n");
    server();
    sleep(5);
    return(1);
}
