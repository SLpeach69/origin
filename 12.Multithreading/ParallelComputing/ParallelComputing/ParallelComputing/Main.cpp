#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <iomanip>

class VectorSumCalculator {
private:
    size_t hardware_threads;

public:
    VectorSumCalculator() {
        hardware_threads = std::thread::hardware_concurrency();
        std::cout << "Available hardware cores: " << hardware_threads << std::endl;
    }

    void calculatePartialSum(const std::vector<int>& vec1, const std::vector<int>& vec2,
        std::vector<int>& result, size_t start, size_t end) {
        for (size_t i = start; i < end; i++) {
            result[i] = vec1[i] + vec2[i];
        }
    }

    long long measureExecutionTime(const std::vector<int>& vec1, const std::vector<int>& vec2,
        std::vector<int>& result, int num_threads) {
        size_t n = vec1.size();
        size_t chunk_size = n / num_threads;

        std::vector<std::thread> threads;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < num_threads; i++) {
            size_t start_idx = i * chunk_size;
            size_t end_idx = (i == num_threads - 1) ? n : start_idx + chunk_size;

            threads.emplace_back(&VectorSumCalculator::calculatePartialSum, this,
                std::ref(vec1), std::ref(vec2), std::ref(result),
                start_idx, end_idx);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    std::vector<int> generateRandomVector(size_t size, int min_val = 1, int max_val = 100) {
        std::vector<int> vec(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min_val, max_val);

        for (size_t i = 0; i < size; i++) {
            vec[i] = dis(gen);
        }
        return vec;
    }

    bool verifyResult(const std::vector<int>& vec1, const std::vector<int>& vec2,
        const std::vector<int>& result) {
        for (size_t i = 0; i < vec1.size(); i++) {
            if (result[i] != vec1[i] + vec2[i]) {
                return false;
            }
        }
        return true;
    }

    void runBenchmark() {
        std::vector<size_t> sizes = { 1000, 10000, 100000, 1000000 };
        std::vector<int> thread_counts = { 2, 4, 8, 16 };

        std::cout << "\nBenchmark Results (time in microseconds):\n";
        std::cout << "=====================================================================\n";
        std::cout << "Size\\Threads |";

        for (int threads : thread_counts) {
            std::cout << std::setw(10) << threads << " |";
        }
        std::cout << std::endl;
        std::cout << "=====================================================================\n";

        for (size_t size : sizes) {
            std::cout << std::setw(12) << size << " |";

            auto vec1 = generateRandomVector(size);
            auto vec2 = generateRandomVector(size);
            std::vector<int> result(size);

            for (int threads : thread_counts) {
                long long time = measureExecutionTime(vec1, vec2, result, threads);

                if (!verifyResult(vec1, vec2, result)) {
                    std::cout << " ERROR! |";
                }
                else {
                    std::cout << std::setw(10) << time << " |";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "=====================================================================\n";

        std::cout << "\nOptimal thread count analysis:\n";
        for (size_t size : sizes) {
            auto vec1 = generateRandomVector(size);
            auto vec2 = generateRandomVector(size);
            std::vector<int> result(size);

            long long best_time = LLONG_MAX;
            int best_threads = 0;

            for (int threads : thread_counts) {
                long long time = measureExecutionTime(vec1, vec2, result, threads);
                if (time < best_time) {
                    best_time = time;
                    best_threads = threads;
                }
            }

            std::cout << "Size " << std::setw(8) << size << ": optimal threads = "
                << best_threads << " (time: " << best_time << " ?s)" << std::endl;
        }
    }
};

int main() {
    VectorSumCalculator calculator;
    calculator.runBenchmark();

    return 0;
}