#include "opennurbs.h"

ON_Line::ON_Line()
{
  from.Zero();
  to.Zero();
}

ON_Line::ON_Line( const ON_3dPoint& from_pt, const ON_3dPoint& to_pt )
: from(from_pt), to(to_pt)
{}

ON_Line::~ON_Line()
{}
ON_3dPoint& ON_Line::operator[](int i)
{
  return (i<=0) ? from : to;
}
const ON_3dPoint& ON_Line::operator[](int i) const
{
  return (i<=0) ? from : to;
}
bool ON_Line::Create( const ON_3dPoint& from_pt, const ON_3dPoint& to_pt )
{
  from = from_pt;
  to = to_pt;
  return IsValid();
}
bool ON_Line::IsValid() const
{
  return (from != to && from.IsValid() && to.IsValid());
}
double ON_Line::Length() const
{
  return from.DistanceTo(to);
}
ON_3dPoint ON_Line::PointAt( double t ) const
{
  // 26 Feb 2003 Dale Lear
  //     Changed 
  //          return (1-t)*from + t*to;
  //     to the following so that axis aligned lines will
  //     return exact answers for large values of t.  
  //     See RR 9683.
  const double s = 1.0-t;
  return  ON_3dPoint( (from.x == to.x) ? from.x : s*from.x + t*to.x,
                      (from.y == to.y) ? from.y : s*from.y + t*to.y,
                      (from.z == to.z) ? from.z : s*from.z + t*to.z );
}
void ON_Line::Reverse()
{
  ON_3dPoint tmp = from;
  from = to;
  to = tmp;
}
ON_3dVector ON_Line::Direction() const
{
  return (to-from);
}
bool ON_Line::ClosestPointTo( const ON_3dPoint& point, double *t ) const
{
  bool rc = false;
  if ( t ) {
    const ON_3dVector D = Direction();
    const double DoD = D.LengthSquared();
    if ( DoD > 0.0 ) {
      if ( point.DistanceTo(from) <= point.DistanceTo(to) ) {
        *t = ((point - from)*D)/DoD;
      }
      else {
        *t = 1.0 + ((point - to)*D)/DoD;
      }
      rc = true;
    }
    else {
      *t = 0.0;
    }
  }
  return rc;
}
ON_3dPoint ON_Line::ClosestPointTo( const ON_3dPoint& point ) const
{
  double t;
  ClosestPointTo( point, &t );
  return PointAt(t);
}
double ON_Line::DistanceTo( ON_3dPoint test_point ) const
{
  return test_point.DistanceTo(ClosestPointTo(test_point));
}
bool ON_Line::Transform( const ON_Xform& tr )
{
  from = tr*from;
  to = tr*to;
  // 5 June 2003 Dale Lear RR 10493
  //    Always return true.
  //return (from != to) ? true : false;
  return true;
}