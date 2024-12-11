#include "Command.h"

namespace engine
{

  Command::Command() : typeId(CMDTypeId::SETUP_GAME) {}
  Command::~Command() = default;

  CMDTypeId Command::getCMDTypeId()
  {
    return typeId;
  }

  void Command::setNewCMD(CMDTypeId cmd)
  {
    typeId = cmd;
  }

}
