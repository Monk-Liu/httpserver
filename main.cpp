#include "main.h"
int main(int argc, char **argv){

    if(argc==3){
        MyServer s(atoi(argv[2]), argv[1]);
        MySocket* sfd;
        string rbuff;
        MyThreadPool mtp(10);
        HttpHandler * hd;
        while(1){
            sfd = s.myaccept();
            if(sfd && sfd>=0){
                int i=0;
                sfd->myread(rbuff);
                //cout<<rbuff<<endl;
                hd = new HttpHandler(sfd, rbuff);
                mtp.addtask(hd);
                //hd->run();
                rbuff.clear();
            }else{
                printf("---------------------->Error with sfd[%d]\n",sfd);
            }
        }
    }
    return 0;
}
