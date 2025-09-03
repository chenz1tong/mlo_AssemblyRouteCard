#include "DWGControl.h"

DWGControl::DWGControl()
{
}
DWGControl::~DWGControl()
{
}
bool DWGControl::loadDWG(const char* fileName)
{
	memset(&dwg, 0, sizeof(Dwg_Data));
	int error = dwg_read_file(fileName, &dwg);
	if (error >= DWG_ERR_CRITICAL) {
		//std::cerr << "Error reading DWG file: " << filename << std::endl;
		return false;
	}
	return true;
}

Dwg_Entity_VIEWPORT** DWGControl::getViewPort()
{
	Dwg_Entity_VIEWPORT** ports = dwg_getall_VIEWPORT(dwg_model_space_ref(&dwg));
	if (ports) {
		return ports;
	}
   return nullptr;
}
Dwg_Entity_TEXT** DWGControl::getAllText()
{
	Dwg_Entity_TEXT** texts = dwg_getall_TEXT(dwg_model_space_ref(&dwg));
	if (texts) {
		return texts;
	}
	return nullptr;
}
string DWGControl::getTextInNeed()
{

	return string();
}
BITCODE_3BD DWGControl::getPartNamePos() {
	BITCODE_3BD portsPos = getViewPort()[0]->center;

	BITCODE_3BD pos;
	pos.x = portsPos.x + m_standardData.viewPartRelX;
	pos.y = portsPos.y + m_standardData.viewPartRelY;
	pos.z=portsPos.z;
	return pos;
}


