#include "opennurbs.h"
ON_Plane::ON_Plane() : origin(0.0,0.0,0.0), xaxis(1.0,0.0,0.0), yaxis(0.0,1.0,0.0), zaxis(0.0,0.0,1.0)
{
	equation[0]=0.0; equation[1]= 0.0;equation[2]=0.0;equation[3] = 1.0;
}
ON_Plane::ON_Plane(const ON_3dPoint& origin,const ON_3dVector& normal)
{
	CreateFromNormal(origin,normal);
}
ON_Plane::ON_Plane(const ON_3dPoint& origin,const ON_3dVector& x_dir,const ON_3dVector& y_dir)
{
	CreateFromFrame(origin,x_dir,y_dir);
}
ON_Plane::ON_Plane(const ON_3dPoint& origin,const ON_3dPoint& x_point,const ON_3dPoint& y_point)
{
	CreateFromPoints(origin,x_point,y_point);
}
ON_Plane::ON_Plane(const double e[4])
{
	CreateFromEquation(e);
}
ON_Plane::~ON_Plane(){}
const ON_3dPoint& ON_Plane::Origin() const{return origin;}
const ON_3dVector& ON_Plane::Xaxis() const{ return xaxis;}
const ON_3dVector& ON_Plane::Yaxis() const{ return yaxis;}
const ON_3dVector& ON_Plane::Normal() const{ return zaxis;}
void ON_Plane::SetOrigin( const ON_3dPoint& origin_point ){ origin = origin_point;UpdateEquation();}
///////////////////////////////
bool ON_Plane::operator==(const ON_Plane& other) const
{
	return (origin==other.origin && xaxis==other.xaxis && yaxis==other.yaxis && zaxis==other.zaxis)? true : false;
}

bool ON_Plane::operator!=(const ON_Plane& other) const
{
	return ON_Plane::operator==(other)?false:true;
}
bool ON_Plane::CreateFromNormal(const ON_3dPoint&  P, const ON_3dVector& N )
{
	origin = P;
	zaxis = N;
	bool b = zaxis.Unitize();
	xaxis.PerpendicularTo( zaxis );
	xaxis.Unitize();
	yaxis = ON_3dVector::ON_CrossProduct( zaxis, xaxis );
	yaxis.Unitize();
	UpdateEquation();
	return b;
}
bool ON_Plane::CreateFromFrame(const ON_3dPoint&  P,const ON_3dVector& X,const ON_3dVector& Y )
{
	origin = P;
	xaxis = X;
	xaxis.Unitize();
	yaxis = Y - xaxis*ON_3dVector::ON_DotProduct( Y, xaxis);
	yaxis.Unitize();
	zaxis = ON_3dVector::ON_CrossProduct( xaxis, yaxis );
	bool b = zaxis.Unitize();
	UpdateEquation();
	if ( b )
	{    
		b = IsValid();
		if ( b )
		{  
			if ( fabs(Y*zaxis) > ON_SQRT_EPSILON *(Y.Length()) )
				b = false;
		}
	}
	return b;
}

bool ON_Plane::CreateFromEquation(const double e[4]   )
{
	bool b = false;
	equation[0]=e[0];equation[1]=e[1];equation[2]=e[2];equation[3]=e[3];

	zaxis.x = e[0];
	zaxis.y = e[1];
	zaxis.z = e[2];

	double d = zaxis.Length();
	if ( d > 0.0 ) {
		d = 1.0/d;
		origin =zaxis* (-d*equation[3]);
		b = true;
	}
	xaxis.PerpendicularTo( zaxis );
	xaxis.Unitize();
	yaxis = ON_3dVector::ON_CrossProduct( zaxis, xaxis );
	yaxis.Unitize();
	return b;
}

bool ON_Plane::CreateFromPoints(const ON_3dPoint& P, const ON_3dPoint& Q,const ON_3dPoint& R )
{
	origin = P;
	bool rc = zaxis.PerpendicularTo(P,Q,R);
	xaxis = Q - P;
	xaxis.Unitize();
	yaxis = ON_3dVector::ON_CrossProduct( zaxis, xaxis );
	yaxis.Unitize();
	if ( !UpdateEquation() )
		rc = false;
	return rc;
}
bool ON_Plane::IsValid() const
{
	if (  equation[0]==0&&equation[1]==0&&equation[2]==0&&equation[3]==0)return false;
	double x = equation[0]*origin.x + equation[1]*origin.y + equation[2]*origin.z + equation[3];//plane_equation.ValueAt(origin);
	if ( fabs(x) >  ON_ZERO_TOLERANCE )
	{
		double tol = fabs(origin.MaximumCoordinate()) + fabs(equation[3]);
		if ( tol > 1000.0 && origin.IsValid() )
		{  
			tol *= (ON_EPSILON*10.0);
			if ( fabs(x) > tol )
				return false;
		}
		else
			return false;
	}

	if ( !ON_3dVector::ON_IsRightHandFrame( xaxis, yaxis, zaxis ) )
		return false;

	ON_3dVector N = ON_3dVector(equation[0],equation[1],equation[2]);
	N.Unitize();
	x = ON_3dVector::ON_DotProduct( N, zaxis );
	if ( fabs(x-1.0) >  ON_SQRT_EPSILON )
		return false;

	return true;
}

double ON_Plane::DistanceTo( const ON_3dPoint& point) const
{
	return ( point - origin)*zaxis;
}
bool ON_Plane::Transform( const ON_Xform& xform){
	if ( xform.IsIdentity() )return IsValid();
	ON_3dPoint origin_pt = xform*origin;
	bool bUseVectorXform = (    0.0 == xform.m_xform[3][0] 
	&& 0.0 == xform.m_xform[3][1]
	&& 0.0 == xform.m_xform[3][2] 
	&& 1.0 == xform.m_xform[3][3]
	);
	ON_3dVector xaxis_vec = bUseVectorXform ? (xform*xaxis) : ((xform*(origin+xaxis)) - origin_pt);
	ON_3dVector yaxis_vec = bUseVectorXform ? (xform*yaxis) : ((xform*(origin+yaxis)) - origin_pt);
	return CreateFromFrame( origin_pt, xaxis_vec, yaxis_vec );
}
bool ON_Plane::UpdateEquation()
{
	bool rc = false;
	if ( origin.IsValid() && zaxis.IsValid() )
	{
		equation[0] = zaxis.x;
		equation[1] = zaxis.y;
		equation[2] = zaxis.z;
		ON_3dVector v(equation[0],equation[1],equation[2]);
		rc = ( fabs(1.0 - v.Length()) > ON_ZERO_TOLERANCE ) ? v.Unitize() : true;
		equation[3] = -(v.x*origin.x + v.y*origin.y + v.z*origin.z);
	}
	return rc;
}

