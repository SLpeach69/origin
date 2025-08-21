#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>

class ClientQueue {
private:
    std::atomic<int> client_count;
    int max_clients;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> clients_finished;

public:
    ClientQueue(int max) : client_count(0), max_clients(max), clients_finished(false) {}

    void addClient() {
        std::unique_lock<std::mutex> lock(mtx);
        int current_count = client_count.load(std::memory_order_acquire);

        if (current_count < max_clients) {
            client_count.fetch_add(1, std::memory_order_release);
            std::cout << "New client arrived! Total clients: " << client_count.load(std::memory_order_relaxed) << std::endl;
            cv.notify_all();
        }
        else {
            clients_finished.store(true, std::memory_order_release);
            cv.notify_all();
        }
    }

    void serveClient() {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [this]() {
            return client_count.load(std::memory_order_acquire) > 0 ||
                (clients_finished.load(std::memory_order_acquire) &&
                    client_count.load(std::memory_order_acquire) == 0);
            });

        int current_count = client_count.load(std::memory_order_acquire);
        if (current_count > 0) {
            client_count.fetch_sub(1, std::memory_order_release);
            std::cout << "Client served! Clients remaining: " << client_count.load(std::memory_order_relaxed) << std::endl;
            cv.notify_all();
        }
    }

    bool shouldStopAddingClients() {
        return clients_finished.load(std::memory_order_acquire);
    }

    bool isWorkFinished() {
        return clients_finished.load(std::memory_order_acquire) &&
            client_count.load(std::memory_order_acquire) == 0;
    }

    int getClientCount() {
        return client_count.load(std::memory_order_acquire);
    }

    void testMemoryOrdering() {
        std::cout << "\nTesting different memory ordering modes:\n";

        client_count.store(10, std::memory_order_seq_cst);
        std::cout << "Seq_cst store: " << client_count.load(std::memory_order_seq_cst) << std::endl;

        client_count.store(5, std::memory_order_release);
        std::cout << "Release store: " << client_count.load(std::memory_order_acquire) << std::endl;

        client_count.store(3, std::memory_order_relaxed);
        std::cout << "Relaxed store: " << client_count.load(std::memory_order_relaxed) << std::endl;

        client_count.fetch_add(2, std::memory_order_seq_cst);
        std::cout << "Seq_cst fetch_add: " << client_count.load(std::memory_order_relaxed) << std::endl;

        client_count.fetch_sub(1, std::memory_order_release);
        std::cout << "Release fetch_sub: " << client_count.load(std::memory_order_acquire) << std::endl;
    }
};

void clientThread(ClientQueue& queue) {
    while (!queue.shouldStopAddingClients()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Ускорим для тестов
        queue.addClient();
    }
    std::cout << "Maximum client capacity reached. No new clients accepted." << std::endl;
}

void operatorThread(ClientQueue& queue) {
    while (!queue.isWorkFinished()) {
        queue.serveClient();
        if (!queue.isWorkFinished()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Ускорим для тестов
        }
    }
    std::cout << "All clients served. Operator is finishing work." << std::endl;
}

void stressTest(ClientQueue& queue, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        queue.addClient();
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

int main() {
    int max_clients;
    std::cout << "Enter maximum number of clients: ";
    std::cin >> max_clients;

    ClientQueue queue(max_clients);

    queue.testMemoryOrdering();

    std::cout << "\nStarting main simulation...\n";

    std::thread client(clientThread, std::ref(queue));
    std::thread operator_(operatorThread, std::ref(queue));

    std::thread stress1(stressTest, std::ref(queue), 10);
    std::thread stress2(stressTest, std::ref(queue), 10);

    client.join();
    operator_.join();
    stress1.join();
    stress2.join();

    std::cout << "Final client count: " << queue.getClientCount() << std::endl;
    std::cout << "Work finished: " << (queue.isWorkFinished() ? "Yes" : "No") << std::endl;
    std::cout << "Program completed." << std::endl;

    return 0;
}