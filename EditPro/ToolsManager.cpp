#include "ToolsManager.h"


ToolsManager::ToolsManager(EPProject* p_epproject) : m_epproject(p_epproject)
{
	m_tools.push_back(new PaintTool(m_epproject));
	m_selectedTool = m_tools[0];
}

ToolsManager::~ToolsManager()
{

}

Tool* ToolsManager::getSelectedTool()
{
	return m_selectedTool;
}
