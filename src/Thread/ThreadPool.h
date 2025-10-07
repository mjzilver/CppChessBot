#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();
    void submit(std::function<void()> task);
    void join();

private:
    unsigned int nThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable cv;

    std::atomic<bool> stop = false;

    void workerLoop();
};