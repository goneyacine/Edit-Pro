#include "Vectors.h"

using namespace EP;

Vector2::Vector2() : x(0),y(0)
{
}

Vector2::Vector2(double p_value) : x(p_value),y(p_value)
{
}

Vector2::Vector2(double p_x, double p_y) : x(p_x), y(p_y)
{

}


Vector3::Vector3() : x(0), y(0),z(0)
{
}

Vector3::Vector3(double p_value) : x(p_value), y(p_value),z(p_value)
{
}

Vector3::Vector3(double p_x, double p_y,double p_z) : x(p_x), y(p_y),z(p_z)
{

}


Vector4::Vector4() : x(0), y(0), z(0),w(0)
{
}

Vector4::Vector4(double p_value) : x(p_value), y(p_value), z(p_value),w(p_value)
{
}

Vector4::Vector4(double p_x, double p_y, double p_z,double p_w) : x(p_x), y(p_y), z(p_z),w(p_w)
{

}