#include "opennurbs.h"

ON_3dVector::ON_3dVector()
{}

const ON_3dVector ON_3dVector::ZeroVector(0.0,0.0,0.0);
const ON_3dVector ON_3dVector::XAxis(1.0,0.0,0.0);
const ON_3dVector ON_3dVector::YAxis(0.0,1.0,0.0);
const ON_3dVector ON_3dVector::ZAxis(0.0,0.0,1.0);
string ON_3dVector::ToString() const{
	string str="";char X[20];char Y[20];char Z[20];
	sprintf_s(X,"%f",x);
	sprintf_s(Y,"%f",y);
	sprintf_s(Z,"%f",z);
	str+=X;str+="/";str+=Y;str+="/";str+=Z;
	return str;
}
ON_3dVector::ON_3dVector(double xx,double yy,double zz)
{x=xx;y=yy;z=zz;}
bool ON_3dVector::IsValid() const
{
  return (ON_IS_VALID(x) && ON_IS_VALID(y) && ON_IS_VALID(z) ) ? true : false;
}
void ON_3dVector::Transform( const ON_Xform& xform )
{
	double xx,yy,zz;
	xx = xform.m_xform[0][0]*x + xform.m_xform[0][1]*y + xform.m_xform[0][2]*z;
	yy = xform.m_xform[1][0]*x + xform.m_xform[1][1]*y + xform.m_xform[1][2]*z;
	zz = xform.m_xform[2][0]*x + xform.m_xform[2][1]*y + xform.m_xform[2][2]*z;
	x = xx;
	y = yy;
	z = zz;
}

double ON_3dVector::Length() const
{
	return ON_Length3d(x,y,z);
}
bool ON_3dVector::Unitize()
{
	double d = Length();

	if ( ON_IS_FINITE(d) )
	{
		if ( d > ON_DBL_MIN )
		{
			x /= d;
			y /= d;
			z /= d;
			return true;
		}

		if ( d > 0.0 )
		{
			ON_3dVector tmp;
			tmp.x = x*8.9884656743115795386465259539451e+307;
			tmp.y = y*8.9884656743115795386465259539451e+307;
			tmp.z = z*8.9884656743115795386465259539451e+307;
			d = tmp.Length();
			if ( ON_IS_FINITE(d) && d > ON_DBL_MIN )
			{
				x = tmp.x/d;
				y = tmp.y/d;
				z = tmp.z/d;
				return true;
			}
		}
	}

	x = 0.0;
	y = 0.0;
	z = 0.0;

	return false;
}
void ON_3dVector::Zero()
{
  x = y = z = 0.0;
}
bool ON_3dVector::PerpendicularTo( const ON_3dVector& v )
{
	//bool rc = false;
	int i, j, k; 
	double a, b;
	k = 2;
	if ( fabs(v.y) > fabs(v.x) ) {
		if ( fabs(v.z) > fabs(v.y) ) {
			// |v.z| > |v.y| > |v.x|
			i = 2;
			j = 1;
			k = 0;
			a = v.z;
			b = -v.y;
		}
		else if ( fabs(v.z) >= fabs(v.x) ){
			// |v.y| >= |v.z| >= |v.x|
			i = 1;
			j = 2;
			k = 0;
			a = v.y;
			b = -v.z;
		}
		else {
			// |v.y| > |v.x| > |v.z|
			i = 1;
			j = 0;
			k = 2;
			a = v.y;
			b = -v.x;
		}
	}
	else if ( fabs(v.z) > fabs(v.x) ) {
		// |v.z| > |v.x| >= |v.y|
		i = 2;
		j = 0;
		k = 1;
		a = v.z;
		b = -v.x;
	}
	else if ( fabs(v.z) > fabs(v.y) ) {
		// |v.x| >= |v.z| > |v.y|
		i = 0;
		j = 2;
		k = 1;
		a = v.x;
		b = -v.z;
	}
	else {
		// |v.x| >= |v.y| >= |v.z|
		i = 0;
		j = 1;
		k = 2;
		a = v.x;
		b = -v.y;
	}
	double* this_v = &x;
	this_v[i] = b;
	this_v[j] = a;
	this_v[k] = 0.0;
	return (a != 0.0) ? true : false;
}

bool ON_3dVector::PerpendicularTo( const ON_3dPoint& P0, const ON_3dPoint& P1, const ON_3dPoint& P2)
{
  // Find a the unit normal to a triangle defined by 3 points
  ON_3dVector V0, V1, V2, N0, N1, N2;
  Zero();
  V0 = P2 - P1;
  V1 = P0 - P2;
  V2 = P1 - P0;
  N0 = ON_CrossProduct( V1, V2 );
  if ( !N0.Unitize() )
    return false;
  N1 = ON_CrossProduct( V2, V0 );
  if ( !N1.Unitize() )
    return false;
  N2 = ON_CrossProduct( V0, V1 );
  if ( !N2.Unitize() )
    return false;
  const double s0 = 1.0/V0.Length();
  const double s1 = 1.0/V1.Length();
  const double s2 = 1.0/V2.Length();
  // choose normal with smallest total error
  const double e0 = s0*fabs(ON_3dVector::ON_DotProduct(N0,V0)) + s1*fabs(ON_3dVector::ON_DotProduct(N0,V1)) + s2*fabs(ON_3dVector::ON_DotProduct(N0,V2));
  const double e1 = s0*fabs(ON_3dVector::ON_DotProduct(N1,V0)) + s1*fabs(ON_3dVector::ON_DotProduct(N1,V1)) + s2*fabs(ON_3dVector::ON_DotProduct(N1,V2));
  const double e2 = s0*fabs(ON_3dVector::ON_DotProduct(N2,V0)) + s1*fabs(ON_3dVector::ON_DotProduct(N2,V1)) + s2*fabs(ON_3dVector::ON_DotProduct(N2,V2));

  if ( e0 <= e1 ) {
    if ( e0 <= e2 ) {
      *this = N0;
    }
    else {
      *this = N2;
    }
  }
  else if (e1 <= e2) {
    *this = N1;
  }
  else {
    *this = N2;
  }
  
  return true;
}
double ON_3dVector::LengthSquared() const
{
	return (x*x + y*y + z*z);
}


//////////////////////////////////////////////////////////////////////////////
ON_3dVector ON_3dVector::operator+( const ON_3dVector& v ) const
{
	return ON_3dVector(x+v.x,y+v.y,z+v.z);
}

ON_3dPoint ON_3dVector::operator+( const ON_3dPoint& p ) const
{
	return ON_3dPoint(x+p.x,y+p.y,z+p.z);
}

ON_3dVector ON_3dVector::operator-( const ON_3dVector& v ) const
{
	return ON_3dVector(x-v.x,y-v.y,z-v.z);
}

ON_3dPoint ON_3dVector::operator-( const ON_3dPoint& v ) const
{
	return ON_3dPoint(x-v.x,y-v.y,z-v.z);
}

ON_3dVector ON_3dVector::operator/( double d ) const
{
	const double one_over_d = 1.0/d;
	return ON_3dVector(x*one_over_d,y*one_over_d,z*one_over_d);
}
ON_3dVector ON_3dVector::operator*( double d ) const
{
	return ON_3dVector(x*d,y*d,z*d);
}
ON_3dVector& ON_3dVector::operator-=(const ON_3dVector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
ON_3dVector& ON_3dVector::operator*=(double d)
{
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

ON_3dVector& ON_3dVector::operator/=(double d)
{
	const double one_over_d = 1.0/d;
	x *= one_over_d;
	y *= one_over_d;
	z *= one_over_d;
	return *this;
}

ON_3dVector& ON_3dVector::operator+=(const ON_3dVector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
ON_3dVector& ON_3dVector::operator=(const ON_3dVector& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

ON_3dVector& ON_3dVector::operator=(const ON_3dPoint& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

double ON_3dVector::operator*( const ON_3dPoint& v ) const
{
	return (x*v.x + y*v.y + z*v.z);
}
double ON_3dVector::operator*( const ON_3dVector& v ) const
{
	return (x*v.x + y*v.y + z*v.z);
}
bool ON_3dVector::operator==( const ON_3dVector& v ) const
{
  return (x==v.x&&y==v.y&&z==v.z)?true:false;
}
bool ON_3dVector::operator==( const ON_3dPoint& p ) const
{
  return (x==p.x&&y==p.y&&z==p.z)?true:false;
}
////////////////////////////////////////////////////////////////////////////
ON_3dVector ON_3dVector::ON_CrossProduct( const ON_3dVector& a , const ON_3dVector& b )
{
	return ON_3dVector(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y );
}
double ON_3dVector::ON_DotProduct(const ON_3dVector& a , const ON_3dVector& b ){
return a.x*b.x + a.y*b.y + a.z*b.z;
}
double ON_3dVector::ON_Length3d(double x, double y, double z)
{
	double len;
	x = fabs(x);
	y = fabs(y);
	z = fabs(z);
	if ( y >= x && y >= z ) {
		len = x; x = y; y = len;
	}
	else if ( z >= x && z >= y ) {
		len = x; x = z; z = len;
	}
	if ( x > ON_DBL_MIN ) 
	{
		y /= x;
		z /= x;
		len = x*sqrt(1.0 + y*y + z*z);
	}
	else if ( x > 0.0 && ON_IS_FINITE(x) )
		len = x;
	else
		len = 0.0;

	return len;
}








bool ON_3dVector::ON_IsOrthogonalFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z )
{
  // returns true if X, Y, Z is an orthogonal frame
  if (! X.IsValid() || !Y.IsValid() || !Z.IsValid() )
    return false;

  double lx = X.Length();
  double ly = Y.Length();
  double lz = Z.Length();
  if ( lx <=  ON_SQRT_EPSILON )
    return false;
  if ( ly <=  ON_SQRT_EPSILON )
    return false;
  if ( lz <=  ON_SQRT_EPSILON )
    return false;
  lx = 1.0/lx;
  ly = 1.0/ly;
  lz = 1.0/lz;
  double xy = (X.x*Y.x + X.y*Y.y + X.z*Y.z)*lx*ly;
  double yz = (Y.x*Z.x + Y.y*Z.y + Y.z*Z.z)*ly*lz;
  double zx = (Z.x*X.x + Z.y*X.y + Z.z*X.z)*lz*lx;
  if (    fabs(xy) > ON_SQRT_EPSILON 
       || fabs(yz) > ON_SQRT_EPSILON
       || fabs(zx) > ON_SQRT_EPSILON
     )
  {
    double t = 0.0000152587890625;
    if ( fabs(xy) >= t || fabs(yz)  >= t || fabs(zx) >= t )
      return false;

    // do a more careful (and time consuming check)
    // This fixes RR 22219 and 22276
    ON_3dVector V;
    V = ON_CrossProduct(X,Y)*(lx*ly);
    t = fabs((V.x*Z.x + V.y*Z.y + V.z*Z.z)*lz);
    if ( fabs(t-1.0) > ON_SQRT_EPSILON )
      return false;

    V = ON_CrossProduct(Y,Z)*(ly*lz);
    t = fabs((V.x*X.x + V.y*X.y + V.z*X.z)*lx);
    if ( fabs(t-1.0) > ON_SQRT_EPSILON )
      return false;

    V = ON_CrossProduct(Z,X)*(lz*lx);
    t = fabs((V.x*Y.x + V.y*Y.y + V.z*Y.z)*ly);
    if ( fabs(t-1.0) > ON_SQRT_EPSILON )
      return false;
  }
  return true;
}

bool ON_3dVector::ON_IsOrthonormalFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z )
{
  // returns true if X, Y, Z is an orthonormal frame
  if ( !ON_IsOrthogonalFrame( X, Y, Z ) )
    return false;
  double x = X.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;
  x = Y.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;
  x = Z.Length();
  if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
    return false;

  return true;
}

bool ON_3dVector::ON_IsRightHandFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z )
{
  // returns true if X, Y, Z is an orthonormal right hand frame
  if ( !ON_IsOrthonormalFrame(X,Y,Z) )
    return false;
  double x = ON_DotProduct( ON_CrossProduct( X, Y ), Z );
  if ( x <=  ON_SQRT_EPSILON )
    return false;
  return true;
}
/////////////////////////////////////////////////
ON_3dPoint operator*(double d, const ON_3dPoint& p)
{
  return ON_3dPoint(d*p.x,d*p.y,d*p.z);
}
ON_3dVector operator*(double d, const ON_3dVector& v)
{
  return ON_3dVector(d*v.x,d*v.y,d*v.z);
}