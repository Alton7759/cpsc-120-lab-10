// Christian Alton bonilla
// CPSC 120-01
// 2022-11-14
// Alton77@csu.fullerton.edu
// @alton7759
//
// Lab 10-01
// Partners: @annavera38
//
// Calculate the area of a triangle defined by length and width.
//
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>

#include <climits>
#include <cstdio>
#include <future>

#include "rectangle_area_functions.h"

// Thanks to Paul Inventado
// https://github.com/google/googletest/issues/348#issuecomment-431714269
// Fail immediately.
// NOLINT(cppcoreguidelines-macro-usage)
#define ASSERT_DURATION_LE(millisecs, stmt)                                 \
  {                                                                         \
    std::promise<bool> completed;                                           \
    auto stmt_future = completed.get_future();                              \
    std::thread(                                                            \
        [&](std::promise<bool>& completed) {                                \
          stmt;                                                             \
          completed.set_value(true);                                        \
        },                                                                  \
        std::ref(completed))                                                \
        .detach();                                                          \
    if (stmt_future.wait_for(std::chrono::milliseconds(millisecs)) ==       \
        std::future_status::timeout)                                        \
      GTEST_FATAL_FAILURE_("\tExecution time greater than " #millisecs      \
                           " milliseconds.\n\tRevise algorithm for better " \
                           "performance and check for "                     \
                           "infinite loops.");                              \
  }

// Defer failure
// NOLINT(cppcoreguidelines-macro-usage)
#define EXPECT_DURATION_LE(millisecs, stmt)                                    \
  {                                                                            \
    std::promise<bool> completed;                                              \
    auto stmt_future = completed.get_future();                                 \
    std::thread(                                                               \
        [&](std::promise<bool>& completed) {                                   \
          stmt;                                                                \
          completed.set_value(true);                                           \
        },                                                                     \
        std::ref(completed))                                                   \
        .detach();                                                             \
    if (stmt_future.wait_for(std::chrono::milliseconds(millisecs)) ==          \
        std::future_status::timeout)                                           \
      GTEST_NONFATAL_FAILURE_("\tExecution time greater than " #millisecs      \
                              " milliseconds.\n\tRevise algorithm for better " \
                              "performance and check for "                     \
                              "infinite loops.");                              \
  }
namespace {

// Tests RectangleArea()

// Tests negative input.
TEST(RectangleAreaTest, Negative) {
  EXPECT_DURATION_LE(5, EXPECT_EQ(0, RectangleArea(-10, 4)));
  EXPECT_DURATION_LE(5, EXPECT_EQ(0, RectangleArea(-10, -4)));
  EXPECT_DURATION_LE(5, EXPECT_EQ(0, RectangleArea(10, -4)));
  EXPECT_DURATION_LE(5, EXPECT_EQ(0, RectangleArea(0, 0)));
  EXPECT_DURATION_LE(5, EXPECT_EQ(0, RectangleArea(0, 123)));
  EXPECT_DURATION_LE(5, EXPECT_EQ(0, RectangleArea(123, 0)));
}

// Tests some trivial cases.
TEST(RectangleAreaTest, Positive) {
  EXPECT_DURATION_LE(5, EXPECT_EQ(1, RectangleArea(1, 1)));
  EXPECT_DURATION_LE(5, EXPECT_EQ(164034, RectangleArea(701, 234)));
  EXPECT_DURATION_LE(5, EXPECT_EQ(4478819, RectangleArea(2371, 1889)));
}

}  // namespace
