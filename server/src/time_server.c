#include <zmq.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <signal.h>

#define FULL_ADDRESS "tcp://*:5555"

volatile sig_atomic_t stop_flag = 0;

//ctrl+c signal handler - activating stop flag
void sigint_handling(int signum)
{
    stop_flag = 1;
}

//cleaning up
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

    //assignment of ctrl+c signal handler
    signal(SIGINT, sigint_handling);

    //waiting for "send" command from user
    char cmd[10];
    do
    {
        printf("Type send to start\n");
        scanf("%9s", cmd);
    }
    while (strcmp(cmd, "send") != 0);
    printf("Server started. Press Ctrl+C to stop\n");

    //main loop - exit when stop flag is activated
    int prev_secs = -1;
    while (!stop_flag) {
        time_t total_seconds;
        struct tm *timeinfo;
        
        time(&total_seconds);
        timeinfo = localtime(&total_seconds);

        int hours, mins, secs;
        hours = timeinfo->tm_hour;
        mins = timeinfo->tm_min;
        secs = timeinfo->tm_sec;
        
        //send data only when seconds changed
        if (prev_secs == secs)
            continue;
        
        char message[9];
        sprintf(message, "%02d:%02d:%02d", hours, mins, secs);
        zmq_send(publisher, message, strlen(message), 0);
        
        prev_secs = secs;
    }

    destroy_socket_and_context(publisher, context);

    printf("\nServer stopped\n");
    return 0;
}