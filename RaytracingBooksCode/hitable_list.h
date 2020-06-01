#ifndef HITABLELISTH
#define HITABLELISTH

#include "vec3.h"
#include "hit_record.h"
#include "ray.h"
#include <vector>
#include "hitable_list.h"
#include "hitable.h"

struct hitable_list : public hitable
{
    hitable_list() {}

    hitable_list(vector<shared_ptr<hitable>> l)
    {
        objects = l;
    }

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& output_box) const override;

    void add(shared_ptr<hitable> object) {
        objects.push_back(object);
    }

    vector<shared_ptr<hitable>> objects;
};

#endif
