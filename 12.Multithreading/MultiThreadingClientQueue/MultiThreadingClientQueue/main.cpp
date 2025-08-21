#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class ClientQueue {
private:
    mutable std::mutex mtx;
    int client_count;
    int max_clients;
    std::condition_variable cv;
    bool clients_finished;

public:
    ClientQueue(int max) : client_count(0), max_clients(max), clients_finished(false) {}

    void addClient() {
        std::unique_lock<std::mutex> lock(mtx);
        if (client_count < max_clients) {
            client_count++;
            std::cout << "New client arrived! Total clients: " << client_count << std::endl;
            cv.notify_all();
        }
        else {
            clients_finished = true;
            cv.notify_all();
        }
    }

    void serveClient() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return client_count > 0 || (clients_finished && client_count == 0); });

        if (client_count > 0) {
            client_count--;
            std::cout << "Client served! Clients remaining: " << client_count << std::endl;
            cv.notify_all();
        }
    }

    bool shouldStopAddingClients() {
        std::lock_guard<std::mutex> lock(mtx);
        return clients_finished;
    }

    bool isWorkFinished() {
        std::lock_guard<std::mutex> lock(mtx);
        return clients_finished && client_count == 0;
    }

    int getClientCount() {
        std::lock_guard<std::mutex> lock(mtx);
        return client_count;
    }
};

void clientThread(ClientQueue& queue) {
    while (!queue.shouldStopAddingClients()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        queue.addClient();
    }
    std::cout << "Maximum client capacity reached. No new clients accepted." << std::endl;
}

void operatorThread(ClientQueue& queue) {
    while (!queue.isWorkFinished()) {
        queue.serveClient();
        if (!queue.isWorkFinished()) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    std::cout << "All clients served. Operator is finishing work." << std::endl;
}

int main() {
    int max_clients;
    std::cout << "Enter maximum number of clients: ";
    std::cin >> max_clients;

    ClientQueue queue(max_clients);

    std::thread client(clientThread, std::ref(queue));
    std::thread operator_(operatorThread, std::ref(queue));

    client.join();
    operator_.join();

    std::cout << "Program completed." << std::endl;
    return 0;
}