#pragma once

#include "Tool.h"
#include "PaintTool.h"
#include "Layer.h"
#include "EPProject.h"
class ToolsManager
{
public :
	ToolsManager(EPProject* p_epproject);
	~ToolsManager();
	Tool* getSelectedTool();

private :
	std::vector<Tool*> m_tools;
	Tool* m_selectedTool;
	
	EPProject* m_epproject;
};
