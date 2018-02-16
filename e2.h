//
// Created by Brian Swenson on 2/8/18.
//

#ifndef E2_E2_H
#define E2_E2_H

#include <numeric>
#include <future>

#define fmin(x, y) (x < y ? x : y)
#define fmax(x, y) (x > y ? x : y)

struct async_result_t {
	long sum;
	int min;
	int max;

	async_result_t operator + (const async_result_t& r) {
		async_result_t t;
		t.max = fmax(max, r.max); // max > r.max ? max : r.max;
		t.min = fmin(min, r.min); //min < r.min ? min : r.min;
		t.sum = sum + r.sum;
		return t;
	}
};

async_result_t async_calc(std::vector<int>&);

#endif //E2_E2_H
