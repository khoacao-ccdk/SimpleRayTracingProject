/*
* HitableList class
* Used to keep track of the objects that the light ray hits
*/
#ifndef HitableList_H
#define HitableList_H

#include "Hitable.h"

class HitableList: public Hitable{
public:
	Hitable** list;
	float list_size;
	HitableList();
	HitableList(Hitable** l, float size);
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;
};

#endif
