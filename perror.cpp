#include "perror.h"

int perr(){

    char * msg = strerror(errno);
    printf("%s\n",msg);
    return 0;
}
