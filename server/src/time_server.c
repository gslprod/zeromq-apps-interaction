#include <zmq.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define FULL_ADDRESS "tcp://*:5555"

//cleaning up function
void destroy_socket_and_context(void *socket, void *context)
{
    zmq_close(socket);
    zmq_ctx_destroy(context);
}

int main(void)
{
    //creating and setting up PUB socket
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    //clean up and exit if connection error
    if (zmq_bind(publisher, FULL_ADDRESS) != 0)
    {
        destroy_socket_and_context(publisher, context);

        printf("Connection error. Exiting\n");
        return 1;
    }

    //main loop
    while (1)
    {
        printf("Type 'send' to send message, 'exit' to quit program\n");

        char cmd[30];
        scanf("%29s", cmd);

        //waiting for command from user
        if (strcmp(cmd, "exit") == 0)
            break;
        else if (strcmp(cmd, "send") != 0)
        {
            printf("Unknown command\n");
            continue;
        }

        time_t total_seconds;
        struct tm *timeinfo;
        
        //getting time
        time(&total_seconds);
        timeinfo = localtime(&total_seconds);

        int hours, mins, secs;
        hours = timeinfo->tm_hour;
        mins = timeinfo->tm_min;
        secs = timeinfo->tm_sec;
        
        //sending message with time
        char message[9];
        sprintf(message, "%02d:%02d:%02d", hours, mins, secs);
        zmq_send(publisher, message, strlen(message), 0);

        printf("Message sent: %s\n", message);
    }

    //cleaning up and exiting
    destroy_socket_and_context(publisher, context);

    printf("\nExiting\n");
    return 0;
}