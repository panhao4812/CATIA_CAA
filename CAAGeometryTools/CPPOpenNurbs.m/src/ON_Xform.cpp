#include "opennurbs.h"
ON_Xform::ON_Xform()
{
	memset( m_xform, 0, sizeof(m_xform) );
	m_xform[3][3] = 1.0;
}
ON_Xform::ON_Xform( double d )
{
	memset( m_xform, 0, sizeof(m_xform) );
	m_xform[0][0] = m_xform[1][1] = m_xform[2][2] = d;
	m_xform[3][3] = 1.0;
}
ON_Xform::ON_Xform( double m[4][4] )
{
	memcpy( &m_xform[0][0], &m[0][0], sizeof(m_xform) );
}
ON_Xform::ON_Xform( const double m[4][4] )
{
	memcpy( &m_xform[0][0], &m[0][0], sizeof(m_xform) );
}
bool ON_Xform::IsValid() const
{
	int i;
	const double* x = &m_xform[0][0];
	bool rc = true;
	for (i = 0; i < 16 && rc; i++)
	{
		rc = ON_IS_VALID(*x++);
	}
	return rc;
}
bool ON_Xform::IsZero() const
{
	const double* v = &m_xform[0][0];
	for ( int i = 0; i < 15; i++ )
	{
		if ( *v++ != 0.0 )
			return false;
	}
	return true;
}

void ON_Xform::Rotation( double angle,ON_3dVector axis,ON_3dPoint center )
{
	Rotation( sin(angle), cos(angle), axis, center );
}

void ON_Xform::Rotation(ON_3dVector start_dir,ON_3dVector end_dir,ON_3dPoint rotation_center)
{
	if ( fabs(start_dir.Length()-1.0) > ON_SQRT_EPSILON )
		start_dir.Unitize();
	if ( fabs(end_dir.Length()-1.0) > ON_SQRT_EPSILON )
		end_dir.Unitize();
	double cos_angle = start_dir*end_dir;
	ON_3dVector axis = ON_3dVector::ON_CrossProduct(start_dir,end_dir);
	double sin_angle = axis.Length();
	if ( 0.0 == sin_angle || !axis.Unitize() )
	{
		axis.PerpendicularTo(start_dir);
		axis.Unitize();
		sin_angle = 0.0;
		cos_angle = (cos_angle < 0.0) ? -1.0 : 1.0;
	}
	Rotation(sin_angle,cos_angle,axis,rotation_center);
}

void ON_Xform::Rotation(  double sin_angle,double cos_angle,ON_3dVector axis,ON_3dPoint center)
{
	Identity();

	for(;;)
	{
		// 29 June 2005 Dale Lear
		//     Kill noise in input
		if ( fabs(sin_angle) >= 1.0-ON_SQRT_EPSILON && fabs(cos_angle) <= ON_SQRT_EPSILON )
		{
			cos_angle = 0.0;
			sin_angle = (sin_angle < 0.0) ? -1.0 : 1.0; 
			break;
		}

		if ( fabs(cos_angle) >= 1.0-ON_SQRT_EPSILON && fabs(sin_angle) <= ON_SQRT_EPSILON )
		{
			cos_angle = (cos_angle < 0.0) ? -1.0 : 1.0; 
			sin_angle = 0.0;
			break;
		}

		if ( fabs(cos_angle*cos_angle + sin_angle*sin_angle - 1.0) > ON_SQRT_EPSILON )
		{
			ON_3dVector cs(cos_angle,sin_angle,0);
			if ( cs.Unitize() )
			{
				cos_angle = cs.x;
				sin_angle = cs.y;
				// no break here
			}
			else
			{
				cout<<"sin_angle and cos_angle are both zero."<<endl;
				cos_angle = 1.0;
				sin_angle = 0.0;
				break;
			}
		}

		if ( fabs(cos_angle) > 1.0-ON_EPSILON || fabs(sin_angle) < ON_EPSILON )
		{
			cos_angle = (cos_angle < 0.0) ? -1.0 : 1.0; 
			sin_angle = 0.0;
			break;
		}

		if ( fabs(sin_angle) > 1.0-ON_EPSILON || fabs(cos_angle) < ON_EPSILON )
		{
			cos_angle = 0.0;
			sin_angle = (sin_angle < 0.0) ? -1.0 : 1.0; 
			break;
		}

		break;
	}

	if (sin_angle != 0.0 || cos_angle != 1.0) 
	{
		const double one_minus_cos_angle = 1.0 - cos_angle;
		ON_3dVector a = axis;
		if ( fabs(a.LengthSquared() - 1.0) >  ON_EPSILON )
			a.Unitize();

		m_xform[0][0] = a.x*a.x*one_minus_cos_angle + cos_angle;
		m_xform[0][1] = a.x*a.y*one_minus_cos_angle - a.z*sin_angle;
		m_xform[0][2] = a.x*a.z*one_minus_cos_angle + a.y*sin_angle;

		m_xform[1][0] = a.y*a.x*one_minus_cos_angle + a.z*sin_angle;
		m_xform[1][1] = a.y*a.y*one_minus_cos_angle + cos_angle;
		m_xform[1][2] = a.y*a.z*one_minus_cos_angle - a.x*sin_angle;

		m_xform[2][0] = a.z*a.x*one_minus_cos_angle - a.y*sin_angle;
		m_xform[2][1] = a.z*a.y*one_minus_cos_angle + a.x*sin_angle;
		m_xform[2][2] = a.z*a.z*one_minus_cos_angle + cos_angle;

		if ( center.x != 0.0 || center.y != 0.0 || center.z != 0.0 ) {
			m_xform[0][3] = -((m_xform[0][0]-1.0)*center.x + m_xform[0][1]*center.y + m_xform[0][2]*center.z);
			m_xform[1][3] = -(m_xform[1][0]*center.x + (m_xform[1][1]-1.0)*center.y + m_xform[1][2]*center.z);
			m_xform[2][3] = -(m_xform[2][0]*center.x + m_xform[2][1]*center.y + (m_xform[2][2]-1.0)*center.z);
		}

		m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0;
		m_xform[3][3] = 1.0;
	}
}


void ON_Xform::Rotation(
						const ON_3dVector&  X0, // initial frame X (X,Y,Z = right handed orthonormal frame)
						const ON_3dVector&  Y0, // initial frame Y
						const ON_3dVector&  Z0, // initial frame Z
						const ON_3dVector&  X1, // final frame X (X,Y,Z = another right handed orthonormal frame)
						const ON_3dVector&  Y1, // final frame Y
						const ON_3dVector&  Z1  // final frame Z
						)
{
	// transformation maps X0 to X1, Y0 to Y1, Z0 to Z1

	// F0 changes x0,y0,z0 to world X,Y,Z
	ON_Xform F0;
	F0[0][0] = X0.x; F0[0][1] = X0.y; F0[0][2] = X0.z;
	F0[1][0] = Y0.x; F0[1][1] = Y0.y; F0[1][2] = Y0.z;
	F0[2][0] = Z0.x; F0[2][1] = Z0.y; F0[2][2] = Z0.z;
	F0[3][3] = 1.0;

	// F1 changes world X,Y,Z to x1,y1,z1
	ON_Xform F1;
	F1[0][0] = X1.x; F1[0][1] = Y1.x; F1[0][2] = Z1.x;
	F1[1][0] = X1.y; F1[1][1] = Y1.y; F1[1][2] = Z1.y;
	F1[2][0] = X1.z; F1[2][1] = Y1.z; F1[2][2] = Z1.z;
	F1[3][3] = 1.0;

	*this = F1*F0;
}
void ON_Xform::Rotation(   // (not strictly a rotation)
						// transformation maps P0 to P1, P0+X0 to P1+X1, ...
						const ON_3dPoint&   P0,  // initial frame center
						const ON_3dVector&  X0, // initial frame X
						const ON_3dVector&  Y0, // initial frame Y
						const ON_3dVector&  Z0, // initial frame Z
						const ON_3dPoint&   P1,  // final frame center
						const ON_3dVector&  X1, // final frame X
						const ON_3dVector&  Y1, // final frame Y
						const ON_3dVector&  Z1  // final frame Z
						)
{
	// transformation maps P0 to P1, P0+X0 to P1+X1, ...

	// T0 translates point P0 to (0,0,0)
	ON_Xform T0;
	T0.Translation( -P0.x, -P0.y, -P0.z );

	ON_Xform R;
	R.Rotation(X0,Y0,Z0,X1,Y1,Z1);

	// T1 translates (0,0,0) to point o1
	ON_Xform T1;
	T1.Translation( P1 );

	*this = T1*R*T0;
}
ON_Xform ON_Xform::operator*( const ON_Xform& rhs ) const
{
	double m[4][4];
	const double* p = &rhs.m_xform[0][0];

	m[0][0] = m_xform[0][0]*p[0] + m_xform[0][1]*p[4] + m_xform[0][2]*p[ 8] + m_xform[0][3]*p[12];
	m[0][1] = m_xform[0][0]*p[1] + m_xform[0][1]*p[5] + m_xform[0][2]*p[ 9] + m_xform[0][3]*p[13];
	m[0][2] = m_xform[0][0]*p[2] + m_xform[0][1]*p[6] + m_xform[0][2]*p[10] + m_xform[0][3]*p[14];
	m[0][3] = m_xform[0][0]*p[3] + m_xform[0][1]*p[7] + m_xform[0][2]*p[11] + m_xform[0][3]*p[15];

	m[1][0] = m_xform[1][0]*p[0] + m_xform[1][1]*p[4] + m_xform[1][2]*p[ 8] + m_xform[1][3]*p[12];
	m[1][1] = m_xform[1][0]*p[1] + m_xform[1][1]*p[5] + m_xform[1][2]*p[ 9] + m_xform[1][3]*p[13];
	m[1][2] = m_xform[1][0]*p[2] + m_xform[1][1]*p[6] + m_xform[1][2]*p[10] + m_xform[1][3]*p[14];
	m[1][3] = m_xform[1][0]*p[3] + m_xform[1][1]*p[7] + m_xform[1][2]*p[11] + m_xform[1][3]*p[15];

	m[2][0] = m_xform[2][0]*p[0] + m_xform[2][1]*p[4] + m_xform[2][2]*p[ 8] + m_xform[2][3]*p[12];
	m[2][1] = m_xform[2][0]*p[1] + m_xform[2][1]*p[5] + m_xform[2][2]*p[ 9] + m_xform[2][3]*p[13];
	m[2][2] = m_xform[2][0]*p[2] + m_xform[2][1]*p[6] + m_xform[2][2]*p[10] + m_xform[2][3]*p[14];
	m[2][3] = m_xform[2][0]*p[3] + m_xform[2][1]*p[7] + m_xform[2][2]*p[11] + m_xform[2][3]*p[15];

	m[3][0] = m_xform[3][0]*p[0] + m_xform[3][1]*p[4] + m_xform[3][2]*p[ 8] + m_xform[3][3]*p[12];
	m[3][1] = m_xform[3][0]*p[1] + m_xform[3][1]*p[5] + m_xform[3][2]*p[ 9] + m_xform[3][3]*p[13];
	m[3][2] = m_xform[3][0]*p[2] + m_xform[3][1]*p[6] + m_xform[3][2]*p[10] + m_xform[3][3]*p[14];
	m[3][3] = m_xform[3][0]*p[3] + m_xform[3][1]*p[7] + m_xform[3][2]*p[11] + m_xform[3][3]*p[15];

	return ON_Xform(m);
}

ON_Xform ON_Xform::operator+( const ON_Xform& rhs ) const
{
	double m[4][4];
	const double* p = &rhs.m_xform[0][0];

	m[0][0] = m_xform[0][0] + p[0];
	m[0][1] = m_xform[0][1] + p[1];
	m[0][2] = m_xform[0][2] + p[2];
	m[0][3] = m_xform[0][3] + p[3];

	m[1][0] = m_xform[1][0] + p[4];
	m[1][1] = m_xform[1][1] + p[5];
	m[1][2] = m_xform[1][2] + p[6];
	m[1][3] = m_xform[1][3] + p[7];

	m[2][0] = m_xform[2][0] + p[ 8];
	m[2][1] = m_xform[2][1] + p[ 9];
	m[2][2] = m_xform[2][2] + p[10];
	m[2][3] = m_xform[2][3] + p[11];

	m[3][0] = m_xform[3][0] + p[12];
	m[3][1] = m_xform[3][1] + p[13];
	m[3][2] = m_xform[3][2] + p[14];
	m[3][3] = m_xform[3][3] + p[15];

	return ON_Xform(m);
}

ON_Xform ON_Xform::operator-( const ON_Xform& rhs ) const
{
	double m[4][4];
	const double* p = &rhs.m_xform[0][0];

	m[0][0] = m_xform[0][0] - p[0];
	m[0][1] = m_xform[0][1] - p[1];
	m[0][2] = m_xform[0][2] - p[2];
	m[0][3] = m_xform[0][3] - p[3];

	m[1][0] = m_xform[1][0] - p[4];
	m[1][1] = m_xform[1][1] - p[5];
	m[1][2] = m_xform[1][2] - p[6];
	m[1][3] = m_xform[1][3] - p[7];

	m[2][0] = m_xform[2][0] - p[ 8];
	m[2][1] = m_xform[2][1] - p[ 9];
	m[2][2] = m_xform[2][2] - p[10];
	m[2][3] = m_xform[2][3] - p[11];

	m[3][0] = m_xform[3][0] - p[12];
	m[3][1] = m_xform[3][1] - p[13];
	m[3][2] = m_xform[3][2] - p[14];
	m[3][3] = m_xform[3][3] - p[15];

	return ON_Xform(m);
}

ON_3dPoint ON_Xform::operator*( const ON_3dPoint& p ) const
{
	const double x = p.x; // optimizer should put x,y,z in registers
	const double y = p.y;
	const double z = p.z;
	double xh[3], w;
	const double* m = &m_xform[0][0];
	xh[0] = m[ 0]*x + m[ 1]*y + m[ 2]*z + m[ 3];
	xh[1] = m[ 4]*x + m[ 5]*y + m[ 6]*z + m[ 7];
	xh[2] = m[ 8]*x + m[ 9]*y + m[10]*z + m[11];
	w     = m[12]*x + m[13]*y + m[14]*z + m[15];
	w = (w != 0.0) ? 1.0/w : 1.0;
	return ON_3dPoint( w*xh[0], w*xh[1], w*xh[2] );
}

ON_3dVector ON_Xform::operator*( const ON_3dVector& v ) const
{
	const double x = v.x; // optimizer should put x,y,z in registers
	const double y = v.y;
	const double z = v.z;
	double xh[3];
	const double* m = &m_xform[0][0];
	xh[0] = m[0]*x + m[1]*y + m[ 2]*z;
	xh[1] = m[4]*x + m[5]*y + m[ 6]*z;
	xh[2] = m[8]*x + m[9]*y + m[10]*z;
	return ON_3dVector( xh[0],xh[1],xh[2] );
}

void ON_Xform::Scale( double x, double y, double z )
{
	memset( m_xform, 0, sizeof(m_xform) );
	m_xform[0][0] = x;
	m_xform[1][1] = y;
	m_xform[2][2] = z;
	m_xform[3][3] = 1.0;
}

void ON_Xform::Scale( const ON_3dVector& v )
{
	memset( m_xform, 0, sizeof(m_xform) );
	m_xform[0][0] = v.x;
	m_xform[1][1] = v.y;
	m_xform[2][2] = v.z;
	m_xform[3][3] = 1.0;
}

void ON_Xform::Scale(ON_3dPoint fixed_point,double scale_factor)
{
	if ( fixed_point.x == 0.0 && fixed_point.y == 0.0 && fixed_point.z == 0.0 )
	{
		Scale( scale_factor, scale_factor, scale_factor );
	}
	else
	{
		ON_Xform t0, t1, s;
		t0.Translation( ON_3dPoint::Origin - fixed_point );
		s.Scale( scale_factor, scale_factor, scale_factor );
		t1.Translation( fixed_point - ON_3dPoint::Origin );
		operator=(t1*s*t0);
	}
}



void ON_Xform::Translation( double x, double y, double z )
{
	Identity();
	m_xform[0][3] = x;
	m_xform[1][3] = y;
	m_xform[2][3] = z;
	m_xform[3][3] = 1.0;
}

void ON_Xform::Translation( const ON_3dVector& v )
{
	Identity();
	m_xform[0][3] = v.x;
	m_xform[1][3] = v.y;
	m_xform[2][3] = v.z;
	m_xform[3][3] = 1.0;
}
void ON_Xform::Translation( const ON_3dPoint& v )
{
	Identity();
	m_xform[0][3] = v.x;
	m_xform[1][3] = v.y;
	m_xform[2][3] = v.z;
	m_xform[3][3] = 1.0;
}

void ON_Xform::Zero()
{
	memset( m_xform, 0, sizeof(m_xform) );
}

void ON_Xform::Identity()
{
	memset( m_xform, 0, sizeof(m_xform) );
	m_xform[0][0] = m_xform[1][1] = m_xform[2][2] = m_xform[3][3] = 1.0;
}
double* ON_Xform::operator[](int i)
{
	return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : NULL;
}

const double* ON_Xform::operator[](int i) const
{
	return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : NULL;
}
bool ON_Xform::IsIdentity( double zero_tolerance ) const
{
  // The code below will return false if m_xform[][] contains
  // a nan value.
  const double* v = &m_xform[0][0];
  for ( int i = 0; i < 3; i++ )
  {
    if ( !(fabs(1.0 - *v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
    if ( !(fabs(*v++) <= zero_tolerance) )
      return false;
  }
  if ( !(fabs( 1.0 - *v ) <= zero_tolerance) )
    return false;
  return true;
}
///////////////////////////////////////////////////////////////////////////