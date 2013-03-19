# generate aditional code for GISASFW Python API

default: build

build:
	python codegenerator.py make

install:
	python codegenerator.py install



.PHONY: clean

clean:
	rm -r -f output
	rm -f *~
	rm -f named_tuple.py
	rm -f *.pyc
	rm -f exposed_decl.pypp.txt
