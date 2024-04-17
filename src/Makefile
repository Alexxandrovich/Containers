FLAGS=-Wall -Wextra -Werror -std=c++17 -g
LFLAGS=-lm
GFLAGS=-lgtest

TARGET=google_test_vector google_test_stack google_test_set
TARGET+=google_test_list_queue

test: $(TARGET)

google_test_vector:
	g++ $(FLAGS) -c tests/s21_googletest_vector.cc
	g++ $(FLAGS) s21_googletest_vector.o $(LFLAGS) $(GFLAGS) -o test_vector
	./test_vector

google_test_stack:
	g++ $(FLAGS) -c tests/s21_googletest_stack.cc
	g++ $(FLAGS) s21_googletest_stack.o $(LFLAGS) $(GFLAGS) -o test_stack
	./test_stack

google_test_set:
	g++ $(FLAGS) -c tests/s21_googletest_set.cc
	g++ $(FLAGS) s21_googletest_set.o $(LFLAGS) $(GFLAGS) -o test_set
	./test_set

google_test_list_queue:
	g++ $(FLAGS) -c tests/s21_googletest_list_queue.cc
	g++ $(FLAGS) s21_googletest_list_queue.o $(LFLAGS) $(GFLAGS) -o test_list_queue
	./test_list_queue

gcov_report_vector: clean add_coverage google_test_vector
	# lcov --ignore-errors mismatch --no-external -t "test" -o test.info -c -d .
	lcov --no-external -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

gcov_report_stack: clean add_coverage google_test_stack
	# lcov --ignore-errors mismatch --no-external -t "test" -o test.info -c -d .
	lcov --no-external -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

gcov_report_set: clean add_coverage google_test_set
	# lcov --ignore-errors mismatch --no-external -t "test" -o test.info -c -d .
	lcov --no-external -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

gcov_report_list_queue: clean add_coverage google_test_list_queue
	# lcov --ignore-errors mismatch --no-external -t "test" -o test.info -c -d .
	lcov --no-external -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

add_coverage:
	$(eval FLAGS += --coverage)

clean:
	rm -rf report
	rm -f *.o a.out *.gcno *.gcda test.info test_*

.PHONY: test google_test gcov_report add_coverage

