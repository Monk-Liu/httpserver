#include "main.h"
int main(int argc, char **argv){

    if(argc==3){
        MyServer s(atoi(argv[2]), argv[1]);
        string rbuff;
        //MyThreadPool mtp(10);
        HttpHandler * hd;
        MySocket* sfd;
        vector<MySocket*> sfdlist;
        while(1){
            sfdlist = s.selectaccept();
            for(int i=0; i<sfdlist.size(); i++){
                sfd = sfdlist[i];
                sfd->myread(rbuff);
                HttpHandler hdnopool(sfd,rbuff);
                hdnopool.run();
                rbuff.clear();
            }
            //sfd = s.myaccept();
            /*if(sfd && sfd>=0){
                sfd->myread(rbuff);
                //hd = new HttpHandler(sfd, rbuff);
                //mtp.addtask(hd);
                hd->run();
                rbuff.clear();
            }*/
        }
    }
    return 0;
}
