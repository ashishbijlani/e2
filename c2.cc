//
// Created by Brian Swenson on 2/8/18.
//

#include <iostream>
#include <vector>

#include "e2.h"

static auto seq_calc(int* start, size_t count) {
	async_result_t res;
	res.sum = std::accumulate(start, start + count, 0);
	res.min = *std::min_element(start, start + count);
	res.max = *std::max_element(start, start + count);
	return res;
}

static inline
auto acc(async_result_t r, std::future<async_result_t>& f) {
	return r + f.get();
}

async_result_t async_calc(std::vector<int>& v) {
	unsigned num_threads = std::thread::hardware_concurrency() << 2;
    auto fut = std::vector<std::future<async_result_t>>(num_threads);
	auto split = v.size() / num_threads;
    for(auto i = 0; i < num_threads; ++i)
		fut[i] = std::async(std::launch::async, seq_calc, v.data() + i * split, split);

	async_result_t res = {0/*sum*/, 1000/*min*/, 0/*max*/};
	return std::accumulate(fut.begin(), fut.end(), res, acc);
}

