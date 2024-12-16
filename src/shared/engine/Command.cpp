#include "Command.h"

namespace engine
{
  Command::Command() {}
  CMDTypeId Command::getCMDTypeId()
  {
    return typeId;
  }

  void Command::setNewCMD(CMDTypeId cmd)
  {
    typeId = cmd;
  }
  Command::~Command() {
    
  }

}
