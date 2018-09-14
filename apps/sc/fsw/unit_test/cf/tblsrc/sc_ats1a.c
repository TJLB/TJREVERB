 /*************************************************************************
 ** File:
 **   $Id: sc_ats1a.c 1.1 2009/01/26 14:41:57EST nyanchik Exp  $
 **
 ** Purpose: 
 **   This file contains a sample of creating an RTS table
 **
 ** References:
 **   Flight Software Branch C Coding Standard Version 1.2
 **   CFS Development Standards Document
 ** Notes:
 **
 **   $Log: sc_ats1a.c  $ 
 **   Revision 1.1 2009/01/26 14:41:57EST nyanchik  
 **   Initial revision 
 **   Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/sc/fsw/unit_test/cf/tblsrc/project.pj 
 *************************************************************************/

#include "sc_app.h"
#include "cfe_tbl_filedef.h"


/************************************************************************
The structure of a cFE raw command using CCSDS. 
Note the command shown has no parameters. If more parameters are needed, the are added after the checksum.

0x1803, 0xC000, 0x0001, 0x0000
   ^       ^      ^     ^ ^ 
   |       |      |     | the last byte is the checksum for the command
   |       |      |     The first byte is the command code
   |       |      2 bytes for the length of command after these two bytes
   |       2 bytes for sequence counter always 0xC000
   The application to recieve and processs the command in app_msgids.h
   
note that in the case of SC, there is information before the cFE command structure,
like the time tag and the command number (for ATS's)
************************************************************************/

uint16     SC_Ats1a[SC_ATS_BUFF_SIZE] = {
/* This is a valid table that does not go to the end of the buffer  */
/* 8F below is the checksum for the command
 Send a few commands, and then to a switch ATS 
to test switching */

0x0000, 0x0001, 0x0080, 0x0000, 0x18A9, 0xC000, 0x0001, 0x008F,
0x0000, 0x0002, 0x0082, 0x0000, 0x18A9, 0xC000, 0x0001, 0x008F,
0x0000, 0x0003, 0x0079, 0x0000, 0x18A9, 0xC000, 0x0001, 0x008F,

/* Switch ATS to test internal switching */
0x0000, 0x0004, 0x0088, 0x0000, 0x18A9, 0xC000, 0x0001, 0x0887 

};

CFE_TBL_FILEDEF(SC_Ats1a, SC_APP.ATS_TBL1, SC ATS table 1a,ATS_TBL1a.tbl)


/************************/
/*  End of File Comment */
/************************/

