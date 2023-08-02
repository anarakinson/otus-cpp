#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


namespace monitor {

    template <typename T>
    class Monitor {
    public:
        template <typename... Args>
        Monitor(Args &&...args) : m_container{std::forward<Args>(args)...} {}  // push all arguments to monitored container as is via std::forward

        // wrapper class locking monitors mutex when created
        class helper {
        public:
            helper(Monitor *monitor) : 
                m_parent{monitor},         // wrap self
                m_lock{monitor->m_mutex}   // lock mutex
                {}

            T *operator -> () { return &m_parent->m_container; }

        private:
            Monitor *m_parent;
            std::lock_guard<std::mutex> m_lock;
        };

        helper operator -> () { return helper(this); }   // create helper and wrap self with it

    private:
        T m_container;
        std::mutex m_mutex;
    };


    void example() {

        Monitor<std::vector<int>> thread_safe_vector{1, 2, 3, 4, 5};

        auto lambda = [] (Monitor<std::vector<int>> &vec, int start = 0, int end = 10) {
            for (int i = start; i < end; ++i) {
                vec->push_back(i);
            }
        };

        std::thread thread1{lambda, std::ref(thread_safe_vector)};
        std::thread thread2{lambda, std::ref(thread_safe_vector), 10, 14};
        std::thread thread3{lambda, std::ref(thread_safe_vector), 111, 120};

        thread1.join();
        thread2.join();
        thread3.join();

        for (int i = 0; i < thread_safe_vector->size(); ++i) {
            std::cout << thread_safe_vector->data()[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << thread_safe_vector->size() << std::endl;

    }

} // namespace monitor


int main(/* int argc, char **argv */) {

    monitor::example();

    return 0;

}
