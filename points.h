#ifndef _POINT_H_
#define _POINT_H_

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define X  0
#define Y  1

class Point{
private:

	float x,y;

public:
	
	Point(void);
	Point(float _x, float _y);
	Point(const Point& p);

	inline Point& operator = (const Point &p);
	inline Point  operator + (const Point &p);
	inline Point  operator * (const float &k);
	inline float  operator * (const Point &p);
	inline Point  operator - (const Point &p) const;
	inline Point  operator / (const float &k);
	inline Point& operator +=(const Point &p);
	inline Point& operator -=(const Point &p);
	inline Point& operator *=(const float &k);
	inline bool	  operator ==(const Point &a) const;
	inline bool   operator < (const Point &a) const;
	inline float  operator [](unsigned int i) const;
	inline float& operator [](unsigned int i);
	inline void   LineTo(const Point& q,float *A,float *B,float *C);

	friend inline Point operator * (const float &k,const Point &a);
	friend inline Point operator + (const Point &a, const Point &b);

	inline void set(const float &_x,const float &_y){
		x = _x;
		y = _y;
	}

	inline float lentgh(void){
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
inline Point Point::operator * (const float &k){
	Point escdot(x*k, y*k);
	return escdot;
}
//======================================================================//
inline Point operator *(const float &k,const Point &a){
	Point mult = a;
	return (mult*=k);
}
//======================================================================//
inline float Point::operator * (const Point &p){
	return (x*p[X] + y*p[Y]);
}
//======================================================================//
inline Point Point::operator /(const float &k){
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
inline Point& Point::operator *=(const float &k){
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
inline float Point::operator [] (unsigned int i) const {
	assert(i<2);
	switch(i){
		case 0: return x; break;
		case 1: return y; break;
	};
	return x;
}
//======================================================================//
inline float & Point::operator [] (unsigned int i) {
	assert(i<2);
	switch(i){
		case 0: return x; break;
		case 1: return y; break;
	}
	return x;
}
//======================================================================//
inline void Point::LineTo(const Point& q,float *A,float *B,float *C){
	*A = q[Y] - y;
	*B = x - q[X];
	*C = y*q[X] - q[Y]*x;
}
//======================================================================//
#endif
