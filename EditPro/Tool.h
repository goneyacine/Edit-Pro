#pragma once
#include <qevent.h>
#include "EPProject.h"
#include "Vectors.h"
class Tool
{
public :
	Tool(EPProject* p_epproject);
	virtual void onMouseDrag(QMouseEvent* p_event, EP::Vector2 p_mouseRelativePosition);
	virtual void onMousePress(QMouseEvent* p_event, EP::Vector2 p_mouseRelativePosition);
	virtual void onMouseRelease(QMouseEvent* p_event, EP::Vector2 p_mouseRelativePosition);
	virtual void onMouseWheel(QWheelEvent* p_event);

protected:
	EPProject* m_epproject;
};