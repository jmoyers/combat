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
  condition_variable empty;

  mutex work_mutex;
  condition_variable work_avail;
  deque<function<T(void)>> work;

  mutex listeners_mutex;
  vector<function<void(T)>> listeners;

public:
  WorkQueue() : exit(false) {
    int num_threads = thread::hardware_concurrency();

    for (int i = 0; i < num_threads; i++) {
      threads.push_back(std::thread([&] {
        while (true) {
          auto task = wait_for_work();

          // threads cancelled with stop()
          if (task == nullopt) {
            return;
          }

          T val = task.value()();

          scoped_lock lock(listeners_mutex, work_mutex);

          for (auto l : listeners) {
            l(val);
          }

          if (work.empty())
            empty.notify_one();
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

  void subscribe(function<void(T)> l) {
    scoped_lock lock(listeners_mutex);
    listeners.push_back(l);
  }

  void join() {
    unique_lock lock(work_mutex);
    empty.wait(lock, [&]() { return work.empty(); });
  }

  void stop() {
    if (exit)
      return;
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