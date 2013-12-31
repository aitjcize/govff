#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# pyovff - an OVFF translator implemented in python 
#
# Copyright (C) 2010 -  Wei-Ning Huang (AZ) <aitjcize@gmail.com>
# All Rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# 2010/03/23: Ver 0.1, first release

import sys
import sqlite3
import getopt

# Program Information
program_name = 'pyovff'
program_version = '0.1.3'

# datatbase path
database = '/usr/share/ovff/database/boshiamy.db'

def help():
    sys.stderr.write(
"usage: {0} [-e] [-i pInfile] [-o pOutfile]\n\
       {0} [-v] [-h]\n\n\
       -e      Encode mode, default mode is decode mode.\n\
       -i      Specify source filename, default is stdin\n\
       -o      Specify destination filename, default is stdout\n\
       -v      Show version info\n\
       -h      Show this help list\n\n\
Note: You can also pipe the data through pyovff, for example:\n\
pyovff -i pInfile -o pOutfile\n\
can be written as:\n\
pyovff < pInfile > pOutfile\n\n\
Please report bugs to Aitjcize <aitjcize@gmail.com>\n"
    .format(program_name))

def version():
    sys.stdout.write(
"PyOVFF嘸蝦米翻譯機 Ver {0}\n\
Copyright (C) 2009 Aitjcize (Wei-Ning Huang)\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\nThis is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n\
Written by Aitjcize (Wei-Ning Huang).\n"
    .format(program_version))

def preprocess(n):
    '''
    Preprocess list n, deal with '\n', '\t'.
    '''
    # I finally came up this way to solve the seperators problems once and for
    # all :)
    seperators = '\t\n'

    for i, oi in enumerate(n):
        # '' is the result of split(' '), we must recover it.
        if oi == '':
            n.pop(i)
            n.insert(i, ' ')

        L = []
        t = 0
        prev = ''
        # expend sepeartors to list L
        for j in oi:
            if j in seperators:
                if len(L) != 0:
                    L.pop()
                if oi[:t] != '':
                    L.append(oi[:t])
                # append adjacent seperators, because the first one is used as
                # seperator, the second one should remain untouched. '\n'
                # should always be appended.
                if (prev in seperators and j == prev) or j == '\n':
                    L.append(j)
                if oi[t + 1:] != '':
                    L.append(oi[t + 1:])
                oi = oi[t + 1:]
                t = -1
            t += 1
            prev = j

        # insert the expended element from L into n
        if len(L) != 0:
            n.pop(i)
            for j, oj in enumerate(L):
                n.insert(i + j , oj)
    return n

def ovff_decode(inFile = sys.stdin, outFile = sys.stdout):
    '''
    decode ovff data from inFile and output to outFile
    '''
    n = preprocess(inFile.read().split(' '))
    inFile.close()
    sqlHandle = sqlite3.connect(database)
    sqlHandle.text_factory = str
    c = sqlHandle.cursor()

    for i in n:
        if i in ' \n':
            outFile.write(i)
            continue

        # omit none ASCII word or len(word) > 5 to prevent query error
        if ord(i[0]) > 255 or len(i) > 5:
            outFile.write(i)
            continue

        word = i.upper()
        query_str = 'SELECT phrase FROM phrases WHERE '

        for j in range(5):
            if j >= len(word):
                query_str += 'm' + str(j) + ' IS NULL AND '
                continue
            if word[j] == '.':
                alpha = '56'
            elif word[j] == ',':
                alpha = '55'
            elif word[j] == '\'':
                alpha = '27'
            elif word[j] == '[':
                alpha = '45'
            elif word[j] == ']':
                alpha = '46'
            else:
                alpha = str(ord(word[j]) - ord('A') + 1)
            query_str += 'm' +str(j) +'=' + alpha + ' AND '

        query_str = query_str.strip(' AND ')
        query_str += ' ORDER BY -freq LIMIT 1;'
        result = c.execute(query_str).fetchone()

        if result == None:
            outFile.write(i)
        else:
            outFile.write(result[0])
    
    c.close()
    sqlHandle.close()

def ovff_encode(inFile = sys.stdin, outFile = sys.stdout):
    '''
    encode chinese characters from inFile and output to outFile
    '''
    n = preprocess(list(unicode(inFile.read(), 'utf8')))
    inFile.close()
    sqlHandle = sqlite3.connect(database)
    sqlHandle.text_factory = str
    c = sqlHandle.cursor()

    for i in n:

        # omit none chinese(including `\n') to prevent query error
        if ord(i) < 256:
            outFile.write(i)
            continue

        query_str = "SELECT m0,m1,m2,m3,m4 FROM phrases WHERE phrase='%s'" \
                    " ORDER BY -freq,category LIMIT 1;" % i.encode('utf8')
        result = c.execute(query_str).fetchall()
        encoded = ''

        for j in result[0]:
            if j != None:
                if j == 56:
                    encoded += '.'
                elif j == 55:
                    encoded += ','
                elif j == 27:
                    encoded += '\''
                elif j == 45:
                    encoded += '['
                elif j == 46:
                    encoded += ']'
                else:
                    encoded += chr(64 + j)

        encoded += ' '
        outFile.write(encoded)

    c.close()
    sqlHandle.close()

def main():
    '''
    main function
    '''
    inFile = sys.stdin
    outFile = sys.stdout
    do_encode = False

    try:
        optlist, args = getopt.getopt(sys.argv[1:], 'vhei:o:')
    except getopt.GetoptError as i:
        print 'error:', i.msg
        sys.exit(1)

    for i in optlist:
        if i[0] == '-e':
            do_encode = True
        elif i[0] == '-h':
            help()
            sys.exit(0)
        elif i[0] == '-v':
            version()
            sys.exit(0)
        elif i[0] == '-i':
            try:
                inFile = open(i[1], 'r')
            except IOError as err:
                print 'error: {0}: {1}'.format(i[1], err.args[1])
                sys.exit(1)

        elif i[0] == '-o':
            try:
                outFile = open(i[1], 'w')
            except IOError as err:
                print 'error: {0}: {1}'.format(i[1], err.args[1])
                sys.exit(1)
        else:
            # This should not happen
            sys.exit(1)

    if len(args) != 0:
        for i in args:
            print 'Unknown option `%s\'.' % i
        sys.exit(1)

    if do_encode:
        ovff_encode(inFile, outFile)
    else:
        ovff_decode(inFile, outFile)

__all__ = [ ovff_encode, ovff_decode ]

if __name__ == '__main__':
    main()
