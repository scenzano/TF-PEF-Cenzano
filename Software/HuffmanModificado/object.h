#ifndef _OBJECT_H
#define	_OBJECT_H

#include<iostream>
#include<string>
#include<cstdio>
#include<typeinfo>
using namespace std;

class Object
{
           public:
        
	Object();
	virtual ~Object();
	virtual bool equals( Object * otro );
	virtual int  hashCode();
};

#endif	/* _OBJECT_H */

