#include "string.h"
#include "zmq.h"
#include "assert.h"
#include "stdlib.h"
#include "unistd.h"

int main (void)
{
    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert (rc == 0);
    printf("Starting publish ...\n");
    while (1) {
        //  Send message to all subscribers
        char update [100];
        sprintf (update, "%d Hello from server", rand() % 3 + 1);
        printf("Sending: %s\n", update);
        zmq_send (publisher, update, strlen(update), 0);
        sleep(2);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
