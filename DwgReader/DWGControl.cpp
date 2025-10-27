#include "DWGControl.h"
#include <mutex>
#include "FormatHandle.h"
#include "Bridge.h"
DWGControl* DWGControl::self = nullptr;
DWGControl::DWGControl()
{
	
}
DWGControl::~DWGControl()
{
}


bool DWGControl::loadDWG(const char* fileName)
{
	//memset(&dwg, 0, sizeof(Dwg_Data));
	//int error = dwg_read_file(fileName, &dwg);
	//if (error >= DWG_ERR_CRITICAL) {
	//	//std::cerr << "Error reading DWG file: " << filename << std::endl;
	//	return false;
	//}
	return Bridge::getInstance()->loadDWG(fileName);
	//DWGBridge::simpleRead(string(fileName));
	//Dwg_Object_Ref* refs = dwg_model_space_ref(&dwg);
	////Dwg_Entity_MTEXT** texts = dwg_getall_MTEXT(refs);
	//for (BITCODE_BL i = 0; i < dwg.num_objects; i++) {
	//	if (dwg.object[i].type == DWG_TYPE_MTEXT) {
	//		Dwg_Entity_MTEXT* text = dwg.object[i].tio.entity->tio.MTEXT;
	//		int ssssa= strlen(text->text);
	//		char* s = text->text;
	//		string ss = GB2312ToUTF8(text->text);
	//		
	////		FormatHandle::OutputToDebugWindow(ss);/*
	//		double x = text->ins_pt.x;
	//		double y = text->ins_pt.y;
	//		FormatHandle::OutputToDebugWindow(FormatHandle::StringToUTF8("   "));
	//		FormatHandle::OutputToDebugWindow(FormatHandle::StringToUTF8(std::to_string( x)));
	//		FormatHandle::OutputToDebugWindow(FormatHandle::StringToUTF8("   "));
	//		FormatHandle::OutputToDebugWindow(FormatHandle::StringToUTF8(std::to_string( y)));*/

	
	
	//	//else if (dwg.object[i].type == DWG_TYPE_MLEADEROBJECTCONTEXTDATA) {
	//	//	Dwg_Entity_MLEADER* mleader = dwg.object[i].tio.entity->tio.MLEADER;
	//	//	if (mleader->content.type == DWG_MLEADER_CONTENT_MTEXT) {
	//	//		Dwg_MLEADER_Content_MText* mtext = &mleader->content.mtext;
	//	//		const char* textContent = mtext->default_text;
	//	//}
	//}
	//return true;
}
std::string DWGControl::ConvertToUTF8(const std::string& input, UINT codepage) {
	int requiredSize = MultiByteToWideChar(codepage, 0, input.c_str(), -1, nullptr, 0);
	std::wstring utf16Str(requiredSize, L'\0');
	MultiByteToWideChar(codepage, 0, input.c_str(), -1, &utf16Str[0], requiredSize);

	requiredSize = WideCharToMultiByte(CP_UTF8, 0, &utf16Str[0], -1, nullptr, 0, nullptr, nullptr);
	std::string utf8Str(requiredSize, '\0');
	WideCharToMultiByte(CP_UTF8, 0, &utf16Str[0], -1, &utf8Str[0], requiredSize, nullptr, nullptr);

	return utf8Str;
}
std::string DWGControl::CharToUTF8(char* input, UINT codepage) {
	if (!input) return "";

	// 计算需要的宽字符数
	int utf16_len = MultiByteToWideChar(codepage, 0, input, -1, nullptr, 0);
	if (utf16_len <= 0) return "";

	wchar_t* utf16_str = new wchar_t[utf16_len];
	MultiByteToWideChar(codepage, 0, input, -1, utf16_str, utf16_len);

	// 计算 UTF-8 编码的长度
	int utf8_len = WideCharToMultiByte(CP_UTF8, 0, utf16_str, -1, nullptr, 0, nullptr, nullptr);
	if (utf8_len <= 0) {
		delete[] utf16_str;
		return "";
	}

	char* utf8_str = new char[utf8_len];
	WideCharToMultiByte(CP_UTF8, 0, utf16_str, -1, utf8_str, utf8_len, nullptr, nullptr);

	std::string result(utf8_str);
	delete[] utf16_str;
	delete[] utf8_str;

	return result;
}
std::string DWGControl::GB2312ToUTF8(const char* gb2312Str) {
	if (gb2312Str == nullptr) {
		return "";
	}

	// 首先将 GB2312 编码转换为 UTF-16 编码
	int utf16Length = MultiByteToWideChar(936, 0, gb2312Str, -1, nullptr, 0);
	if (utf16Length <= 0) {
		return "";
	}

	wchar_t* utf16Str = new wchar_t[utf16Length];
	MultiByteToWideChar(936, 0, gb2312Str, -1, utf16Str, utf16Length);

	// 然后将 UTF-16 编码转换为 UTF-8 编码
	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, utf16Str, -1, nullptr, 0, nullptr, nullptr);
	if (utf8Length <= 0) {
		delete[] utf16Str;
		return "";
	}

	char* utf8Str = new char[utf8Length];
	WideCharToMultiByte(CP_UTF8, 0, utf16Str, -1, utf8Str, utf8Length, nullptr, nullptr);

	std::string utf8Result(utf8Str);
	delete[] utf16Str;
	delete[] utf8Str;

	return utf8Result;
}
//Dwg_Entity_VIEWPORT** DWGControl::getViewPort()
//{
//	Dwg_Entity_VIEWPORT** ports = dwg_getall_VIEWPORT(dwg_model_space_ref(&dwg));
//
//	if (ports) {
//		//for (BITCODE_BL j = 0; j < ports[0]->num_frozen_layers; j++) {
//		//	Dwg_Object* viewport_entity = viewport->entities[j];
//		//	print_text_entity(viewport_entity);
//		//}
//		return ports;
//	}
//	Dwg_Entity_TEXT** ts= dwg_getall_TEXT(dwg_model_space_ref(&dwg));
//   return nullptr;
//}
//Dwg_Entity_MTEXT** DWGControl::getAllText()
//{
//	Dwg_Object_Ref* refs = dwg_model_space_ref(&dwg);
//	Dwg_Entity_MTEXT** texts = dwg_getall_MTEXT(refs);
//	if (texts) {
//		return texts;
//	}
//	return nullptr;
//}
//Dwg_Entity_DIMENSION_LINEAR** DWGControl::getAllLNDimension() {
//	Dwg_Object_Ref* refs = dwg_model_space_ref(&dwg);
//
//	Dwg_Entity_DIMENSION_LINEAR**  dimension= dwg_getall_DIMENSION_LINEAR(refs);
//	if (dimension) {
//		return dimension;
//	}
//	return nullptr;
//}
//Dwg_Entity_DIMENSION_RADIUS** DWGControl::getAllRadiusDimension() {
//	Dwg_Object_Ref* refs = dwg_model_space_ref(&dwg);
//	Dwg_Entity_DIMENSION_RADIUS** dimension = dwg_getall_DIMENSION_RADIUS(refs);
//	if (dimension) {
//		return dimension;
//	}
//	return nullptr;
//}
 DWGControl* DWGControl::getInstance()
{
	//mutex.lock();
	if (self == nullptr)
		self = new DWGControl();
	//mutex.unlock();
	return self;
}
 std::map<string, string> DWGControl::getCSharpMap()
 {
	 std::map<string, string> re= Bridge::getInstance()->getAll();
	 std::map<string, string>::iterator it;
	 for (it = re.begin(); it != re.end(); it++) {
		 FormatHandle::OutputToDebugWindow(it->first);
		 FormatHandle::OutputToDebugWindow("\n");
		 FormatHandle::OutputToDebugWindow(it->second);

	 }
	 return re;
 }
//BITCODE_3BD DWGControl::getPartNamePos() {
//	BITCODE_3BD portsPos = getViewPort()[0]->center;
//
//	BITCODE_3BD pos;
//	pos.x = portsPos.x + m_standardData.viewPartRelX;
//	pos.y = portsPos.y + m_standardData.viewPartRelY;
//	pos.z=portsPos.z;
//	return pos;
//}


