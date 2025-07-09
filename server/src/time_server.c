#include <zmq.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>

#define FULL_ADDRESS "ipc:///tmp/time_server"

volatile sig_atomic_t stop_flag = 0;

void sigint_handling(int signum) {
    stop_flag = 1;
}

int main()
{
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int code = zmq_bind(publisher, FULL_ADDRESS);
    assert(code == 0 && "Connection error");

    signal(SIGINT, sigint_handling);

    char cmd[10];
    do
    {
        printf("Type send to start\n");
        scanf("%9s", cmd);
    }
    while (strcmp(cmd, "send") != 0);
    printf("Server started. Press Ctrl+C to stop\n");

    while (!stop_flag) {
        time_t total_seconds;
        struct tm *timeinfo;

        time(&total_seconds);
        timeinfo = localtime(&total_seconds);

        int hours, mins, secs;
        hours = timeinfo->tm_hour;
        mins = timeinfo->tm_min;
        secs = timeinfo->tm_sec;

        char message[9];
        sprintf(message, "%02d:%02d:%02d", hours, mins, secs);
        zmq_send(publisher, message, strlen(message), 0);
        
        //printf("%s\n", message);
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);

    printf("\nServer stopped\n");
    return 0;
}