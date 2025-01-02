//
// Created by apin on 20.12.2024.
//

#ifndef VINS_FOCUS_NODE_HPP
#define VINS_FOCUS_NODE_HPP


#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include <vector>
#include <mutex>
#include <condition_variable>


namespace vins {
namespace core {
namespace transport {


class Node {
public:
    /*********Public fields*********/


    /*********Public methods*********/
    explicit Node(const std::string &name) : _name(name), _running(false) {}

    virtual ~Node() {
        stop();
    }

    virtual void init() = 0;

    void start() {
        _running = true;
        _worker_thread = std::thread(&Node::run, this);
    }

    void stop() {
        _running = false;
        if (_worker_thread.joinable()) {
            _worker_thread.join();
        }
    }

    void subscribe(const std::function<void()> &callback) {
        std::lock_guard<std::mutex> lock(_mutex);
        _callbacks.push_back(callback);
    }

    void publish() {
        std::lock_guard<std::mutex> lock(_mutex);
        for (const auto &callback : _callbacks) {
            callback();
        }
    }

protected:
    /*********Protected fields*********/
    std::string _name;
    std::atomic<bool> _running;
    std::thread _worker_thread;
    std::vector<std::function<void()>> _callbacks;
    std::mutex _mutex;
    std::condition_variable _cv;

    /*********Protected methods*********/
    virtual void run() = 0;


private:
    /*********Private fields*********/


    /*********Private methods*********/

};

}; // namespace transport
}; // namespace core
}; // namespace vins


#endif //VINS_FOCUS_NODE_HPP
