#pragma once

namespace EP
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(double p_value);
		Vector2(double p_x, double p_y);
		double x, y;
	};

	class Vector3
	{
	public:
		Vector3();
		Vector3(double p_value);
		Vector3(double p_x, double p_y, double p_z);

		double x, y, z;
	};
	class Vector4
	{
	public :
		Vector4();
		Vector4(double p_value);
		Vector4(double p_x,double p_y,double p_z,double p_w);

		double x, y, z, w;
	};
}