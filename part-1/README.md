# Calculating the Area of a Rectangle

A [rectangle](https://en.wikipedia.org/wiki/Rectangle) is a four sided polygon with four right angles. A rectangle is defined by its length and width.

Given the length _l_ and width _w_ of a rectangle, one can calculate the area of a rectangle by finding the product of length and width, _l_ × _w_.

The purpose of this exercise is to gain practice using the following elements:
* Writing our own command line parser (please refer to previous labs for examples)
* Using instructor provided [unit tests](https://en.wikipedia.org/wiki/Unit_testing).
* Defining functions

This project is defined in 4 files:
* `rectangle_area.cc`
* `rectangle_area_functions.cc`
* `rectangle_area_functions.h` - Do not edit or change this file.
* `rectangle_area_unittest.cc` - Do not edit or change this file.

In `rectangle_area.cc`, our main function for our program is defined. In this file, the command line arguments are processed and converted to integers. From there, they are passed to the function `int RectangleArea(int length, int width)`.

The function `int RectangleArea(int length, int width)` is defined in the file `rectangle_area_functions.cc`. The compiler separately compiles each file and then combines the output from each compilation step into an executable binary file (a .exe file).

This project demonstrates [modular programming](https://en.wikipedia.org/wiki/Modular_programming) where different elements of our program are defined in different files. Imagine trying to write a large program like a web browser, word processor, or operating system in just a single file. The amount of code in the file would make it difficult to navigate and chnange. For this and many other reasons, programmers like to break their programs down into multiple files. In our project, we have one file which has our main program `rectangle_area.cc` and another file which contains the functions used in our main program `rectangle_area_functions.cc`.

The file `rectangle_area_functions.h` is called a [header file](https://google.github.io/styleguide/cppguide.html#Header_Files). Notice that it is almost the same name as `rectangle_area_functions.cc` except that the file extension `.cc` has been changed to `.h`. This tells the programmer that it is the header file for the C++ source file named `rectangle_area_functions.cc`. The header file is used to help the programmer and compiler know what is available for use in a given `.cc` file.

Another benefit of modular programming is that we can break our program down into independent pieces which can be tested independently. As our programs increase in complexity, we will be writing more units of code that we need to make sure function correctly. One way to do this is to follow the practice of [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development). 

Test-driven development is where the tests are written first and then we develop the software to pass the tests. The motivation is that if the person who wrote the specification (your instructor) understands what they want, then tests can be written to document how the code is going to be used. Then the developer (you, the student) can develop your software and know that it is correct(-ish) if it passes the tests.

We can never really know if the code is correct because the tests could be flawed or wrong. Regardless, test-driven development is an effective way to communicate how we would like our programs to behave.

In this exercise, [unit tests](https://en.wikipedia.org/wiki/Unit_testing) have been included which test the function `int RectangleArea(int length, int width)`. To run the unit tests, use the command `make unittest`.

If any of the tests fail, use the output to go back and revise your code and re-run the unit tests. Once you have all your tests passing, then you likely have all the parts working correctly.

Remember, verifying a unit (a part) does not mean that the entire program (the system that uses the parts) is working correctly. That part is still up to the developer to verify through rigorous testing. As a starting point, you can use the instructor's partial tests with `make test`.

## Functions

### `RectangleArea`
Calculate the area of a triangle defined by length and width. 

Although rectangles with negative length and width exist, this program is meant to be used to calculate the positive area of rectangles one could encounter in the physical world. Because of this requirement, length and width must be positive integers. Values less than 1 mean that the rectangle has 0 area.

```c++
int RectangleArea(int length, int width) {
  int area{-1};
  // TODO: Implement the function according to the specifications.
  return area;
}
```

## Requirements

Write a program that takes two integers as a command line argument which represent the length and width of a non-degenerate, positive area rectangle. Calculate the area using the function `int RectangleArea(int length, int width)` which is defined in `rectangle_area_functions.cc`. Print a message to the terminal showing the length, width and the area of the rectangle. See the Example Output Section for more details.

A rectangle is defined by a positive length and a positive width. Rectangles defined by lengths or widths that are less than or equal to 0 have 0 area.

You shall use [cout](https://en.cppreference.com/w/cpp/io/cout) to print messages to the terminal.

_Do not use_ [cin](https://en.cppreference.com/w/cpp/io/cin) to read in values from the keyboard. This program is not interactive and an interactive program will be marked with a zero score.

The program reads in two value from the command line (`argv`), stores them in a vector named `args`. Use the examples provided to process command line arguments.

Use `stoi()` only. Do not use `atoi()`.

Make certain that the error messgaes your program generates matches the examples given below in Example Output section.

The starting code defines a series of `TODO` comments which you can use to formulate your plan and develop your program.

Write your program progressively. Compile your program often and check that you're making progress. Make sure your program behaves the way you expect. Start with the functions and use the unit tests to verify they work correctly. Then move on to writing the main function once all you functions pass their unit tests.

The output of your program must match the output given in the section Example Output below.

To compile your program, you use the `make` command. A Makefile is provided for this exercise.

The Makefile has the following targets:

* all: builds the project
* clean: removes object and dependency files
* spotless: removes everything the clean target removes and all binaries
* format: outputs a [`diff`](https://en.wikipedia.org/wiki/Diff) showing where your formatting differes from the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
* lint: output of the [linter](https://en.wikipedia.org/wiki/Lint_(software)) to give you tips on how to improve your code
* header: check to make sure your files have the appropriate header
* test: run tests to help you verify your program is meeting the assignment's requirements. This does not grade your assignment.
* unittest: run unit tests to verify parts of your program performs according to the instructor supplied unit tests.

## Don't Forget

Please remember that:

- You need to put a header in every file.
- You need to follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- Remove the `TODO` comments.

## Testing Your Code

Computers only ever do exactly what they are told, exactly the way they are told it, and never anything else. Testing is an important process to writing a program. You need to test for the program to behave correctly and test that the program behaves incorrectly in a predictable way.

As programmers we have to remember that there are a lot of ways that we can write the wrong program and only one to a few ways to write the correct program. We have to be aware of [cognitive biases](https://en.wikipedia.org/wiki/List_of_cognitive_biases) that we may exercise that lead us to believe we have correctly completed our program. That belief may be incorrect and our software may have errors. [Errors in software](https://www.wired.com/2005/11/historys-worst-software-bugs/) may lead to loss of [life](https://www.nytimes.com/2019/03/14/business/boeing-737-software-update.html), [property](https://en.wikipedia.org/wiki/Mariner_1), [reputation](https://en.wikipedia.org/wiki/Pentium_FDIV_bug), or [all of the above](https://en.wikipedia.org/wiki/2009%E2%80%9311_Toyota_vehicle_recalls).

### Test strategy

Start simple, and work your way up. Good tests are specific, cover a broad range of fundamentally different possibilities, can identify issues quickly, easily, and directly, without need for much set up, and can almost be diagnosed by inspection if the code fails to execute the test correctly.

## Example Output

Please ensure your program's output is identical to the example below.

```
$ make unittest
set -e; clang++ -MM -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 rectangle_area_functions.cc \
| sed 's/\(rectangle_area_functions\)\.o[ :]*/\1.o rectangle_area_functions.d : /g' > rectangle_area_functions.d; \
[ -s rectangle_area_functions.d ] || rm -f rectangle_area_functions.d
set -e; clang++ -MM -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 rectangle_area.cc \
| sed 's/\(rectangle_area\)\.o[ :]*/\1.o rectangle_area.d : /g' > rectangle_area.d; \
[ -s rectangle_area.d ] || rm -f rectangle_area.d
rm: cannot remove 'unittest': No such file or directory
rm: cannot remove 'test_detail.json': No such file or directory
make: [Makefile:142: cleanunittest] Error 1 (ignored)
clang++ -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 -c rectangle_area_functions.cc
Running main() from /build/googletest-j5yxiC/googletest-1.10.0/googletest/src/gtest_main.cc
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from RectangleAreaTest
[ RUN      ] RectangleAreaTest.Negative
[       OK ] RectangleAreaTest.Negative (0 ms)
[ RUN      ] RectangleAreaTest.Positive
[       OK ] RectangleAreaTest.Positive (0 ms)
[----------] 2 tests from RectangleAreaTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
$ make
clang++ -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 -c rectangle_area.cc
clang++ -g -O3 -Wall -pipe -std=c++17 -o rectangle_area rectangle_area.o rectangle_area_functions.o 
$ ./rectangle_area 
Please provide two arguments, a rectangle's length and width.
For example:
./rectangle_area 23 17
$ ./rectangle_area 42
Please provide two arguments, a rectangle's length and width.
For example:
./rectangle_area 23 17
$ ./rectangle_area 42 10
42 x 10 = 420
$ ./rectangle_area 23 17
23 x 17 = 391
```

