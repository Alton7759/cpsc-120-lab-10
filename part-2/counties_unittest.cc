
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>
#include <limits.h>

#include <cstdio>
#include <future>

#include "counties_functions.h"

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

std::vector<std::vector<std::string>> ca_counties{
    {{"Alameda",   "Alpine",        "Amador",       "Butte",
      "Calaveras", "Colusa",        "Contra Costa", "Del Norte",
      "El Dorado", "Fresno",        "Glenn",        "Humboldt",
      "Imperial",  "Inyo",          "Kern",         "Kings",
      "Lake",      "Lassen",        "Los Angeles",  "Madera",
      "Marin",     "Mariposa",      "Mendocino",    "Merced",
      "Modoc",     "Mono",          "Monterey",     "Napa",
      "Nevada",    "Orange",        "Placer",       "Plumas",
      "Riverside", "Sacramento",    "San Benito",   "San Bernardino",
      "San Diego", "San Francisco", "San Joaquin",  "San Luis Obispo",
      "San Mateo", "Santa Barbara", "Santa Clara",  "Santa Cruz",
      "Shasta",    "Sierra",        "Siskiyou",     "Solano",
      "Sonoma",    "Stanislaus",    "Sutter",       "Tehama",
      "Trinity",   "Tulare",        "Tuolumne",     "Ventura",
      "Yolo",      "Yuba"},
     {"1648556", "1235",   "41259",   "208309",  "46221",  "21917",
      "1161413", "28100",  "193221",  "1013581", "28805",  "136310",
      "179851",  "18970",  "917673",  "153443",  "68766",  "33159",
      "9829544", "159410", "260206",  "17147",   "91305",  "286461",
      "8661",    "13247",  "437325",  "136207",  "103487", "3167809",
      "412300",  "19915",  "2458395", "1588921", "66677",  "2194710",
      "3286069", "815201", "789410",  "283159",  "737888", "446475",
      "1885508", "267792", "182139",  "3283",    "44118",  "451716",
      "485887",  "552999", "99063",   "65498",   "16060",  "477054",
      "55810",   "839784", "216986",  "83421"}}};

// Tests std::string AllCountiesString(const std::array<std::array<std::string,
// 58>, 2>& ca_counties);

// "Alameda Alpine Amador Butte Calaveras Colusa Contra Costa Del Norte El
// Dorado Fresno Glenn Humboldt Imperial Inyo Kern Kings Lake Lassen Los Angeles
// Madera Marin Mariposa Mendocino Merced Modoc Mono Monterey Napa Nevada Orange
// Placer Plumas Riverside Sacramento San Benito San Bernardino San Diego San
// Francisco San Joaquin San Luis Obispo San Mateo Santa Barbara Santa Clara
// Santa Cruz Shasta Sierra Siskiyou Solano Sonoma Stanislaus Sutter Tehama
// Trinity Tulare Tuolumne Ventura Yolo Yuba "

// Tests negative input.
TEST(AllCountiesString, String) {
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(
             "Alameda Alpine Amador Butte Calaveras Colusa Contra Costa Del "
             "Norte El Dorado Fresno Glenn Humboldt Imperial Inyo Kern Kings "
             "Lake Lassen Los Angeles Madera Marin Mariposa Mendocino Merced "
             "Modoc Mono Monterey Napa Nevada Orange Placer Plumas Riverside "
             "Sacramento San Benito San Bernardino San Diego San Francisco San "
             "Joaquin San Luis Obispo San Mateo Santa Barbara Santa Clara "
             "Santa Cruz Shasta Sierra Siskiyou Solano Sonoma Stanislaus "
             "Sutter Tehama Trinity Tulare Tuolumne Ventura Yolo Yuba ",
             AllCountiesString(ca_counties)));
}

// Tests int CountyIndex(const std::array<std::array<std::string, 58>, 2>&
// ca_counties, const std::string match_county);
TEST(CountyIndex, Found) {
  EXPECT_DURATION_LE(5, EXPECT_EQ(0, CountyIndex(ca_counties, "Alameda")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(1, CountyIndex(ca_counties, "Alpine")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(2, CountyIndex(ca_counties, "Amador")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(3, CountyIndex(ca_counties, "Butte")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(4, CountyIndex(ca_counties, "Calaveras")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(5, CountyIndex(ca_counties, "Colusa")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(6, CountyIndex(ca_counties, "Contra Costa")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(7, CountyIndex(ca_counties, "Del Norte")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(8, CountyIndex(ca_counties, "El Dorado")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(9, CountyIndex(ca_counties, "Fresno")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(10, CountyIndex(ca_counties, "Glenn")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(11, CountyIndex(ca_counties, "Humboldt")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(12, CountyIndex(ca_counties, "Imperial")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(13, CountyIndex(ca_counties, "Inyo")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(14, CountyIndex(ca_counties, "Kern")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(15, CountyIndex(ca_counties, "Kings")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(16, CountyIndex(ca_counties, "Lake")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(17, CountyIndex(ca_counties, "Lassen")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(18, CountyIndex(ca_counties, "Los Angeles")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(19, CountyIndex(ca_counties, "Madera")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(20, CountyIndex(ca_counties, "Marin")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(21, CountyIndex(ca_counties, "Mariposa")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(22, CountyIndex(ca_counties, "Mendocino")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(23, CountyIndex(ca_counties, "Merced")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(24, CountyIndex(ca_counties, "Modoc")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(25, CountyIndex(ca_counties, "Mono")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(26, CountyIndex(ca_counties, "Monterey")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(27, CountyIndex(ca_counties, "Napa")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(28, CountyIndex(ca_counties, "Nevada")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(29, CountyIndex(ca_counties, "Orange")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(30, CountyIndex(ca_counties, "Placer")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(31, CountyIndex(ca_counties, "Plumas")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(32, CountyIndex(ca_counties, "Riverside")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(33, CountyIndex(ca_counties, "Sacramento")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(34, CountyIndex(ca_counties, "San Benito")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(35, CountyIndex(ca_counties, "San Bernardino")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(36, CountyIndex(ca_counties, "San Diego")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(37, CountyIndex(ca_counties, "San Francisco")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(38, CountyIndex(ca_counties, "San Joaquin")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(39, CountyIndex(ca_counties, "San Luis Obispo")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(40, CountyIndex(ca_counties, "San Mateo")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(41, CountyIndex(ca_counties, "Santa Barbara")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(42, CountyIndex(ca_counties, "Santa Clara")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(43, CountyIndex(ca_counties, "Santa Cruz")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(44, CountyIndex(ca_counties, "Shasta")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(45, CountyIndex(ca_counties, "Sierra")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(46, CountyIndex(ca_counties, "Siskiyou")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(47, CountyIndex(ca_counties, "Solano")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(48, CountyIndex(ca_counties, "Sonoma")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(49, CountyIndex(ca_counties, "Stanislaus")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(50, CountyIndex(ca_counties, "Sutter")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(51, CountyIndex(ca_counties, "Tehama")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(52, CountyIndex(ca_counties, "Trinity")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(53, CountyIndex(ca_counties, "Tulare")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(54, CountyIndex(ca_counties, "Tuolumne")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(55, CountyIndex(ca_counties, "Ventura")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(56, CountyIndex(ca_counties, "Yolo")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(57, CountyIndex(ca_counties, "Yuba")));
}

TEST(CountyIndex, NotFound) {
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(-1, CountyIndex(ca_counties, "Tulare County")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(-1, CountyIndex(ca_counties, "Junk")));
}

}  // namespace
