#pragma once

#include "hitable_list.h"

#include <iostream>

using namespace std;

struct bvh_node : public hitable
{
	bvh_node();
	bvh_node(hitable_list& list, float time0, float time1);
	bvh_node(vector<shared_ptr<hitable>>& objects, size_t start, size_t end, float time0, float time1);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const;

	shared_ptr<hitable> left;
	shared_ptr<hitable> right;
	aabb box;
};

