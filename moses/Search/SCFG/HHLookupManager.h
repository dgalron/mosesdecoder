#pragma once

namespace Moses
{
class HHInputPathSCFG;

class HHLookupManager
{
public:
  void Lookup(HHInputPathSCFG &path);
};



class HHLookupManagerMemory : public HHLookupManager
{

};

}

