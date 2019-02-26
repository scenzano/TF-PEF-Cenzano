#ifndef _COMPARABLE_H
#define	_COMPARABLE_H

#include<iostream>
#include "object.h"

class Comparable : public Object
{
            public:
        
        Comparable();
        virtual ~Comparable();
	virtual int compareTo(Object *otro)=0;
};

#endif	/* _COMPARABLE_H */

