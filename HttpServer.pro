TEMPLATE = subdirs

SUBDIRS += src test mytest

test.depends = src
