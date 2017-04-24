#include "main.h"
int main(int argc, char **argv){

    if(argc==3){
        MyServer s(atoi(argv[2]), argv[1]);
        MySocket* sfd;
        string rbuff;
        while(1){
            sfd = s.myaccept();
            if(sfd && sfd>=0){
                int i=0;
                sfd->myread(rbuff);
                //cout<<rbuff<<endl;
                HttpHandler(sfd, rbuff);
                rbuff.clear();
                delete sfd;
            }else{
                printf("---------------------->Error with sfd[%d]\n",sfd);
            }
        }
    }
    return 0;
}
