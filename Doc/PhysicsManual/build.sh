#!/bin/sh
xelatex BornAgainManual
bibtex  BornAgainManual
makeindex -s index.ist BornAgainManual
makeindex -s nomencl.ist BornAgainManual.nlo -o BornAgainManual.nls
xelatex BornAgainManual
xelatex BornAgainManual
