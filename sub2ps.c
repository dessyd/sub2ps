#ifdef SYSV
#include <fcntl.h>
#else
#include <sys/file.h>
#endif

#include <string.h>
#include <malloc.h>

#define BUFSIZ 80

/* This program and the accompanying files were written by */
/* Travis Mccord, 11045 Wagon Ho Trail, Reno NV */
/* completed September of 1991. */

char  ch;
short secno;

char *ops[32];
char *worlds[60];
char *xboat[10];
char *other[60];

int   f1, f2, f3;		/* file descriptors */

void
zerops()
{
   int   g;

   for (g = 0; g < 32 && ops[g] != NULL; ++g) {
      free(ops[g]);
      ops[g] = NULL;
   }
}


char *
strmov(c)
   char  c[];
{
   int   l;
   char *x1;

   l = strlen(c);
   x1 = malloc(l + 1);
   (void) strcpy(x1, c);
   return x1;
}

int
getops(fin)
   int   fin;
{
   int   cp = 0;
   char  c1, c2, line[60];
   int   st1, st2, k;

   zerops();
   st1 = st2 = 0;
   do {
      for (st1 = 0; (c2 = read(fin, &c1, 1)) && c1 != ',' && c1 != '\n'; ++st1) {
	 if (c2 == -1) {
	    perror("Error reading input file!");
	    exit(-2);
	 }
	 line[st1] = c1;
	 if (st1 == 59)
	    break;
      }
      line[st1] = 0;
      if (line[0] == ' ') {	/* scratch leading spaces */
	 st2 = 1;
	 while (line[st2] == ' ' && st2 < st1)
	    st2++;
	 st1 -= st2;
	 for (k = 0; k < st1; k++)
	    line[k] = line[k + st2];
	 line[st1] = 0;
      }
      if (!c2) {
	 st2 = 2;
	 ops[0] = NULL;
	 return 1;
      }
      st2 = (c1 == '\n');

      if (!st1)
	 ops[cp] = NULL;
      else
	 ops[cp] = strmov(line);
      ++cp;
   }
   while (!st2);

   return st2 == 2;
}

char *
itoa(num)
   int   num;
{
   char *o;

   o = malloc(6);
   (void) sprintf(o, "%d", num);
   return o;
}

void
caps(name)
   char *name;
{
   int   g;

   for (g = 0; name[g]; g++)
      if (isalpha(name[g]))
	 name[g] = toupper(name[g]);
}

void
interpret()
{
   /* takes **ops and interprets it for *worlds or **xboat or **other       */

   int   cp = 0;
   char *loc, line[100], tt;
   int   x, y, z;
   int   xd, yd;

   if (!(ops[0]))
      return;
   if (*ops[cp] == '!') {
      switch (*(ops[cp] + 1)) {
      case 'a':
	 switch (*(ops[1])) {
	 case 't':
	    x = 0;
	    break;
	 case 'l':
	    x = 1;
	    break;
	 case 'b':
	    x = 2;
	    break;
	 case 'r':
	    x = 3;
	    break;
	 default:
	    perror("Error in !adj statement\n");
	    exit(1);
	 }
	 (void) strcpy(line, "\t(");
	 (void) strcat(line, ops[2]);
	 (void) strcat(line, ") ");
	 for (y = 0; *(line + y); ++y);
	 line[y++] = x + '0';
	 line[y] = 0;
	 (void) strcat(line, " bords\n");
	 for (y = 0; other[y] != NULL; ++y);
	 other[y] = strmov(line);
	 *(other + y + 1) = NULL;
	 break;
      case 'b':
	 x = atoi((ops[1]) + 1);
	 switch (*(ops[1])) {
	 case 't':
	    loc = "\tgridUL exch %3.1f hexside mul add exch";
	    (void) sprintf(line, loc, 0.5 + (3 * (x / 2)) + (x % 2));
	    (void) strcat(line, "\n\t(");
	    (void) strcat(line, *(ops + 2));
	    (void) strcat(line, ") borderdraw\n");
	    for (y = 0; other[y] != NULL; ++y);
	    other[y] = strmov(line);
	    other[y + 1] = NULL;
	    break;
	 case 'b':
	    loc = "\tgridUL 21 trheight mul sub exch %d hexside mul add exch";
	    (void) sprintf(line, loc, (3 * (x / 2)) + 2 * (x % 2));
	    (void) strcat(line, "\n\t(");
	    (void) strcat(line, *(ops + 2));
	    (void) strcat(line, ") borderdraw\n");
	    for (y = 0; *(other + y) != NULL; ++y);
	    other[y] = strmov(line);
	    other[y + 1] = NULL;
	    break;
	 case 'l':
	    loc = "\tgridUL %d trheight mul sub";
	    (void) sprintf(line, loc, 2 * x + 1);
	    (void) strcat(line, "\n\t(");
	    (void) strcat(line, *(ops + 2));
	    (void) strcat(line, ") borderdraw\n");
	    for (y = 0; other[y] != NULL; ++y);
	    other[y] = strmov(line);
	    other[y + 1] = NULL;
	    break;
	 case 'r':
	    loc = "\tgridUL exch 12.5 hexside mul add exch %d trheight mul sub";
	    (void) sprintf(line, loc, 2 * x + 1);
	    (void) strcat(line, "\n\t(");
	    (void) strcat(line, *(ops + 2));
	    (void) strcat(line, ") borderdraw\n");
	    for (y = 0; other[y] != NULL; ++y);
	    other[y] = strmov(line);
	    other[y + 1] = NULL;
	    break;
	 default:
	    perror("Error in !border statement");
	    exit(1);
	 }
	 break;
      case 's':
	 (void) strcpy(line, "\t(");
	 (void) strcat(line, *(ops + 1));
	 (void) strcat(line, ") 1 subtitle\n");
	 for (y = 0; other[y] != NULL; ++y);
	 other[y] = strmov(line);
	 other[y + 1] = NULL;
	 break;
      case 't':
	 (void) strcpy(line, "\t(");
	 (void) strcat(line, *(ops + 1));
	 (void) strcat(line, ") 0 subtitle\n");
	 for (y = 0; other[y] != NULL; ++y);
	 other[y] = strmov(line);
	 other[y + 1] = NULL;
	 break;
      case 'x':
	 if (!secno) {
	    perror("Xboat cannot be first line!");
	    exit(-2);
	 }
	 xd = 8 * ((secno - 1) % 4);
	 yd = 10 * ((secno - 1) / 4);
	 (void) strcpy(line, "\t[");
	 for (y = 1; *(ops + y) != NULL; ++y) {
	    int   hex;

	    hex = atoi(*(ops + y));
	    (void) strcat(line, " ");
	    (void) strcat(line, itoa((hex / 100) - xd));
	    (void) strcat(line, " ");
	    (void) strcat(line, itoa((hex % 100) - yd));
	 }
	 (void) strcat(line, " ] xboat\n");
	 for (y = 0; other[y] != NULL; ++y);
	 other[y] = strmov(line);
	 other[y + 1] = NULL;
	 break;
      case '!':		/* using double bang for comments */
	 break;			/* do nothing */
      default:
	 perror("Misplaced Bang");
	 exit(1);
      }
   } else {
      int   tz;

      z = atoi(ops[1]);
      tz = ((z / 100) - 1) / 8 + 1 + (((z % 100) - 1) / 10) * 4;
      if (secno != tz)
	 if (!secno)
	    secno = tz;
	 else {
	    perror("World outside of subsector!");
	    exit(-1);
	 }
      tt = ops[2][17];
      caps(ops[2]);
      ops[2][17] = tt;
      if (ops[2][4] == '9' || ops[2][4] >= 'A')
	 caps(ops[0]);
      if (ops[2][10] == 'X')
	 ops[2][10] = ' ';
      if (ops[2][12] == 'G')
	 ops[2][12] = ' ';	/* scratches G for Green zone */
      (void) sprintf(line, "\t(%s) %d (%s) (%s) doworld\n", ops[0],
		     z, ops[2], ops[3]);
      for (y = 0; *(worlds + y) != NULL; ++y);
      worlds[y] = strmov(line);
      worlds[y + 1] = NULL;
   }
}

void
sortworlds()
{
   char *a, *b;
   int   c;
   int   pos, pos2, pos3, tst;

   if (worlds[0] == NULL)
      return;

   for (pos = 0; worlds[pos] != NULL; ++pos);

   for (pos2 = pos - 1; pos2; --pos2) {
      c = pos2;
      for (pos3 = 0; pos3 < pos2; ++pos3) {
	 b = (ch) ? worlds[c] : strchr(worlds[c], ')') + 1;
	 a = (ch) ? worlds[pos3] : strchr(worlds[pos3], ')') + 1;
	 tst = (ch) ? strcmp(a, b) : ((atoi(a) > atoi(b)) ? 1 : 0);
	 if (tst > 0)
	    c = pos3;
      }
      if (c != pos2) {
	 char *tmp;

	 tmp = worlds[pos2];
	 worlds[pos2] = worlds[c];
	 worlds[c] = tmp;
      }
   }
}

main(argc, argv)
   int   argc;
   char **argv;
{
   int   tr;
   char  ins[BUFSIZ];

   secno = 0;
   for (--argc, ++argv; argc; --argc, ++argv) {
      if (**argv == '-') {
	 if (*(*argv + 1) == 0) {
	    (void) printf("Usage: sub2ps [-a] filename[.sub]\n");
	    exit(0);
	 } else if (*(*argv + 1) == 'a')
	    ch = -1;
	 else {
	    perror("Illegal option");
	    exit(1);
	 }
      } else {
	 char  xd[25];

	 if ((f3 = open(*argv, O_RDONLY, 0)) == -1) {
	    (void) strcpy(xd, *argv);
	    (void) strcat(xd, ".sub");
	    if ((f3 = open(xd, O_RDONLY, 0)) == -1) {
	       perror("Bad Filename");
	       exit(1);
	    }
	 }
	 (void) strcpy(xd, *argv);
	 (void) strcat(xd, ".ps");
	 if ((f2 = creat(xd, 0666)) == -1) {
	    perror("Can't open output file!");
	    exit(1);
	 }
	 if ((f1 = open("ps1", O_RDONLY, 0)) == -1) {
	    perror("Can't find ps files!");
	    exit(1);
	 }
	 for (tr = 0; (tr = read(f1, ins, BUFSIZ)) == BUFSIZ; (void) write(f2, ins, tr));
	 if (tr > 0)
	    (void) write(f2, ins, tr);
	 (void) close(f1);

	 do {
	    tr = getops(f3);
	    interpret();
	 }
	 while (!tr);
	 (void) close(f3);
	 sortworlds();
	 if (xboat[0] != NULL)
	    for (tr = 0; xboat[tr] != NULL; ++tr)
	       (void) write(f2, xboat[tr], strlen(xboat[tr]));
	 f1 = open("ps2", O_RDONLY, 0);
	 for (tr = 0; (tr = read(f1, ins, BUFSIZ)) > 0; (void) write(f2, ins, tr));
	 if (other[0] != NULL)
	    for (tr = 0; other[tr] != NULL; ++tr)
	       (void) write(f2, other[tr], strlen(other[tr]));
	 if (worlds[0] != NULL)
	    for (tr = 0; worlds[tr] != NULL; ++tr)
	       (void) write(f2, worlds[tr], strlen(worlds[tr]));
	 (void) write(f2, "\tshowpage\n%%Trailer\n\n", 21);

	 (void) close(f2);
      }
   }
}
