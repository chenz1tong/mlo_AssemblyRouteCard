#include "DWGToXlsxConfig.h"

void DWGToXlsxConfig::getItems()
{
    XLSXLocations item;
    auto cells = m_JsonControl["relatedLocations"];
    for (auto cell : cells) {
        item.propertyName = cell["property"].get<string>();
        item.toCell = cell["to"].get<string>();
        m_items.insert(std::make_pair(item.propertyName, item.toCell));

    }
}

std::map<string, string> DWGToXlsxConfig::getCellsPos()
{
    return m_items;
}
