#include "opennurbs.h"

ON_3dPoint::ON_3dPoint(){}
const ON_3dPoint ON_3dPoint::Origin(0.0,0.0,0.0);
ON_3dPoint::ON_3dPoint(double xx,double yy,double zz)
{x=xx;y=yy;z=zz;}
void ON_3dPoint::Transform( const ON_Xform& xform )
{
	double xx,yy,zz,ww;
	if ( xform.m_xform ) {
		ww = xform.m_xform[3][0]*x + xform.m_xform[3][1]*y + xform.m_xform[3][2]*z + xform.m_xform[3][3];
		if ( ww != 0.0 )
			ww = 1.0/ww;
		xx = ww*(xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][2]*z + xform.m_xform[0][3]);
		yy = ww*(xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][2]*z + xform.m_xform[1][3]);
		zz = ww*(xform.m_xform[2][0]*x + xform.m_xform[2][1]*y + xform.m_xform[2][2]*z + xform.m_xform[2][3]);
		x = xx;
		y = yy;
		z = zz;
	}
}

void ON_3dPoint::Zero()
{
	x = y = z = 0.0;
}
double ON_3dPoint::DistanceTo( const ON_3dPoint& p ) const
{
	return ON_3dVector::ON_Length3d(p.x-x,p.y-y,p.z-z);
}
string ON_3dPoint::ToString() const{
	string str="";char X[20];char Y[20];char Z[20];
	sprintf_s(X,"%f",x);
	sprintf_s(Y,"%f",y);
	sprintf_s(Z,"%f",z);
	str+=X;str+="/";str+=Y;str+="/";str+=Z;
	return str;
}
bool ON_3dPoint::IsValid() const
{
  return (ON_IS_VALID(x) && ON_IS_VALID(y) && ON_IS_VALID(z) ) ? true : false;
}
int ON_3dPoint::MaximumCoordinateIndex() const
{
  return (fabs(y)>fabs(x)) ? ((fabs(z)>fabs(y))?2:1) : ((fabs(z)>fabs(x))?2:0);
}

double ON_3dPoint::MaximumCoordinate() const
{
  double c = fabs(x); if (fabs(y)>c) c=fabs(y); if (fabs(z)>c) c=fabs(z);
  return c;
}

int ON_3dPoint::MinimumCoordinateIndex() const
{
  return (fabs(y)<fabs(x)) ? ((fabs(z)<fabs(y))?2:1) : ((fabs(z)<fabs(x))?2:0);
}

double ON_3dPoint::MinimumCoordinate() const
{
  double c = fabs(x); if (fabs(y)<c) c=fabs(y); if (fabs(z)<c) c=fabs(z);
  return c;
}
////////////////////////////////////////////////////////
ON_3dPoint ON_3dPoint::operator+( const ON_3dPoint& p ) const
{
	return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dPoint ON_3dPoint::operator+( const ON_3dVector& v ) const
{
	return ON_3dPoint(x+v.x,y+v.y,z+v.z);
}

ON_3dVector ON_3dPoint::operator-( const ON_3dPoint& p ) const
{
	return ON_3dVector(x-p.x,y-p.y,z-p.z);
}

ON_3dPoint ON_3dPoint::operator-( const ON_3dVector& v ) const
{
	return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}

double ON_3dPoint::operator*(const ON_3dPoint& h) const
{
	return x*h.x + y*h.y + z*h.z;
}

double ON_3dPoint::operator*(const ON_3dVector& h) const
{
	return x*h.x + y*h.y + z*h.z;
}
ON_3dPoint ON_3dPoint::operator*( const ON_Xform& xform ) const
{
	const double px = x; // optimizer should put px,py,pz in registers
	const double py = y;
	const double pz = z;
	double hx[3], w;
	const double* m = &xform.m_xform[0][0];
	hx[0] = m[0]*px + m[4]*py + m[ 8]*pz + m[12];
	hx[1] = m[1]*px + m[5]*py + m[ 9]*pz + m[13];
	hx[2] = m[2]*px + m[6]*py + m[10]*pz + m[14];
	w     = m[3]*px + m[7]*py + m[11]*pz + m[15];
	w = (w != 0.0) ? 1.0/w : 1.0;
	return ON_3dPoint( w*hx[0], w*hx[1], w*hx[2] );
}


ON_3dPoint& ON_3dPoint::operator=(const ON_3dVector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
ON_3dPoint& ON_3dPoint::operator=(const ON_3dPoint& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
ON_3dPoint& ON_3dPoint::operator*=(double d)
{
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

ON_3dPoint& ON_3dPoint::operator/=(double d)
{
	const double one_over_d = 1.0/d;
	x *= one_over_d;
	y *= one_over_d;
	z *= one_over_d;
	return *this;
}

ON_3dPoint& ON_3dPoint::operator+=(const ON_3dPoint& p)
{
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}

ON_3dPoint& ON_3dPoint::operator+=(const ON_3dVector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

ON_3dPoint& ON_3dPoint::operator-=(const ON_3dPoint& p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}

ON_3dPoint& ON_3dPoint::operator-=(const ON_3dVector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
ON_3dPoint ON_3dPoint::operator*( double d ) const
{
	return ON_3dPoint(x*d,y*d,z*d);
}
ON_3dPoint ON_3dPoint::operator/( double d ) const
{
	const double one_over_d = 1.0/d;
	return ON_3dPoint(x*one_over_d,y*one_over_d,z*one_over_d);
}

bool ON_3dPoint::operator==( const ON_3dVector& v ) const
{
  return (x==v.x&&y==v.y&&z==v.z)?true:false;
}
bool ON_3dPoint::operator==( const ON_3dPoint& p ) const
{
  return (x==p.x&&y==p.y&&z==p.z)?true:false;
}
bool ON_3dPoint::operator!=( const ON_3dPoint& p ) const
{
  return (x!=p.x||y!=p.y||z!=p.z)?true:false;
}
///////////////////////////////////////////////////////////
double ON_3dPoint::CrossProduct(const ON_3dPoint& A, const ON_3dPoint& B,const ON_3dPoint& C)
{
	return (((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y)));
}
double ON_3dPoint::DotProduct(const ON_3dPoint& A, const ON_3dPoint& B, const ON_3dPoint& C)
{
	return (((B.x - A.x) * (C.y - A.y)) + ((B.y - A.y) * (C.y - A.y)));
}
bool ON_3dPoint::OrthoClose(const ON_3dPoint& Point1,const ON_3dPoint& Point2, double t)
{
	return (((fabs((double) (Point1.x - Point2.x)) < t) && (fabs((double) (Point1.y - Point2.y)) < t)) && (fabs((double) (Point1.z - Point2.z)) < t));
}




