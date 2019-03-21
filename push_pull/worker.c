#include "zmq.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"

int main (void)
{
    //  Socket to receive messages on
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    zmq_connect (receiver, "tcp://localhost:5557");

    //  Socket to send messages to
    void *sender = zmq_socket (context, ZMQ_PUSH);
    zmq_connect (sender, "tcp://localhost:5558");

    //  Process tasks forever
    char string[100] = {0};
    int len = 0;
    while (1) {
        len = zmq_recv (receiver, string, 100, 0);
        string[len] = '\0';
        printf ("%s.", string);     //  Show progress
        fflush (stdout);
        usleep (atoi (string) * 1000);    //  Do the work
        zmq_send (sender, "", 0, 0);        //  Send results to sink
    }
    zmq_close (receiver);
    zmq_close (sender);
    zmq_ctx_destroy (context);
    return 0;
}
