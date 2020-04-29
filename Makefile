##
# apricot
#
# @file
# @version 0.0.1

# our testing targets
.PHONY: tests flake black mypy python build lib tags format

# setup the cmake library
lib:
	make -C build -j4

# setup and compile the C++ library
build:
	mkdir -p build
	cd build && cmake ..
	make -C build -j4

# run clangformat
format:
	find src include -type f -iname '*.cpp' -or -iname '*.hpp' -exec clang-format -i {} +

# run the Python chain
python: mypy isort black flake tests

# run the Python tests
tests:
	python -m pytest tests

# run flake
flake:
	python -m flake8 apricot

# run black
black:
	python -m black -t py37 apricot tests

# run mypy
mypy:
	python -m mypy apricot

# run isort
isort:
	python -m isort --atomic -rc -y apricot

# generate a TAGS library
tags:
	find src include -type f -iname '*.cpp' -or -iname '*.hpp' -exec etags {} +

# end
