#ifndef _COMMON_LOG_LOG_H_
#define _COMMON_LOG_LOG_H_

#include <string>
#include <iostream>

namespace GCommon{
  namespace GLog{

class GLog{
  public:
    static void Log(std::string& msg,std::string type="default"){
		std::cout<<"type="<<type<<",msg="<<msg<<std::endl;
	
	}
	  




};

  }
}

#endif