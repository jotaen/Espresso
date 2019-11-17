.PHONY: test.out run-test

test.out:
	@clang++ \
		-std=c++11 \
		-o test.out \
		test/unit-tests.cpp

run-test:
	@# https://github.com/catchorg/Catch2/blob/master/docs/command-line.md#showing-results-for-successful-tests
	@make test.out && ./test.out --durations yes
