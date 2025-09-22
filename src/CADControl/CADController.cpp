#include "CADController.h"
#include <mutex>
#include <dwg_api.h>
#include <dwg.h>
CADController* CADController::instance = nullptr;
CADController* CADController::getInstance()
{
	std::mutex mutex;
	mutex.lock();
	if (instance == nullptr)
		instance = new CADController();
		mutex.unlock();
		return instance;
}

string CADController::getPartName()
{
	return m_partName;
}

string CADController::getPaperSN()
{
	return m_dwgSn;
}

string CADController::getPartSN()
{
	return m_objectSn;
}

string CADController::getCustomerVersion()
{
	return m_customVersion;
}

string CADController::getPaperVersion()
{
	return m_dwgVersion;
}

string CADController::getVersion()
{
	return m_customVersion+ m_dwgVersion;
}

string CADController::getProjectName()
{
	return m_projectName;
}

string CADController::getMaterial()
{
	return m_material;
}

std::map<string,string> CADController::getAllTexts()
{
	std::map<string,string> mapText=getTextInNeed();
	std::map<string, string> mapdimension1 = getDimensionRadiusText();
	std::map<string, string> mapdimension2 = getDimensionLNText();
	mapdimension1.insert(mapdimension2.begin(), mapdimension2.end());
	mapText.insert(mapdimension1.begin(), mapdimension1.end());
	return mapText;
}
string CADController::handleDiameter(string str) {
	size_t pos1 = str.find("{");
	string str11 = str.substr(0, pos1);
	size_t pos = str.find("S");
	size_t pos2 = str.find("^");
	string str1 = str.substr(pos+1, pos2-pos-1);
	str.pop_back();
	str.pop_back();
	return str11+"," +str1 +"/" + str.substr(pos2 + 1);
}
string CADController::handleThick(string str)
{
	size_t pos = str.find("%");
	size_t pos2 = str.find("P");
	string str1 = str.substr(0, pos);
	return str1+","+str.substr(pos2+1);
}
bool CADController::getView()
{
	Dwg_Entity_VIEWPORT** op= DWGControl::getInstance()->getViewPort();
	if (op == nullptr)
		return false;
	return true;
}
bool CADController::initRead(const char* fileName)
{

	return DWGControl::getInstance()->loadDWG(fileName);
}
void CADController::initData()
{
	return loadData();
}
void CADController::loadData()
{
	m_standardData = SystemConfigModel::getInstance()->getDWGPos();
}
std::map<string, string> CADController::getDimensionLNText() {
	Dwg_Entity_DIMENSION_LINEAR** texts = DWGControl::getInstance()->getAllLNDimension();
	Dwg_Entity_VIEWPORT* vp = DWGControl::getInstance()->getViewPort()[0];
	BITCODE_3BD viewPort = DWGControl::getInstance()->getViewPort()[0]->center;
	int i = 0;
	double diameterX,diameterY;
	map<string, string> _map;
	while (texts[i]) {
		Dwg_Entity_DIMENSION_LINEAR* ts = texts[i];
		if (texts[i]->def_pt.x< viewPort.x + vp->width / 2 && texts[i]->def_pt.x > viewPort.x - vp->width / 2 &&
			texts[i]->def_pt.y < viewPort.y + vp->height / 2 && texts[i]->def_pt.y > viewPort.y - vp->height / 2)
		{
			if (abs(texts[i]->xline1_pt.x- texts[i]->xline2_pt.x) < 2) {
				diameterX = texts[i]->def_pt.x;
				diameterY = texts[i]->def_pt.y;
				string str = handleDiameter(texts[i]->user_text);
				_map.insert(std::make_pair("diameter",str ));

			}
		}
		i++;
	}	
	
	vp = DWGControl::getInstance()->getViewPort()[0];
	viewPort = DWGControl::getInstance()->getViewPort()[0]->center;
	i = 0;
	while (texts[i]) {
		if (texts[i]->def_pt.x< viewPort.x + vp->width / 2 && texts[i]->def_pt.x > viewPort.x - vp->width / 2 &&
			texts[i]->def_pt.y < viewPort.y + vp->height / 2 && texts[i]->def_pt.y > viewPort.y - vp->height / 2)
		{
			if (texts[i]->def_pt.y < diameterY) {
				string str = handleThick(texts[i]->user_text);
				_map.insert(std::make_pair("centerThick", str));
			}
		}
			i++;

	}
	return _map;
}
std::map<string, string> CADController::getDimensionRadiusText()
{
	std::map<string,string> _map;
	string str;
	Dwg_Entity_DIMENSION_RADIUS** texts = DWGControl::getInstance()->getAllRadiusDimension();
	Dwg_Entity_VIEWPORT* vp = DWGControl::getInstance()->getViewPort()[0];
	BITCODE_3BD viewPort = DWGControl::getInstance()->getViewPort()[0]->center;
	
	int i = 0;
	string val1 ="999999";
	while (texts[i]) {
		if (texts[i]->def_pt.x< viewPort.x + vp->width / 2 && texts[i]->def_pt.x > viewPort.x - vp->width / 2 &&
			texts[i]->def_pt.y < viewPort.y + vp->height / 2 && texts[i]->def_pt.y > viewPort.y - vp->height / 2) {
			switch (i)
			{
			case 0: str = texts[i]->user_text; break;
			case 1:val1= texts[i]->user_text; break;
			default:
				break;
			}
		}

		i++;
	}
	remove(str.begin(), str.end(), 'R');
	remove(val1.begin(), val1.end(), 'R');
	_map.insert(std::make_pair( "R", "R1:"+str + "," + "R2:"+val1));
	return _map;
}
std::map<string, string> CADController::getTextInNeed()
{
	map<string, string> _map;
	Dwg_Entity_MTEXT** texts =DWGControl::getInstance()-> getAllText();
	BITCODE_3BD viewPort = DWGControl::getInstance()->getViewPort()[0]->center;
	int i = 0;
	string msg = "Get text is:";
	//test
	while (texts[i]) {
		string str1 = texts[i]->text;

		if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.partName.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.partName.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.partName.bottom && texts[i]->ins_pt.y > viewPort.y + m_standardData.partName.top)
		{
			string str = texts[i]->text;
			int index = str.find(';');
			str.pop_back();
			//int endIndex = str.find( '}');
			m_partName = str.substr(index + 1);
			msg = msg + "PartName is " + m_partName + "\n";
			_map.insert(std::make_pair("PartName", m_partName));
		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.projectName.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.projectName.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.projectName.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.projectName.top)
		{
			m_projectName = texts[i]->text;
			msg = msg + "ProjectName is " + m_projectName + "\n";
			_map.insert(std::make_pair("ProjectName", m_projectName));

		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.customVersion.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.customVersion.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.customVersion.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.customVersion.top)
		{
			m_customVersion = texts[i]->text;
			msg = msg + "CustomVersion is " + m_customVersion + "\n";
			_map.insert(std::make_pair("CustomVersion", m_customVersion));
		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.dwgVersion.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.dwgVersion.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.dwgVersion.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.dwgVersion.top)
		{
			m_dwgVersion = texts[i]->text;
			msg = msg + "DWGVersion is " + m_dwgVersion + "\n";
			_map.insert(std::make_pair("DWGVersion", m_dwgVersion));
		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.objectSn.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.objectSn.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.objectSn.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.objectSn.top)
		{
			string str = texts[i]->text;
			if (str.find("Í¼ºÅ") == std::string::npos) {
				m_objectSn = str;
				msg = msg + "ObjectSN is " + m_objectSn + "\n";
				_map.insert(std::make_pair("ObjectSN", m_objectSn));

			}
		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.CA.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.CA.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.CA.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.CA.top)
		{
			m_CANum++;
			string ca2="999999",ca1;
			ca1 = texts[i]->text;
			switch (m_CANum)
			{
			case 1:	ca1 = texts[i]->text; break;

			case 2: {ca2 = texts[i]->text; m_CANum = 0; break; }
			default:
				break;
			}
			m_CA=ca1 + "," + ca2;

			msg = msg + "CA is " + m_CA + "\n";
			_map.insert(std::make_pair("CA", m_CA));

		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.diameter.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.diameter.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.diameter.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.diameter.top)
		{//Íâ¾¶
			m_ratio = texts[i]->text;
			msg = msg + "m_ratio is " + m_ratio + "\n";
		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.CustomerDwgSn.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.CustomerDwgSn.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.CustomerDwgSn.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.CustomerDwgSn.top)
		{
			string str = texts[i]->text;
			if (str.find("»õºÅ") == std::string::npos) {
				m_CustomerDwgSn = str;
				msg = msg + "CustomerDwgSn is " + m_CustomerDwgSn + "\n";
				_map.insert(std::make_pair("CustomerDwgSn", m_CustomerDwgSn));

			}

		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.material.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.material.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.material.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.material.top)
		{
			string str = texts[i]->text;
			int index = str.find('\\');
			m_material = str.substr(0, index);
			msg = msg + "Material is " + m_material + "\n";
			_map.insert(std::make_pair("Material", m_material));

		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.material.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.material.right &&
			texts[i]->ins_pt.y>viewPort.y + m_standardData.material.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.material.top)
		{
			string str = texts[i]->text;
			int index = str.find('\\');
			m_material = str.substr(0, index);
			msg = msg + "Material is " + m_material + "\n";
			_map.insert(std::make_pair("Material", m_material));

		}
		else if (texts[i]->ins_pt.x > (viewPort.x + m_standardData.material.left) && texts[i]->ins_pt.x< viewPort.x + m_standardData.material.right &&
		texts[i]->ins_pt.y>viewPort.y + m_standardData.material.bottom && texts[i]->ins_pt.y < viewPort.y + m_standardData.material.top)
		{
		string str = texts[i]->text;
		int index = str.find('\\');
		m_material = str.substr(0, index);
		msg = msg + "Material is " + m_material + "\n";
		_map.insert(std::make_pair("Material", m_material));

		}
		i++;
	}
	return _map;
}

CADController::~CADController()
{
}
CADController::CADController()
{
}