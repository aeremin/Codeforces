#pragma once

#include <gtest/gtest.h>


class TestWithIORedirection : public ::testing::Test {
  public:
    TestWithIORedirection() {
        original_cin = std::cin.rdbuf();
        original_cout = std::cout.rdbuf();
        std::cin.rdbuf(in_buf.rdbuf());
        std::cout.rdbuf(out_buf.rdbuf());
    }
    ~TestWithIORedirection() {
        std::cin.rdbuf(original_cin);
        std::cout.rdbuf(original_cout);
    }

    void send_input(const std::string& in) { in_buf << in; }
    std::string get_output() { return out_buf.str(); }

  private:
    std::streambuf* original_cin = nullptr;
    std::streambuf* original_cout = nullptr;
    std::stringstream in_buf;
    std::stringstream out_buf;
};
