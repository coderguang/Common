#ifndef _COMMON_NET_WINSOCKET_WINSOCKET_H_
#define _COMMON_NET_WINSOCKET_WINSOCKET_H_

#if defined(WINSOCK_EXPORTS)&&(defined(WIN32)||defined(WIN64))
#define WINSOCK_DLL_API _declspec(dllexport)
#elif !defined(_LIB)&&(defined(WIN32)||defined(WIN64))&&!defined(_USRDLL)
#define WINSOCK_DLL_API _declspec(dllimport)
#endif

#include <WinSock2.h>
#include <string>

#include "../util/FuncPtr.h"

using namespace GCommon::GUtil;

namespace GCommon{
  namespace GNet{
    namespace GSocket{

#pragma comment(lib,"ws2_32.lib")


#ifdef WINSOCK_DLL_API
  class WINSOCK_DLL_API CWinSocket{
#else
  class CWinSocket{
#endif

public:
  CWinSocket(char* host, int port, int family, int protocol, int sockType);
  virtual ~CWinSocket();
  void init(voFuncStr *newData);
  void sendMsg(std::string msg);
  void close();
protected:
  void initSocket(char *host, int port, int family, int protocol, int sockType);
  std::string& getClassName();

private:
  CWinSocket(CWinSocket&) = delete;
  CWinSocket operator = (CWinSocket &) = delete;

  WORD mVersion;
  WSADATA wsaData;//WSADATA结构被用来保存AfxSocketInit函数返回的WindowsSockets初始化信息。
  SOCKET clientfd;
  struct sockaddr_in servaddr;
  bool isClosed;//是否主动关闭了socket
  voFuncIntStr *newDatas;//暂时不接数据，只发数据

  std::string className;

};

  }
}
}


#endif
