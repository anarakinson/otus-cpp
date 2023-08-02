#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>


constexpr static int ProductsCount = 100;


namespace cond_var {

    template <typename T>
    class Queue {
    public:
        void push(T value) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_queue.push(value);
            m_cond_var.notify_one();
        }

        // Takes entry with waiting is case of empty queue
        bool pop(int &value) {
            std::unique_lock<std::mutex> lock(m_mutex);
            auto lambda = [this] () {
                return (!m_queue.empty() || m_stopped);
            };
            m_cond_var.wait(lock, lambda);

            bool no_more = m_queue.empty() && m_stopped;

            if (!m_queue.empty()) {
                value = m_queue.front();
                m_queue.pop();
            }
            return !no_more;
        }

        // Notificates all threads to unlock them
        void stop() {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_stopped = true;
            m_cond_var.notify_all();
        }

    private:
        std::condition_variable m_cond_var;
        std::mutex m_mutex;
        std::queue<T> m_queue;
        bool m_stopped = false;
    };


    void example() {
        Queue<int> queue;
        int total{};

        std::thread producer = std::thread([&] () {
            for (int i = 0; i < ProductsCount; ++i) {
                queue.push(i);
            }
            queue.stop();
        });

        std::thread consumer = std::thread([&] () {
            int value{};

            while (queue.pop(value)) {
                total += value;
            }
        });

        producer.join();
        consumer.join();

        std::cout << total << std::endl;
        std::cout << ProductsCount * (ProductsCount - 1) / 2 << std::endl;
    }

} // namespace cond_var


int main() {

    cond_var::example();

    return 0;

}