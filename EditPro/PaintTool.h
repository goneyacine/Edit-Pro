#pragma once

#include "Tool.h"
#include <iostream>
#include <vector>
#include "Brush.h"
#include "Vectors.h"

class PaintTool : public Tool
{
public:

	PaintTool(EPProject* p_epproject);
	~PaintTool();

	void onMouseDrag(QMouseEvent* p_event, EP::Vector2 p_mouseRelativePosition) override;
	void onMousePress(QMouseEvent* p_event, EP::Vector2 p_mouseRelativePosition) override;
	void onMouseRelease(QMouseEvent* p_event, EP::Vector2 p_mouseRelativePosition) override;
	void onMouseWheel(QWheelEvent* p_event) override;
private:
	void paint(EP::Vector2 p_paintPosition);
	void loadBrushs();

	std::vector<Brush> m_brushs;
	Brush m_selectedBrush;
};