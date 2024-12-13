#include "Command.h"

namespace engine
{

  CMDTypeId Command::getCMDTypeId()
  {
    return typeId;
  }

  void Command::setNewCMD(CMDTypeId cmd)
  {
    typeId = cmd;
  }

}
