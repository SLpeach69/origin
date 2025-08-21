#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <chrono>

std::pair<int, int> find_min_async(const std::vector<int>& arr, int start_index) {
    if (arr.empty() || start_index >= arr.size()) {
        return { -1, -1 };
    }

    int min_index = start_index;
    int min_value = arr[start_index];

    for (int i = start_index + 1; i < arr.size(); ++i) {
        if (arr[i] < min_value) {
            min_value = arr[i];
            min_index = i;
        }
    }

    return { min_index, min_value };
}

void selection_sort_async(std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        std::promise<std::pair<int, int>> promise;
        std::future<std::pair<int, int>> future = promise.get_future();

        auto async_result = std::async(std::launch::async, [&promise, &arr, i]() {
            auto result = find_min_async(arr, i);
            promise.set_value(result);
            });

        auto [min_index, min_value] = future.get();

        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }

        std::cout << "Step " << i + 1 << ": ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

void selection_sort_sync(std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }

        std::cout << "Step " << i + 1 << ": ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> data = { 64, 25, 12, 22, 11, 8, 35, 42, 17, 9 };
    std::vector<int> data_copy = data;

    std::cout << "Original array: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    std::cout << "Async selection sort:\n";
    auto start_async = std::chrono::high_resolution_clock::now();
    selection_sort_async(data);
    auto end_async = std::chrono::high_resolution_clock::now();

    std::cout << "\nSorted array (async): ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    std::cout << "\nSync selection sort:\n";
    auto start_sync = std::chrono::high_resolution_clock::now();
    selection_sort_sync(data_copy);
    auto end_sync = std::chrono::high_resolution_clock::now();

    std::cout << "Sorted array (sync): ";
    for (int num : data_copy) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    auto async_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_async - start_async);
    auto sync_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_sync - start_sync);

    std::cout << "Async sort time: " << async_duration.count() << " microseconds\n";
    std::cout << "Sync sort time: " << sync_duration.count() << " microseconds\n";

    return 0;
}