#include "string.h"
#include "zmq.h"
#include "assert.h"

int main (int argc, char *argv [])
{
    //  Socket to talk to server
    printf ("Collecting updates from weather server…\n");
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, "tcp://localhost:5556");
    assert (rc == 0);

    char *filter = (argc > 1)? argv [1]: "1";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,
                         filter, strlen (filter));
    assert (rc == 0);

    //  Process 100 updates
    int update_nbr;
    long total_temp = 0;
    char ret_val[100] = {0};
    int ret_len = 0;
    for (update_nbr = 0; update_nbr < 1000; update_nbr++) {
        ret_len = zmq_recv (subscriber, ret_val, 100, 0);
        ret_val[ret_len] = 0;
        printf("msg from server: %s\n", ret_val);
    }
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}
