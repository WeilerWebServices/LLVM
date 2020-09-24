#!/usr/bin/python
##===- Count Lines Of Code in HLVM ---------------------------*- Python -*-===##
# 
#                         High Level Virtual Machine
#
# This file was developed by Reid Spencer and is distributed under the 
# Lesser General Public License.
# 
##===----------------------------------------------------------------------===##
#
# This script finds all the source code files in the source code directories
# (excluding certain things), runs "wc -l" on them to get the number of lines in
# each file and then sums up and prints the total.
#
# The script takes no arguments but does expect to be run from somewhere in
# the top llvm source directory.
#
# Note that the implementation is based on llvmdo. See that script for more
# details.
##===----------------------------------------------------------------------===##

import os
from os.path import join, getsize
import glob;
import datetime;

suffixes = ['.h','.cpp','.cxx','.py','.rng','.in','.xsl','.sh','.pm','.hlx',
            '.exp','.ll','.sh']

docsuffixes = ['.html','.css','.pod','.header','.footer','.intro']

filenames = ['SConscript', 'SConstruct','Makefiles' ]

notdirs = ['.svn','Release','Debug','Optimized','Profile','default']

total = 0
doctotal = 0
for root, dirs, files in os.walk('.'):
  for name in files:
    (basename,ext) = os.path.splitext(name)
    if ext in suffixes or name in filenames:
      lines = 0
      for line in open(join(root,name),'r'):
        lines += 1
      print join(root,name), ":", lines
      total += lines
    if ext in docsuffixes:
      lines = 0
      for line in open(join(root,name),'r'):
        lines += 1
      doctotal += lines
  for d in notdirs:
    if d in dirs:
      dirs.remove(d)

print "Lines Of Code in HLVM:",total
print "Lines Of Doc  in HLVM:",doctotal
now = datetime.date.today()
then = datetime.date(2006,4,24)
days = now.toordinal() - then.toordinal()
print "Code Productivity:",total / ((days * 5) / 7),"loc/day"
print "Total Productivity:", (total+doctotal) / ((days * 5) / 7), "lines/day"
