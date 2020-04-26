##
# apricot
#
# @file
# @version 0.0.1

# our testing targets
.PHONY: tests flake black mypy python build lib tags

lib:
	make -C build -j4

build:
	mkdir -p build
	cd build && cmake ..
	make -C build -j4

tags:
	find src include -type f -iname '*.cpp' -or -iname '*.hpp' -exec etags {} +

python: mypy isort black flake tests

tests:
	python -m pytest tests

flake:
	python -m flake8 apricot

black:
	python -m black -t py37 apricot tests

mypy:
	python -m mypy apricot

isort:
	python -m isort --atomic -rc -y apricot



# end
