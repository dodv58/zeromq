#include "zmq.h"
#include "time.h"
#include "sys/time.h"

int main (void)
{
    //  Prepare our context and socket
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    zmq_bind (receiver, "tcp://*:5558");

    //  Wait for start of batch
    char string[100] = {0};
    int len = 0;
    len = zmq_recv (receiver, string, 100, 0);

    struct timeval tv;
    gettimeofday (&tv, NULL);
    int64_t start = (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);

    //  Process 100 confirmations
    int task_nbr;
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        len = zmq_recv (receiver, string, 100, 0);
        if ((task_nbr / 10) * 10 == task_nbr)
            printf (":");
        else
            printf (".");
        fflush (stdout);
    }
    //  Calculate and report duration of batch
    gettimeofday(&tv, NULL);
    int64_t end = (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);

    printf ("Total elapsed time: %lld msec\n", end - start);

    zmq_close (receiver);
    zmq_ctx_destroy (context);
    return 0;
}
