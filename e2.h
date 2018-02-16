//
// Created by Brian Swenson on 2/8/18.
//

#ifndef E2_E2_H
#define E2_E2_H

#include <numeric>
#include <future>

struct async_result_t {
	long sum;
	int min;
	int max;

	async_result_t& operator += (const async_result_t& r) {
		this->max = this->max > r.max ? this->max : r.max;
		this->min = this->min < r.min ? this->min : r.min;
		this->sum += r.sum;
		return *this;
	}
};

auto calc(int* start, size_t count) {
	//async_result_t res;
	//res.sum = 
	return std::accumulate(start, start + count, 0);
	//res.min = *std::min_element(start, start + count);
	//res.max = *std::max_element(start, start + count);
	//return res;
}

auto parallel_acc(std::vector<int>& v, unsigned int n) -> long unsigned int {
    auto f = std::vector<std::future<long>>(n);

	unsigned num_threads = std::thread::hardware_concurrency();
    for(auto i = 0u; i < n; ++i) {
		f[i] = std::async(std::launch::async, calc,
			v.data() + (i * v.size() / num_threads), v.size() / num_threads);
    }

	std::accumulate(f.begin(), f.end(), 0l, [] (auto sum, auto& fut) { return sum + fut.get(); });
}

//async_result_t async_calc(std::vector<int>& v) {
//	async_result_t total = {0};
//	unsigned num_threads = std::thread::hardware_concurrency();
//    auto future_vec = std::vector<std::future<long>>(num_threads);
//	for (auto i = 0; i < num_threads; ++i) {
//		total += std::async(std::launch::async, calc,
//			v.data() + (i * v.size() / num_threads), v.size() / num_threads).get();
//	}
//	return total;
//}

#endif //E2_E2_H
