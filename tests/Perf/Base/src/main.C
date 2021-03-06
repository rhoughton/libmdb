//
// File:        main.C
// Project:	Mdb
// Desc:        
//
//  Application entry point.
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     07/10/97 06:03
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include "MdbConfig.hh"
#include "AppParam.hh"
#include <iostream>
#include <cstdio>

AppParam * App = 0;

MDB_FUNCT_VERSION(
  main,
  "$Id$");

bool
pAvlTreeOffset(
 const char *	fileName,
 long		recSize,
 size_t		initAllocNumRecs,
 long		quantity,
 ostream &	perfLog
 );

bool
pRBSet(
 const char *	fileName,
 long		recSize,
 size_t		initAllocNumRecs,
 long		quantity,
 ostream &	perfLog
 );

int
main( int argc, char * argv[] )
{

  if( (App = new AppParam( argc, argv, VERID_main ) ) == 0 )
    {
      cerr << "Can't new AppParam." << endl;
      exit( 1 );
    }

  if( ! App->good() || App->help() || ! App->allArgs() )
    App->abort( 1, true, __FILE__, __LINE__ );


  ofstream	perfLog( App->perfLogFn() );

  if( ! perfLog.good() )
    {
      AppError << "Perf log: '" << App->perfLogFn() << "' - "
	       << strerror( errno )
	       << endl;
      exit( 1 );
    }

  perfLog.setf( ios::left, ios::adjustfield );
  perfLog << setw(10) << "App Name"
	  << ' '
	  << setw(12) << "Pass Num"
	  << ' '
	  << setw(24) << "Map Type"
	  << ' '
	  << setw( 5 ) << "I SZ"
	  << ' '
	  << setw( 4) << "A SZ"
	  << ' '
	  << setw( 4 ) << "R SZ"
	  << ' '
	  << setw( 24 ) << "Class"
	  << ' '
	  << setw( 10 ) << "Meth"
	  << ' '
	  << setw( 5 ) << "Order"
	  << ' '
	  << setw( 8 ) << "Start SZ"
	  << ' '
	  << setw( 8 ) << "Quantity"
	  << '\n'
	  << endl
    ;
  
  perfLog.setf( ios::internal, ios::adjustfield );

  
  static long RecSize[] = { 4, 128, 512, 1024, -1 };
  static long Quantity[] = { 1024, 10000, 100000, 500000, -1 };
  
  for( long qty = 0; Quantity[qty] > 0; ++ qty )
    {
      for( long rs = 0; RecSize[rs] > 0; ++ rs )
	{
#if defined( FIXME_ALV )
	  pAvlTreeOffset( "../data/perf.test",
			  RecSize[rs],
			  1,
			  Quantity[qty],
			  perfLog );
	  
	  pAvlTreeOffset( "../data/perf.test",
			  RecSize[rs],
			  Quantity[qty] / 2,
			  Quantity[qty],
			  perfLog );
#endif
	  
	  pRBSet( "../data/perf.test",
		  RecSize[rs],
		  1,
		  Quantity[qty],
		  perfLog );

	  pRBSet( "../data/perf.test",
		  RecSize[rs],
		  Quantity[qty] / 2,
		  Quantity[qty],
		  perfLog );
	}
    }
  
  
  return( 0 );
}
//
// Revision Log:
//
// $Log$
// Revision 4.1  2001/07/27 00:57:46  houghton
// Change Major Version to 4
//
// Revision 2.2  2000/05/27 14:31:56  houghton
// Port: Sun CC 5.0.
//
// Revision 2.1  1997/09/21 19:22:05  houghton
// Changed version to 2
//
// Revision 1.4  1997/07/19 19:55:14  houghton
// Reorederd loops.
//
// Revision 1.3  1997/07/16 19:20:51  houghton
// *** empty log message ***
//
// Revision 1.2  1997/07/14 10:52:29  houghton
// Reworked test order and put into a loop. (Still needs more work)
//
// Revision 1.1  1997/07/13 11:36:40  houghton
// Initial Version.
//
//

