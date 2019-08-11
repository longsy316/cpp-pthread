//
// Created by Herbert Koelman on 2019-07-28.
//

#include <pthread.h>
#include "pthread/pthread.hpp"
#include "gtest/gtest.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include <ctime>

class test_runnable : public pthread::runnable {
public:

    void run() noexcept override {
        try {
            long counter = 0;
            display_message("test_runnable is running ");
            pthread::this_thread::sleep_for(2 * 1000);
            for (auto count = 1000; count > 0; count--) {
                counter += count;
            }

//            std::string input ;
//            std::cout << "Type enter to continue." << std::endl;
//            std::getline(std::cin, input);

            display_message( "done " );
        } catch (const std::exception &err) {
            display_error(std::string{"something went wrong while running test_runnable. "} + err.what() );
        } catch (...) {
            display_error(std::string{"unexpected exception catched in test_runnable."} + __FUNCTION__ + " method.");
        }
    }

    test_runnable( const std::string &message): _message{message}{
        // intentional
    }

private:

    void display_message( const std::string &message){
        auto thid = pthread::this_thread::get_id();
        std::cout << _message << ": "<< message << " (" << thid << ")" << std::endl << std::flush;
    }

    void display_error( const std::string &message){
        auto thid = pthread::this_thread::get_id();
        std::cerr << _message << ": "<< message << " (" << thid << ")" << std::endl << std::flush;
    }

    std::string _message;
};

void display_context_infos(){
    auto thid = pthread::this_thread::get_id();
    std::string test_case_name = ::testing::UnitTest::GetInstance()->current_test_case()->name();
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "| running test case: " << test_case_name << "." << test_name << " (test running thread ID: [" << thid << "])." << std::endl;
    std::cout << std::endl <<std::flush;
}

TEST(thread, join) {
    display_context_infos();

    std::string test_case_name = ::testing::UnitTest::GetInstance()->current_test_case()->name();
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    try {
        std::unique_ptr<test_runnable> tr{new test_runnable{"join test"}};
        pthread::thread t{*tr}; // this starts running the thread

        EXPECT_TRUE(t.joinable());
        t.join();
    } catch (std::exception &err) {
        std::cerr << "something went wrong in test " << test_case_name << "." << test_name << ". " << err.what() << std::endl;
        std::cerr << std::flush;
        FAIL();
    }
}

TEST(thread, status) {
    display_context_infos();

    std::unique_ptr<test_runnable> tr{new test_runnable{"status test"}};

    pthread::thread t{*tr}; // this starts running the thread

    EXPECT_EQ(t.status(), pthread::thread_status::a_thread);

    t.join();
}

TEST(thread, thread_constructor) {
    display_context_infos();

    try {
        pthread::thread t1;
        EXPECT_EQ(t1.status(), pthread::thread_status::not_a_thread);

        std::unique_ptr<test_runnable> tr{new test_runnable{"constructor test"}};
        pthread::thread t2{*tr};
        EXPECT_EQ(t2.status(), pthread::thread_status::a_thread);
        t2.join();
    } catch ( std::exception &err ){
        std::cerr << "thread_constructor test failed. " << err.what() << std::endl ;
    }
}

TEST(thread, move_operator) {

    display_context_infos();

    std::unique_ptr<test_runnable> tr{new test_runnable{"move operator test"}};
    pthread::thread T1{*tr}; // this starts running the thread
    EXPECT_EQ(T1.status(), pthread::thread_status::a_thread); // at this point t& is a running thread

    pthread::thread T2 = std::move(T1); // t2 becomes the running thread and T1 is not a thread anymore
    EXPECT_EQ(T2.status(), pthread::thread_status::a_thread); // T2 is the running thread
    EXPECT_EQ(T1.status(), pthread::thread_status::not_a_thread); // T1 is no longer a thread

    // join shouldn't throw an exception because when t1 was moved to t2, t2 is not a thread anymore
    EXPECT_NO_THROW(T1.join());

    T2.join();
    EXPECT_NO_THROW(T2.join());
}
