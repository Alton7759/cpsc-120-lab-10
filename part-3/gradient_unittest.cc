// Christian Alton bonilla
// CPSC 120-01
// 2022-11-14
// Alton77@csu.fullerton.edu
// @alton7759
//
// Lab 10-03
// Partners: @annavera38
//
// units
//
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>
#include <limits.h>

#include <cstdio>
#include <future>

#include "gradient_functions.h"

// Thanks to Paul Inventado
// https://github.com/google/googletest/issues/348#issuecomment-431714269
// Fail immediately.
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

// Tests bool HasMatchingFileExtension(const std::string& file_name, const
// std::string& extension);
TEST(HasMatchingFileExtension, Exists) {
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(true, HasMatchingFileExtension("image.jpg", ".jpg")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(true, HasMatchingFileExtension("image.png", ".png")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(true, HasMatchingFileExtension("image.JPEG", ".JPEG")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(true, HasMatchingFileExtension("image.GIF", ".GIF")));
}

TEST(HasMatchingFileExtension, NotExist) {
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(false, HasMatchingFileExtension("image.jpg", ".foo")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(false, HasMatchingFileExtension("image.png", ".foo")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(false, HasMatchingFileExtension(".fo", ".foo")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(false, HasMatchingFileExtension("image.FOO", ".foo")));
}

}  // namespace
