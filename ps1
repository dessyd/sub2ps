%!PS-Adobe-1.0
%%Title:subsector.ps
/hexside 26 def
/sside hexside .2 mul def
/dx sside 18 sin mul def
/dy sside 18 cos mul def
/trheight hexside 3 sqrt 2 div mul def
/drawbottom %draws bottom half of one hex
 { hexside 2 div trheight neg 2 copy rlineto
   hexside 0 rlineto neg rlineto } bind def
/flat {hexside 0 rmoveto} bind def
/inch {72 mul} bind def
/gridUL {3.5 inch 9.95 inch} bind def
/dohexrow {currentpoint hexside 2 div trheight rlineto
4 {flat drawbottom} repeat stroke moveto
4 {drawbottom flat} repeat
hexside 2 div trheight neg rlineto stroke } bind def
/cprint { dup stringwidth pop -2 div 0 rmoveto show } bind def
/drawstar	%draws little star representing naval base
      {
	dx dy rlineto
	dx dy neg rlineto
	sside 36 cos neg mul sside 36 sin mul rlineto
	sside 0 rlineto closepath fill } bind def
/drawtri	%draws triangle representing scouts; fill?(bool) => -
      {
	dx dy rlineto
	dx dy neg rlineto
	closepath {fill} {stroke} ifelse } bind def
/drawarmy	%draws army and garrison symbols; army?(bool) => -
      {
	3 0 rlineto
	0 -3 rlineto
	-3 0 rlineto closepath
	{fill} {stroke} ifelse } bind def
/drawvargr	%draws vargr corsair base symbol
      {
	3 -3 rlineto
	3 3 rlineto
	-3 -6 rlineto
	closepath fill } bind def
/drawzho	%draws zhodani base symbol
      {
	5 0 rlineto
	-5 -5 rlineto
	5 0 rlineto stroke } bind def
/bases	%determines which bases to draw; (letter) => -
      {
	dup (A) eq
	{pop currentpoint -12 7 rmoveto drawstar moveto -12 -3 rmoveto
	 true drawtri } 
	{ dup (B) eq 
	{pop currentpoint -12 7 rmoveto drawstar moveto -12 -3 rmoveto
	 false drawtri } 
	  { dup (G) eq
	{pop -12 12 rmoveto false drawarmy } 
	   { dup (M) eq {pop -12 12 rmoveto true drawarmy } 
	    { dup (N) eq {pop -12 7 rmoveto drawstar } 
	     { dup (S) eq {pop -12 7 rmoveto true drawtri } 
              { dup (V) eq {pop -12 12 rmoveto drawvargr }	
	      { dup (W) eq {pop -12 7 rmoveto false drawtri } 
	        { dup (Z) eq {pop -12 12 rmoveto drawzho } 
	 {pop} ifelse } ifelse } ifelse } ifelse } ifelse }
		ifelse } ifelse } ifelse } ifelse  } bind def	

/outbord	%draw outside border
  { gridUL moveto
    3 setlinewidth
    12.5 hexside mul 0 rlineto
    0 -21 trheight mul rlineto
    -12.5 hexside mul 0 rlineto
    closepath } bind def
/outc % outer corners
    {gridUL moveto
    5 setlinewidth
    -10 10 rmoveto
    1.2 inch 0 rmoveto
    -1.2 inch 0 rlineto
    0 -2.2 inch rlineto stroke
    gridUL 21 trheight mul sub moveto
    -10 -10 rmoveto
    0 2.2 inch rmoveto
    0 -2.2 inch rlineto
    1.2 inch 0 rlineto stroke
    gridUL 21 trheight mul sub exch 12.5 hexside mul add exch moveto
    10 -10 rmoveto
    -1.2 inch 0 rmoveto
    1.2 inch 0 rlineto
    0 2.2 inch rlineto stroke
    gridUL exch 12.5 hexside mul add exch moveto
    10 10 rmoveto
    0 -2.2 inch rmoveto
    0 2.2 inch rlineto
    -1.2 inch 0 rlineto
    stroke } bind def

/ccoord  % col row => x y
    { 
    -2 mul trheight mul
    exch dup 2 mod 1 eq { exch trheight add} { exch } ifelse
    exch 1.5 mul hexside mul hexside 2 div sub
    gridUL pop add exch gridUL exch pop add } bind def
/trzone  % Travel Zone; (name) (uwp) x y => same
{newpath 2 index 12 1 getinterval dup dup (G) eq exch ( ) eq or {pop}
{ (A) eq {[5]} {[]} ifelse 0 setdash 
2 copy exch trheight 2 sub add exch moveto
  2 copy trheight 2 sub 0 360 arc stroke}
  ifelse [] 0 setdash} bind def  
/sdraw% draws one hexside; (dirletter) => same
      {dup (y) eq { hexside -2 div trheight rlineto} 
{ dup (u) eq {hexside 2 div trheight rlineto} 
 { dup (j) eq {hexside 0 rlineto} 
  { dup (n) eq {hexside 2 div trheight neg rlineto} 
   { dup (b) eq {hexside -2 div trheight neg rlineto} 
    { dup (g) eq {hexside neg 0 rlineto} {quit} ifelse} ifelse } ifelse
} ifelse } ifelse } ifelse } bind def

/world  %(name) hexnum (uwp) => (name) (uwp)
    {
	1 setlinewidth
     exch dup dup 100 idiv 8 mod dup 0 eq {8 add} if
     exch 10 mod dup 0 eq {10 add} if ccoord
	2 copy moveto
	3 -1 roll dup 10 string cvs
	currentfont /Helvetica findfont 5 scalefont setfont
	(00) stringwidth pop neg 14 rmoveto 
	3 -1 roll 1000 lt {(0) show} if exch show setfont 
    2 copy moveto
    2 copy 12 0 360 arc closepath
    1 setgray fill 0 setgray
    2 index 1 1 getinterval (0) eq { 2 copy moveto 3 3 rmoveto -6 -6 rlineto
2 copy moveto -3 3 rmoveto 6 -6 rlineto stroke }
  { 2 copy exch 3 add exch moveto 2 copy 3 0 359 arc closepath
    2 index 3 1 getinterval (0) eq {stroke} {fill} ifelse } ifelse
    2 copy moveto 0 5 rmoveto
    2 index 0 1 getinterval cprint
    2 copy moveto 3 index dup stringwidth pop 2 div neg -10 rmoveto show
    2 copy moveto trzone
    2 copy moveto 2 index 10 1 getinterval bases
    moveto dup 15 1 getinterval
    (0) eq not {10 10 rmoveto currentpoint 2 0 360 arc fill} if } bind def

/xboat% [dests] => -
{ outbord clip newpath
          (x) exch aload pop ccoord moveto .5 setgray 4 setlinewidth
  { dup (x) eq {exit} if ccoord lineto } loop
stroke 0 setgray initclip } bind def

/borderdraw     % x y (string) => -
  { /x exch def
     moveto 0 setgray 3 setlinewidth
     0 1 x length 1 sub
     {x 1 index 1 getinterval sdraw } for
     stroke } bind def

/swrite		% writes name of adjoining subsector
   {	currentfont exch
	/Times-Roman findfont 14 scalefont setfont
	cprint setfont } bind def

/bords		% (string) 0-3 => -
     {	gsave
	gridUL moveto
	dup 2 mod 1 eq
		{ -7 -10.5 trheight mul rmoveto }
		{ 6.25 hexside mul 6 rmoveto } ifelse
	dup 2 eq { -21 trheight mul 22 sub 0 exch rmoveto } if
	dup 3 eq { 12.5 hexside mul 15 add 0 rmoveto } if
	dup 2 mod 1 eq { dup 2 ge {-90} {90} ifelse rotate } if
	pop swrite grestore } bind def

/dataprint			% prints homeworld data in left hand box
				% (Name) x y (UWP) (Notes)
      {
	/pos pos 11 sub def
	gridUL pop 75 sub dup pos moveto exch show
	90 sub pos moveto /st exch def
	0 1 st length 2 sub
	{dup dup 4.75 mul gridUL pop 165 sub add exch st exch
	 1 getinterval exch pos moveto
		dup (G) eq {-1 0 rmoveto} if show pop} for
	st dup length 1 sub 1 getinterval show
	dup 10 string cvs
	65 pos moveto exch 1000 lt {(0) show} if show
	1 4 div inch pos moveto show } bind def

/noter			% puts notes in data list; (message) tab#
      {
	12 mul 1 4 div inch add
	/pos pos 8 sub def
	pos moveto show		} bind def

/subtitle			%(string) num: 0=title, 1=subtitle
      {
	currentfont exch 0 eq
	{ /Times-Bold findfont 24 scalefont setfont 4.25 inch 10.5 inch moveto}
	{ /Times-Italic findfont 16 scalefont setfont 4.25 inch 10.23 inch moveto} ifelse
	exch cprint setfont } bind def

/doworld	% (Name) loc (UWP) (Notes) => (Name) (UWP)
      {
	4 copy pop world pop pop dataprint } bind def

    %%EndProlog
