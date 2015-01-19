#!/usr/bin/python

# Copyright (c) 2011 Ernesto Mendez (der-design.com)
# Dual licensed under the MIT and GPL licenses:
# http://www.opensource.org/licenses/mit-license.php
# http://www.gnu.org/licenses/gpl.html

# Version 1.0.0
# - Initial Release

from __future__ import generators
import sys
from optparse import OptionParser
import os

def main():
	# Process arguments

	if len(args) > 1:
		parser.error('Too many arguments')
		sys.exit()

	elif len(args) == 0:
		parser.error('Missing filename')
		sys.exit()

	if not os.path.exists(options.directory):
		parser.error("%s: No such directory" % options.directory)
		sys.exit()

	filename = args[0]

	# Create generator

	filetree = dirwalk(os.path.abspath(options.directory))

	# Walk directory tree, create files

	if options.remove == True:

		removed = ['Removing the following files: \n']
		cmd = "rm"

		for file in filetree:
			if (os.path.basename(file) == filename):
				removed.append(file)
				cmd += " %s" % fixpath(file)

		if cmd != "rm":
			for f in removed: print f
			os.system(cmd)
		else:
			print "No files named '%s' found" % filename
			sys.exit()

	# Walk directory tree, delete files

	else:

		created = ["Creating the following files:\n"]
		cmd = "touch"

		for file in filetree:
			if (os.path.isdir(file)):
				created.append("%s%s" % (file, filename))
				cmd += " " + fixpath("%s%s" % (file, filename))

		if cmd != "touch":
			for f in created: print f
			os.system(cmd)
		else:
			print "No empty directories found"
			sys.exit()


def dirwalk(dir, giveDirs=1):
	# http://code.activestate.com/recipes/105873-walk-a-directory-tree-using-a-generator/
    for f in os.listdir(dir):
        fullpath = os.path.join(dir, f)
        if os.path.isdir(fullpath) and not os.path.islink(fullpath):
            if not len(os.listdir(fullpath)):
                yield fullpath + os.sep
            else:
                for x in dirwalk(fullpath):  # recurse into subdir
                    if os.path.isdir(x):
                        if giveDirs:
                            yield x
                    else:
                        yield x
        else:
            yield fullpath


def wrap(text, width):
    return reduce(lambda line, word, width=width: '%s%s%s' % (line, ' \n'[(len(line)-line.rfind('\n')-1 + len(word.split('\n', 1)[0] ) >= width)], word), text.split(' ') )


def fixpath(p):
	return shellquote(os.path.normpath(p))


def shellquote(s):
	return "'" + s.replace("'", "'\\''") + "'"


def init_options():
	global parser, options, args
	parser = OptionParser(usage="usage: %prog [options] filename", description="Add or Remove placeholder files for SCM (Source Control Management) tools that do not support empty directories.")
	parser.add_option("-p", "--path", dest="directory", help="search within PATH", metavar="PATH")
	parser.add_option("-r", "--remove", dest="remove", action="store_true", help="remove FILE from PATH, if it's the only file on PATH")

	(options, args) = parser.parse_args()

if __name__ == '__main__':
	print
	init_options()
	main()
	print
