
/*******************************************************************************
 *  The BYTE UNIX Benchmarks - Release 3
 *          Module: arith.c   SID: 3.3 5/15/91 19:30:19
 *
 *******************************************************************************
 * Bug reports, patches, comments, suggestions should be sent to:
 *
 *	Ben Smith, Rick Grehan or Tom Yager
 *	ben@bytepb.byte.com   rick_g@bytepb.byte.com   tyager@bytepb.byte.com
 *
 *******************************************************************************
 *  Modification Log:
 *  May 12, 1989 - modified empty loops to avoid nullifying by optimizing
 *                 compilers
 *  August 28, 1990 - changed timing relationship--now returns total number
 *	                  of iterations (ty)
 *  November 9, 1990 - made changes suggested by Keith Cantrell
 *                        (digi!kcantrel) to defeat optimization
 *                        to non-existence
 *  October 22, 1997 - code cleanup to remove ANSI C compiler warnings
 *                     Andy Kahn <kahn@zk3.dec.com>
 *
 ******************************************************************************/

char SCCSid[] = "@(#) @(#)arith.c:3.3 -- 5/15/91 19:30:19";
/*
 *  arithmetic test
 *
 */

#include <stdio.h>
#include <stdlib.h>

int dumb_stuff(int);

volatile unsigned long iter;

/* this function is called when the alarm expires */
void report()
{
	printf("COUNT|%ld|1|lps\n", iter);
	exit(0);
}

int main(argc, argv)
int	argc;
char	*argv[];
{
	int	duration;
	int result = 0;

	duration = 10;


	/* set up alarm call */
	iter = 0;	/* init iteration count */
	// wake_me(duration, report);

    int start = get_time();

	/* this loop will be interrupted by the alarm call */
	while (1)
	{
        /* in switching to time-based (instead of iteration-based),
           the following statement was added. It should not skew
           the timings too much--there was an increment and test
           in the "while" expression above. The only difference is
           that now we're incrementing a long instead of an int.  (ty) */
	++iter;
	/* the loop calls a function to insure that something is done
	   the results of the function are fed back in (just so they
	   they won't be thrown away. A loop with
	   unused assignments may get optimized out of existence */
	result = dumb_stuff(result);
	// }
    int temp = get_time() - start;
    if(temp >= 10000){
        break;
    }
    }
	printf("COUNT|%ld|1|lps\n", iter);
	exit(0);
}


/************************** dumb_stuff *******************/
int dumb_stuff(i)
int i;
{
	float	x, y, z;
		z = 0;
        /*
		 *     101
		 * sum       i*i/(i*i-1)
		 *     i=2
		 */
		/* notice that the i value is always reset by the loop */
		for (i=2; i<=101; i++){
			x = i;
			y = x*x;
		    z += y/(y-1);
		}

    return(x+y+z);
}
