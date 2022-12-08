#ifndef opennurbs_H
#define opennurbs_H
//std
#include <iostream.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <deque>  
#include <vector>  
#include <sstream>
#include "CPPOpenNurbs.h"
using namespace std;

#define ON_UNSET_VALUE -1.23432101234321e+308
#define ON_IS_FINITE(x) (0x7FF0 != (*((unsigned short*)(&x) + 3) & 0x7FF0))
#define ON_IS_VALID(x)  (x != ON_UNSET_VALUE && 0x7FF0 != (*((unsigned short*)(&x) + 3) & 0x7FF0))
#define ON_DBL_MIN 2.22507385850720200e-308
#define ON_SQRT_EPSILON 1.490116119385000000e-8
#define ON_EPSILON 2.2204460492503131e-16
#define ON_ZERO_TOLERANCE 2.3283064365386962890625e-10
#define ON_UNSET_COLOR 0xFFFFFFFF
#define ON_RELATIVE_TOLERANCE 2.27373675443232059478759765625e-13

class ON_Xform;
class ON_3dPoint;
class ON_3dVector;
class ON_Polyline;
class ON_Line;
class ON_Plane;
class ClobalFunction;

class ExportedByCPPOpenNurbs ON_3dPoint
{
public:
	double x, y, z;
	static const ON_3dPoint Origin;
	ON_3dPoint();                         // x,y,z not initialized
	ON_3dPoint(double x,double y,double z);
	void Transform( const ON_Xform& xform);
	void Zero(); 
	double DistanceTo( const ON_3dPoint& p ) const;
	bool IsValid() const;
	int MaximumCoordinateIndex() const;
	double MaximumCoordinate() const; // absolute value of maximum coordinate
	int MinimumCoordinateIndex() const;
	double MinimumCoordinate() const;
	ON_3dPoint  operator+(const ON_3dPoint& p) const;
	ON_3dPoint  operator+(const ON_3dVector& v) const;
	ON_3dVector operator-(const ON_3dPoint& p) const;
	ON_3dPoint  operator-(const ON_3dVector& v) const;
	ON_3dPoint& operator*=(double);
	ON_3dPoint& operator/=(double);
	ON_3dPoint& operator+=(const ON_3dPoint&);  // Adding this was a mistake - cannot remove without breaking SDK
	ON_3dPoint& operator+=(const ON_3dVector&);
	ON_3dPoint& operator-=(const ON_3dPoint&);  // Adding this was a mistake - cannot remove without breaking SDK
	ON_3dPoint& operator-=(const ON_3dVector&);
	ON_3dPoint& operator=(const ON_3dVector&);
	ON_3dPoint& operator=(const ON_3dPoint&);
	bool operator==(const ON_3dPoint&) const;
	bool operator==(const ON_3dVector&) const;
	bool operator!=(const ON_3dPoint&) const;
	ON_3dPoint  operator*(double) const;
	ON_3dPoint  operator/(double) const;
	double operator*(const ON_3dPoint&) const; // dot product for points acting as vectors
	double operator*(const ON_3dVector&) const; // dot product for points acting as vectors
	ON_3dPoint operator*(const ON_Xform&) const;
	string ToString() const;
	static	double CrossProduct(const ON_3dPoint& A,const ON_3dPoint& B,const ON_3dPoint& C);
	static double DotProduct(const ON_3dPoint& A,const ON_3dPoint& B,const ON_3dPoint& C);
	static bool OrthoClose(const ON_3dPoint& Point1,const ON_3dPoint& Point2, double t);
};

class ExportedByCPPOpenNurbs ON_3dVector
{
public:
	double x, y, z;
	static const ON_3dVector ZeroVector;  // (0.0,0.0,0.0)
	static const ON_3dVector XAxis;       // (1.0,0.0,0.0)
	static const ON_3dVector YAxis;       // (0.0,1.0,0.0)
	static const ON_3dVector ZAxis;       // (0.0,0.0,1.0)
	bool IsValid() const;
	ON_3dVector();                     // x,y,z not initialized
	ON_3dVector(double x,double y,double z);
	void Transform( const ON_Xform& );
	double Length() const;
	bool  Unitize();
	void Zero();
	double operator*(const ON_3dVector&) const; // inner (dot) product
	double operator*(const ON_3dPoint&) const;

	ON_3dVector  operator*(double) const;
	ON_3dVector  operator/(double) const;
	ON_3dVector  operator+(const ON_3dVector&) const;
	ON_3dPoint   operator+(const ON_3dPoint&) const;
	ON_3dVector  operator-(const ON_3dVector&) const;
	ON_3dPoint   operator-(const ON_3dPoint&) const;
	ON_3dVector& operator*=(double);
	ON_3dVector& operator/=(double);
	ON_3dVector& operator+=(const ON_3dVector&);
	ON_3dVector& operator-=(const ON_3dVector&);
	ON_3dVector& operator=(const ON_3dVector&);
	ON_3dVector& operator=(const ON_3dPoint&);
	bool operator==(const ON_3dPoint&) const;
	bool operator==(const ON_3dVector&) const;
	bool PerpendicularTo(const ON_3dVector& );
	bool PerpendicularTo( const ON_3dPoint& P0, const ON_3dPoint& P1, const ON_3dPoint& P2);
	double LengthSquared() const;
	string ToString() const;
	static double ON_DotProduct(const ON_3dVector& a , const ON_3dVector& b );
	static ON_3dVector ON_CrossProduct( const ON_3dVector& a , const ON_3dVector& b );
	static double ON_Length3d(double x, double y, double z);
	static bool ON_IsRightHandFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z );
	static bool ON_IsOrthogonalFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z );
	static bool ON_IsOrthonormalFrame( const ON_3dVector& X,  const ON_3dVector& Y,  const ON_3dVector& Z );
};

class ExportedByCPPOpenNurbs ON_Xform
{
public:
	//           [0][0] [0][1] [0][2] [0][3]
	//           [1][0] [1][1] [1][2] [1][3]
	//           [2][0] [2][1] [2][2] [2][3]
	//           [3][0] [3][1] [3][2] [3][3]
	// [i][j] = row i, column j.  I.e., 
	double m_xform[4][4]; 
	ON_Xform();                     // zero matrix
	ON_Xform( double );     
	ON_Xform( double[4][4] );// diagonal matrix (d,d,d,1)                      //
	ON_Xform( const double[4][4] ); // from standard double m[4][4]
	bool IsValid() const;
	bool IsZero() const;
	void Identity();
	void Zero();
	void Scale( double x_scale_factor,double y_scale_factor,double z_scale_factor);
	void Scale( const ON_3dVector& scale_vector);
	void Scale(ON_3dPoint fixed_point,double scale_factor);
	void Translation( const ON_3dVector&  d);
	void Translation( const ON_3dPoint&  d);
	void Translation( double dx ,double dy, double dz);
	void Rotation(double sin_angle,double cos_angle,ON_3dVector rotation_axis,ON_3dPoint rotation_center);
	void Rotation(double angle_radians,ON_3dVector rotation_axis,ON_3dPoint rotation_center);
	void Rotation(ON_3dVector start_dir,ON_3dVector end_dir,ON_3dPoint rotation_center);
	void Rotation( 
		const ON_3dVector& X0,
		const ON_3dVector& Y0,
		const ON_3dVector& Z0,
		const ON_3dVector& X1,
		const ON_3dVector& Y1,
		const ON_3dVector& Z1
		);
	void Rotation( 
		const ON_3dPoint& P0,
		const ON_3dVector& X0,
		const ON_3dVector& Y0,
		const ON_3dVector& Z0,
		const ON_3dPoint& P1,
		const ON_3dVector& X1,
		const ON_3dVector& Y1,
		const ON_3dVector& Z1
		);
	ON_Xform operator*( const ON_Xform& rhs ) const;
	ON_Xform operator+( const ON_Xform& rhs ) const;
	ON_Xform operator-( const ON_Xform& rhs ) const;
	ON_3dPoint operator*( const ON_3dPoint& ) const;
	ON_3dVector operator*( const ON_3dVector& ) const;
	double* operator[](int);
	const double* operator[](int) const;

	bool IsIdentity( double zero_tolerance = 0.0) const;
};
class ExportedByCPPOpenNurbs ON_Polyline:public deque<ON_3dPoint>
{
public:
	ON_Polyline();
	ON_Polyline(const deque<ON_3dPoint>&);
	ON_Polyline& operator=(const deque<ON_3dPoint>&); 
	void Add(const ON_3dPoint& p);

	static  bool ComputeHull2d(vector<ON_3dPoint>& nodes, vector<int>& hull);
	static  ON_Polyline  ComputeHull2d(vector<ON_3dPoint> nodes);
	static  vector<ON_3dPoint>  RemoveDupPts(vector<ON_3dPoint> mypoints, double tolerance);

	//~ON_Polyline();
};
class ExportedByCPPOpenNurbs ON_Line{
public:
	ON_3dPoint from;
	ON_3dPoint to;
public:
	ON_Line();
	ON_Line( const ON_3dPoint& start, const ON_3dPoint& end );
	~ON_Line();
	bool IsValid() const;
	ON_3dPoint& operator[](int);
	const ON_3dPoint& operator[](int) const;
	bool Create( const ON_3dPoint& start, const ON_3dPoint& end);
	double Length() const;
	void Reverse();
	bool Transform( const ON_Xform& xform);
	ON_3dPoint PointAt( double t ) const;
	bool ClosestPointTo( const ON_3dPoint& test_point, double* t) const;
	ON_3dPoint ClosestPointTo( const ON_3dPoint& test_point) const;
	double DistanceTo( ON_3dPoint test_point ) const;
	ON_3dVector Direction() const;

};
class ExportedByCPPOpenNurbs ON_Plane{
public :
	ON_3dPoint  origin;
	ON_3dVector xaxis;
	ON_3dVector yaxis;
	ON_3dVector zaxis;
	double equation[4];
public:
	ON_Plane();
	ON_Plane(const ON_3dPoint& origin,const ON_3dVector& normal);
	ON_Plane(const ON_3dPoint& origin,const ON_3dVector& x_dir,const ON_3dVector& y_dir);
	ON_Plane(const ON_3dPoint& origin,const ON_3dPoint& x_point,const ON_3dPoint& y_point);
	ON_Plane(const double equation[4]);
	~ON_Plane();
	bool operator==(const ON_Plane&) const;
	bool operator!=(const ON_Plane&) const;
	bool CreateFromNormal(const ON_3dPoint& origin,const ON_3dVector& normal);
	bool CreateFromFrame(const ON_3dPoint& origin,const ON_3dVector& x_dir,const ON_3dVector& y_dir);
	bool CreateFromPoints(const ON_3dPoint& origin,const ON_3dPoint& point_on_x,const ON_3dPoint& point_on);
	bool CreateFromEquation( const double equation[4]);
	bool IsValid() const;
	const ON_3dPoint& Origin() const;
	const ON_3dVector& Xaxis() const;
	const ON_3dVector& Yaxis() const;
	const ON_3dVector& Normal() const;
	bool UpdateEquation();
	void SetOrigin( const ON_3dPoint& origin );
	double DistanceTo( const ON_3dPoint& point) const;
	bool Transform( const ON_Xform& xform);

};


class ExportedByCPPOpenNurbs GlobalFunction{
public:
GlobalFunction();
static void Print(const ON_3dPoint& pt);
static void Print(const ON_3dVector& v);
static void Print(const ON_Line& line);
static void Print(const ON_Polyline& pl);
static void Print(const ON_Plane& plane);
};
ON_3dVector ExportedByCPPOpenNurbs operator*(double, const ON_3dVector&);
ON_3dPoint ExportedByCPPOpenNurbs operator*(double, const ON_3dPoint&);

#endif