// create a thread pool from scratch

// use hardware_concurrency as a default number of threads

// thread pool lives forever for now

// pass a function to execute on first available thread

// update the ui when the function completes, regardless of order of completion

// lets just allow people to subscribe to when new output is available and
// make the thread pool fit to purpose for now

// no resizing or restarting thread pool for now. stop on destruct.

#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
#include <vector>

using namespace std;

namespace combat {

template <typename T> class WorkQueue {
private:
  vector<thread> threads;
  atomic<bool> exit;

  mutex work_mutex;
  condition_variable work_avail;
  deque<function<T(void)>> work;

  mutex output_mutex;
  condition_variable output_avail;
  deque<T> output;

  mutex listeners_mutex;
  vector<function<void(T)>> listeners;

public:
  WorkQueue() : exit(false) {
    int num_threads = thread::hardware_concurrency();

    for (int i = 0; i < num_threads; i++) {
      threads.push_back(std::thread([&] {
        while (true) {
          auto task = wait_for_work();

          if (task == nullopt) {
            return;
          }

          scoped_lock out_lock(output_mutex);

          T val = task.value()();

          for (auto l : listeners) {
            l(val);
          }
        }
      }));
    }
  }

  optional<function<T()>> wait_for_work() {
    unique_lock work_lock(work_mutex);

    work_avail.wait(work_lock, [&] { return !work.empty() || exit; });

    if (exit) {
      return nullopt;
    }

    auto task = work.front();
    work.pop_front();

    return task;
  }

  void push_work(function<T()> task) {
    bool was_empty = false;

    {
      scoped_lock work_lock(work_mutex);
      was_empty = work.empty();
      work.push_back(task);
    }

    if (was_empty) {
      work_avail.notify_one();
    }
  }

  // subscribe to work output
  void subscribe(function<void(T)> l) {
    scoped_lock lock(listeners_mutex);
    listeners.push_back(l);
  }

  void stop() {
    exit = true;
    work_avail.notify_all();
  }

  ~WorkQueue() {
    stop();

    for (auto &t : threads)
      t.join();
  }
};
} // namespace combat