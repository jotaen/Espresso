.PHONY: test.out run-test

test.out:
	@clang++ \
		-std=c++11 \
		-o test.out \
		test.cpp

run-test:
	@make test.out && ./test.out
