#ifndef _POINT_H_
#define _POINT_H_

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define X  0
#define Y  1

class Point{
private:

	double x,y;

public:
	
	Point(void);
	Point(double _x, double _y);
	Point(const Point& p);

	inline Point& operator = (const Point &p);
	inline Point  operator + (const Point &p);
	inline Point  operator * (const double &k);
	inline double  operator * (const Point &p);
	inline Point  operator - (const Point &p) const;
	inline Point  operator / (const double &k);
	inline Point& operator +=(const Point &p);
	inline Point& operator -=(const Point &p);
	inline Point& operator *=(const double &k);
	inline bool	  operator ==(const Point &a) const;
	inline bool   operator < (const Point &a) const;
	inline double  operator [](unsigned int i) const;
	inline double& operator [](unsigned int i);
	inline void   LineTo(const Point& q,double *A,double *B,double *C);

	friend inline Point operator * (const double &k,const Point &a);
	friend inline Point operator + (const Point &a, const Point &b);

	inline void set(const double &_x,const double &_y){
		x = _x;
		y = _y;
	}

	inline double lentgh(void){
		return sqrt(x*x + y*y);
	}

	inline void print(char *txt){
		printf("%s (%f,%f)\n",txt,x,y);
	}

};
//======================================================================//
inline Point& Point::operator = (const Point &p){
	x = p[X];
	y = p[Y];
	return (*this);
}
//======================================================================//
inline Point Point::operator + (const Point &p){
	Point sum(x + p[X], y + p[Y]);
	return sum;
}
//======================================================================//
inline Point operator + (const Point &a, const Point &b){
	Point sum(a[X] + b[X], a[Y] + b[Y]);
	return sum;
}
//======================================================================//
inline Point Point::operator - (const Point &p) const {
	Point diff(x - p[X], y - p[Y]);
	return diff;
}
//======================================================================//
inline Point Point::operator * (const double &k){
	Point escdot(x*k, y*k);
	return escdot;
}
//======================================================================//
inline Point operator *(const double &k,const Point &a){
	Point mult = a;
	return (mult*=k);
}
//======================================================================//
inline double Point::operator * (const Point &p){
	return (x*p[X] + y*p[Y]);
}
//======================================================================//
inline Point Point::operator /(const double &k){
	assert(k!=0);
	Point div(x/k, y/k);
	return (div);
}
//======================================================================//
inline Point& Point::operator +=(const Point &p){
	x += p[X];
	y += p[Y];

	return (*this);
}
//======================================================================//
inline Point& Point::operator -=(const Point &p){
	x -= p[X];
	y -= p[Y];

	return (*this);
}
//======================================================================//
inline Point& Point::operator *=(const double &k){
	x *= k;
	y *= k;

	return (*this);
}
//======================================================================//
inline bool Point::operator == (const Point &a) const{
	
	if(x == a[X] && y == a[Y])
		return true;

	return false;
}
//======================================================================//
inline bool Point::operator < (const Point &a) const{

	if( x <= a[X] ) 
		return true;

	return false;

}

//======================================================================//
inline double Point::operator [] (unsigned int i) const {
	assert(i<2);
	switch(i){
		case 0: return x; break;
		case 1: return y; break;
	};
	return x;
}
//======================================================================//
inline double & Point::operator [] (unsigned int i) {
	assert(i<2);
	switch(i){
		case 0: return x; break;
		case 1: return y; break;
	}
	return x;
}
//======================================================================//
inline void Point::LineTo(const Point& q,double *A,double *B,double *C){
	*A = q[Y] - y;
	*B = x - q[X];
	*C = y*q[X] - q[Y]*x;
}
//======================================================================//
#endif
