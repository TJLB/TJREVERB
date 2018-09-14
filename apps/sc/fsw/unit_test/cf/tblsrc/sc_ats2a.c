 /*************************************************************************
 ** File:
 **   $Id: sc_ats2a.c 1.1 2009/01/26 14:42:02EST nyanchik Exp  $
 **
 ** Purpose: 
 **   This file contains a sample of creating an RTS table
 **
 ** References:
 **   Flight Software Branch C Coding Standard Version 1.2
 **   CFS Development Standards Document
 ** Notes:
 **
 **   $Log: sc_ats2a.c  $ 
 **   Revision 1.1 2009/01/26 14:42:02EST nyanchik  
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

uint16     SC_Ats2a[SC_ATS_BUFF_SIZE] = {
/* This table tests sending out a command with a bad checksum and then continuing on or not */

0x0000, 0x0001, 0x0094, 0x0000, 0x18A9, 0xC000, 0x0001, 0x008F,
0x0000, 0x0002, 0x0096, 0x0000, 0x18A9, 0xC000, 0x0001, 0x008F,
0x0000, 0x0003, 0x0092, 0x0000, 0x18A9, 0xC000, 0x0001, 0x008F,

/* Unknown Command, but as long as I could make it, 68 words total, FD is checksum for this command */
0x0000, 0x0004, 0x00A0, 0x0000, 0x18A9, 0xC000, 0x0079, 0x0AFD, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,


/* Send out a command with a bad checksum */
0x0000, 0x0005, 0x00A2, 0x0000, 0x18A9, 0xC000, 0x0001, 0x00FF,

/* Testing continuing on sending out the  commands after a checksum failure */
0x0000, 0x0006, 0x00A4, 0x0000, 0x18A9, 0xC000, 0x0001, 0x008F

};

CFE_TBL_FILEDEF(SC_Ats2a, SC_APP.ATS_TBL2, SC ATS table 2a,ATS_TBL2a.tbl)


/************************/
/*  End of File Comment */
/************************/

