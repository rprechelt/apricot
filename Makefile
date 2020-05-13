##
# apricot
#
# @file
# @version 0.0.1

# our testing targets
.PHONY: tests flake black mypy python build lib tags format clean

# setup the cmake library
lib: format
	make -C build -j4

# setup and compile the C++ library
build: format
	mkdir -p build
	cd build && cmake ..
	make -C build -j4

# run clangformat
format:
	find src include -type f -iname '*.cpp' -or -iname '*.hpp' -exec clang-format -i {} +

# run the Python chain
python: isort black flake tests

# run the Python tests
tests:
	python -m pytest tests

# run flake
flake:
	python -m flake8 apricot

# run black
black:
	python -m black -t py37 apricot tests

# run isort
isort:
	python -m isort --atomic -rc -y apricot

# generate a TAGS library
tags:
	find src include -type f -iname '*.cpp' -or -iname '*.hpp' -exec etags {} +

# clean everything up
clean:
	$(RM) -r libapricot.so*
	$(RM) -r build/*
	$(RM) -r _apricot.cpython*
	find . -type d -iname __pycache__ -exec rm -rf {} \+
	$(RM) -r apricot.egg-info
	$(RM) -r .auctex-auto
	$(RM) -r .pytest_cache

# end
