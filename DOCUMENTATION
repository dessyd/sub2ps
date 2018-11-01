
DOCUMENTATION FOR SUBSECTOR MAPPER PROGRAM
by: Travis McCord (mccord@equinox.unr.edu, for now)

**NOTE**	This program is SHAREWARE.  If you like it, please
		send some amount--$5, or whatever you think it's worth
		--to the address below.
		Help out a former student.  Please.		

		Travis McCord
		11045 Wagon Ho Trail
		Reno, NV 89506
		Re: Map Program


The Program

"sub2ps" is a program that takes a specially prepared file containing
data about a MegaTraveller subsector and creates a postscript map of
that subsector.  The map can contain interstellar borders and xboat
routes as well as worlds and bases.

A few sector data files have been included in this package as
demonstration files: A "blank" subsector, which creates a blank map
for the GM's own subsector, and a data file for a sector I made up,
Unknown Subsector, which has examples of most of the major features
of the program.

The Program may be compiled by any C compiler; it's recommended you
use the Unix command:

	cc -O sub2ps.c -o sub2ps

to keep things simple and efficient.  This program is ANSI standard C,
and should work on most systems.

The Data File

Two types of lines can be placed in the data file: world lines and
feature lines.  Both types are described in detail below.

World Lines:

These detail worlds present in the subsector.  (Note: the program uses
the first world it encounters to determine which subsector is being
drawn; detailing a world outside that subsector results in an error
and the program aborts.)  These lines are of this format:

	World Name,0123,A777777-F X G321Im,Notes

where: 0123 is the hex number for the world.  This can be relative to
either the entire sector, or just the subsector (but making them
relative to the entire sector makes placing the Xboat routes
easier--see below.)

A777777-F is the Uwp For the world, in standard format.  The
postscript produced uses the UWP to determine how to represent the
world on the map.

X is a one-letter code showing how many bases are in the system.  This
is standard GDW, as in the Spinward Marches Data in the Imperial
Encyclopedia. (i.e.: N=Imperial Naval, S=Imperial Scout, A=both Naval
and Scout, etc.)  Note that the spaces before and after this letter
are significant, and that an X here represents no bases present.

G321Im is the Travel Zone code; The numbers indicate the Population
Multiple, Number of Planetoid Belts, and Number of Gas Giants,
respectively; and the last 2 characters are the allegiance of the
system.  Again, this is standard GDW.

Notes can be anything; I use this field for the Trade Codes.  The text
here will be printed after the Uwp In the World Data box on the map.


Feature Lines

All feature lines begin with the '!' (bang) character; the fields of
the line are separated by commas. Leading spaces are eliminated by
the program; trailing spaces are not.  These lines
draw special features on the map, as explained below.  (Note that all
these keywords can be abbreviated to any length >=1 character after
the bang.)

!title,<text>
	Causes <text> to be printed in large letters at the top of the
map sheet.  Usually used for the subsector's name.

!subtitle, <text>
	Causes <text> to be printed in Bold Italics just below the
title (above).  Can be used for the subsector Designation (as in,
Some Sector-C)

!adjacent,x,<text>
	used for the names of the subsectors adjacent to the one
drawn, this causes <text>to be printed beside the grid at the position
specified by x.  x can be any of:
	t -for top
	b -for bottom
	l -for left
or	r -for right.
Text printed on either the left or right is rotated 90 degrees 
to fit the space.

!border,<start>,<path>
	draws a thick line between hexes representing the dividing
lines between interstellar states.  <start>is of the form:
<side><number> where <side> can be either t,b,l, or r (as in
!adjacent, above) and <number> indicates which point on that side the
border starts from; counting from either the top going down, or the
left side going right, the first point where a hex's corner contacts
the grid's outline is point 0, the next is point 1, etc., etc.  <path>
directs where the border will go, according to the following key:

		up & left - y		u - up & right

		left - g		 j - right

		down & left- b		n - down and right

Note that the program never checks whether the line actually follows a
hexside on the map.  All letters in this statement must be lowercase.

!xboat,<hex#>,<hex#>,...
	this statement draws the Xboat routes as thick gray lines
on the hex grid.  The <hex#>'s are the actual hex-numbers of
the xboat stops; they may even be outside of the subsector being
drawn.  The program draws straight lines from each stop to the next,
and only shows the part of the route that should appear in the map
(which means routes leading outside of the subsector go to the edge of
the map and stop there).  To direct the routes outside the SECTOR,
assume the first row above or column to the left of the map is
numbered 0, the next -1, etc.  In general, just extrapolate the
row and column numbering out from the map coordinates.

!! <comment>
	allows comments to be placed in the file.  The program ignores
everything from the !! to the end of the line.


The world and feature lines of data file may appear in any order,
except that any !xboat lines must be preceded by at least one world
line.  The first letter following the bang in feature lines must be
lowercase.


The Map

The resulting subsector map includes:
	--a title and subtitle, at the top
	--the subsector map grid, including the worlds and features
from the data file
	--a legend, in the bottom right corner, explaining the symbols
used
	--and a World Data box at left containing the UWP's and data
on the worlds shown, in either hex-number or alphabetical order.  (See
Using the Program, below)


Using the Program

The data file should have the name "secname.sub", (although it can be
just "secname").  The program is invoked by:

	sub2ps [-a] secname

which will produce the file "secname.ps" in the directory.  This file
is standard Adobe Postscript, with no particular mechanisms for
particular printers, so it should work on any PostScript printer.  (It
was originally developed for the NeXT printer, should there be any
problems.)  The -a option affects how the world data is displayed in
the box on the left--if this option is present, the worlds are listed
in alphabetical order.  The default is by hex-number.

Minor bug: specifying the complete name -- example.sub -- will result
in the output going to example.sub.ps --i.e., if the .sub is left on
it isn't removed.

(Please note that MegaTraveller is a trademark of Game Designers'
 Workshop.  There are probably several other things in this file
 that should have (tm), (R) or (C) after them; their exclusion
 in these files should not be considered a challenge to such status.
 My apologies to anyone whose toes I've stepped on.  :)

