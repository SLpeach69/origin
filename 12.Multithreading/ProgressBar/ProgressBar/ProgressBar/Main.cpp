#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <random>

class ProgressBar {
private:
    static std::mutex cout_mutex;
    const int bar_width = 50;

public:
    void update(int thread_num, std::thread::id thread_id,
        int progress, int total, long long elapsed_time) {
        std::lock_guard<std::mutex> lock(cout_mutex);


        std::cout << "\033[" << (thread_num + 3) << ";1H";
        std::cout << "\033[K";

        std::cout << "Thread " << thread_num << " (ID: " << thread_id << ") [";

        int pos = bar_width * progress / total;
        for (int i = 0; i < bar_width; ++i) {
            if (i < pos) std::cout << "#";
            else std::cout << "-";
        }

        std::cout << "] " << (100 * progress / total) << "%";
        std::cout << " Time: " << elapsed_time << "ms";

        if (progress >= total) {
            std::cout << " - COMPLETED";
        }

        std::cout.flush();
    }
};

std::mutex ProgressBar::cout_mutex;

void calculate_task(int thread_num, int calculation_length, ProgressBar& progress_bar) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::thread::id thread_id = std::this_thread::get_id();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(50, 200);

    for (int i = 0; i <= calculation_length; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));

        auto current_time = std::chrono::high_resolution_clock::now();
        long long elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            current_time - start_time).count();

        progress_bar.update(thread_num, thread_id, i, calculation_length, elapsed_time);
    }
}

int main() {
    int num_threads;
    int calculation_length;

    std::cout << "Enter number of threads: ";
    std::cin >> num_threads;

    std::cout << "Enter calculation length: ";
    std::cin >> calculation_length;

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Multithreaded Progress Bars:\n";
    std::cout << "============================\n";

    for (int i = 0; i < num_threads; ++i) {
        std::cout << "Thread " << i << " initializing...\n";
    }
    std::cout.flush();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ProgressBar progress_bar;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(calculate_task, i, calculation_length, std::ref(progress_bar));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "\033[" << (num_threads + 4) << ";1H";
    std::cout << "All calculations completed!\n";

    return 0;
}