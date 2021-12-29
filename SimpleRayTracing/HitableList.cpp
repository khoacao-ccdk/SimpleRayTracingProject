#include "HitableList.h"

HitableList::HitableList() {}

HitableList::HitableList(Hitable** l, float size){
	list = l;
	list_size = size;
}

bool HitableList::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record t_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for(int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, closest_so_far, t_rec)) {
			hit_anything = true;
			closest_so_far = t_rec.t;
			rec = t_rec;
		}
	}
	return hit_anything;
}