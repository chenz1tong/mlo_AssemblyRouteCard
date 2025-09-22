
#include "DWGPosConfig.h"
#include <fstream>

//bool DWGPosConfig::loadFile(const char*path)
//{
//    //m_path = path;
//    std::ifstream ifs(path, std::fstream::in);
//
//    if (ifs.fail())
//    {
//        return false;
//    }
//
//    ifs >> m_JsonControl;
//    return true;
//}
void DWGPosConfig::getItems()
{
    //DWGPosItems items;
    //double s=m_JsonControl["CustomerVersion"]["left"]/*.get<double>()*/;

     //string s = m_JsonControl["CustomerDwgSn"]["left"];
     items.CustomerDwgSn.right = m_JsonControl["CustomerDwgSn"]["right"];
     items.CustomerDwgSn.top = m_JsonControl["CustomerDwgSn"]["top"];
     items.CustomerDwgSn.bottom = m_JsonControl["CustomerDwgSn"]["bottom"]; 

    items.customVersion.left = m_JsonControl["CustomerVersion"]["left"].get<float>();
    items.customVersion.right = m_JsonControl["CustomerVersion"]["right"];
    items.customVersion.top = m_JsonControl["CustomerVersion"]["top"];
    items.customVersion.bottom = m_JsonControl["CustomerVersion"]["bottom"];



  items.material.left = m_JsonControl["Material"]["left"];
  items.material.right = m_JsonControl["Material"]["right"];
  items.material.top = m_JsonControl["Material"]["top"];
  items.material.bottom = m_JsonControl["Material"]["bottom"];

     items.partName.left = m_JsonControl["PartName"]["left"];
    items.partName.right = m_JsonControl["PartName"]["right"];
      items.partName.top = m_JsonControl["PartName"]["top"];
   items.partName.bottom = m_JsonControl["PartName"]["bottom"];

    items.projectName.left = m_JsonControl["projectName"]["left"];
   items.projectName.right = m_JsonControl["projectName"]["right"];
     items.projectName.top = m_JsonControl["projectName"]["top"];
  items.projectName.bottom = m_JsonControl["projectName"]["bottom"];


    items.dwgVersion.left = m_JsonControl["DwgVersion"]["left"];
   items.dwgVersion.right = m_JsonControl["DwgVersion"]["right"];
     items.dwgVersion.top = m_JsonControl["DwgVersion"]["top"];
  items.dwgVersion.bottom = m_JsonControl["DwgVersion"]["bottom"];

   items.objectSn.left = m_JsonControl["ObjectSn"]["left"];
   items.objectSn.right = m_JsonControl["ObjectSn"]["right"];
   items.objectSn.top = m_JsonControl["ObjectSn"]["top"];
   items.objectSn.bottom = m_JsonControl["ObjectSn"]["bottom"];

    items.CA.left = m_JsonControl["CA"]["left"];
   items.CA.right = m_JsonControl["CA"]["right"];
     items.CA.top = m_JsonControl["CA"]["top"];
  items.CA.bottom = m_JsonControl["CA"]["bottom"];

  //  items.R.left = m_JsonControl["R"]["left"];
  // items.R.right = m_JsonControl["R"]["right"];
  //   items.R.top = m_JsonControl["R"]["top"];
  //items.R.bottom = m_JsonControl["R"]["bottom"];
}
DWGPosItems DWGPosConfig::getDWGPos()
{   
    return items;
}
DWGPosConfig::~DWGPosConfig()
{
}
DWGPosConfig::DWGPosConfig() {
    //loadFile(fileName);
    //getItems();
}


