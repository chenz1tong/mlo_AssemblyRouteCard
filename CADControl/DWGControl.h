#include <windows.h>
#include <dwg_api.h>
#include <dwg.h>
#include <string>
using namespace std;
struct DWGData {
	BITCODE_BD viewPartRelX = 16.37;
	BITCODE_BD viewPartRelY = 62;
};
class DWGControl
{
public:
	bool loadDWG(const char* fileName);
	Dwg_Entity_VIEWPORT** getViewPort();
	Dwg_Entity_TEXT** getAllText();
	string getTextInNeed();
	BITCODE_3BD getPartNamePos();
private:
	DWGControl();
	~DWGControl();
private:
	Dwg_Data dwg;
	DWGData m_standardData;
	string m_partName, m_projectName, m_material, m_dwgSn, m_customVersion, m_dwgVersion, m_objectSn, m_CA, m_R, m_ratio, m_thick;
};

