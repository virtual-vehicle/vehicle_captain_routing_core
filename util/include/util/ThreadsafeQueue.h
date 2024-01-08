//
// Created by <Christoph Pilz> on 20.07.2021.
//
// Description:
// Thread-Safe Queue, provided by Sarah Haas
//
// Author(s): "Sarah Haas", "Christoph Pilz"
// Copyright: "Copyright 2021, VIF V2X Platform Project"
// Credits: ["Sarah Haas"]
// License: "TBD"
// Version: "TBD"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// Possible Improvements:
// [] (refactor) upgrade to C++17 (Full original Code), as soon as project is C++17
//

#include <algorithm>
#include <iostream>
#include <mutex>
//#include <optional> //C++17
#include <experimental/optional>
#include <queue>
#include <thread>

using namespace std;

#pragma once

template <typename T>
class ThreadsafeQueue {
    std::queue<T> queue_;
    mutable std::mutex mutex_;

//    [[nodiscard]] bool empty() const { //C++17
    bool empty() const {
        return queue_.empty();
    }

   public:
    ThreadsafeQueue() = default;
    ThreadsafeQueue(const ThreadsafeQueue<T>&) = delete;
    ThreadsafeQueue& operator=(const ThreadsafeQueue<T>&) = delete;

    ThreadsafeQueue(ThreadsafeQueue<T>&& other) noexcept(false) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!empty()) {
            //throw non_empty_queue("Moving into a non-empty queue"s);
        }
        queue_ = std::move(other.queue_);
    }

    virtual ~ThreadsafeQueue() noexcept(false) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!empty()) {
            //throw non_empty_queue("Destroying a non-empty queue"s);
        }
    }

//    [[nodiscard]] unsigned long size() const { //C++17
    unsigned long size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

//    std::optional<T> pop() { //C++17
    std::experimental::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return {};
        }
        T tmp = queue_.front();
        queue_.pop();
        return tmp;
    }

    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
    }
};
