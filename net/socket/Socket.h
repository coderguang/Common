#ifndef _COMMON_NET_SOCKET_SOCKET_H_
#define _COMMON_NET_SOCKET_SOCKET_H_

#include "SocketBase.h"
#include "../../util/FuncPtr.h"
#include <map>
#include <string.h>

namespace GCommon{
  namespace GNet{
    namespace GSocket{

using namespace GCommon::GUtil;

static const int MAX_BUF_SIZE=10240;//the socket read and write buf size
static const int MAX_USER_SIZE=99999;

enum IOType{IOSelect,IOPoll,IOEpoll};


class CSocket{
  public:
    CSocket(IOType type,int family,int sockType,int protocol,int port,int backlog);
   
    virtual ~CSocket();
    
    void init(voFuncIntStr *newConnect,voFuncIntCharptr *newData,voFuncInt *disconnect,voFuncIntInt *except);

    void send(int sockfd,char *buf);
   
    void close(int sockfd);

    int getCounter(){
      return counter;
    }
  
  protected:
    void selectLoop();
    
    void pollLoop();
 
    void epollLoop();

  private:
    CSocket(CSocket&)=delete;
    CSocket operator=(CSocket&)=delete;

    IOType ioType;

    //socket common variable
    int listenfd;
    int connfd;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
  
    //data buf
    char buf[MAX_BUF_SIZE];
    
    int counter;//the sockfd counter

    
    std::map<int,int> sockfdMap;

    int maxIndex;//use for select and poll

    fd_set rset,allset;//use for select mode
   
    int sclient[FD_SETSIZE];//use for select mode
    
    struct pollfd eclient[MAX_USER_SIZE];//use for poll mode
    
    int epfd;
    struct epoll_event *events;//use for epoll mode 
    struct epoll_event ev;//use for epoll mode
   
    voFuncIntStr *newConnects;
    voFuncIntCharptr *newDatas;
    voFuncInt *disconnects;
    voFuncIntInt *excepts;

};


    }
  }
}
#endif