/************************************************************************
 ** File:
 **   $Id: cs_apptbl.c 1.1 2012/09/14 16:05:20GMT-05:00 aschoeni Exp  $
 **
 ** Purpose: 
 **  The CFS Checksum (CS) Application Unit Test Apps Table Definition
 **
 ** Notes:
 **  This is a partially-populated table with a single invalid entry (name).
 **  This table should be located in unit_test\cf\apps\InvldNameNonFullTable
 **
 ** $Log: cs_apptbl.c  $
 ** Revision 1.1 2012/09/14 16:05:20GMT-05:00 aschoeni 
 ** Initial revision
 ** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/cs/fsw/unit_test/cf/apps/InvldEmptyNonFullTable/project.pj
 ** Revision 1.1 2011/09/06 15:24:15EDT jmdagost 
 ** Initial revision
 ** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/cs/fsw/unit_test/cf/apps/InvldNameNonFullTable/project.pj
 ** Revision 1.2 2010/05/03 17:30:03EDT jmdagost 
 ** Major updates to test table data for CS unit test changes.
 **
 *************************************************************************/

#include "cfe.h"
#include "cs_platform_cfg.h"
#include "cs_msgdefs.h"
#include "cs_tbldefs.h"
#include "cfe_tbl_filedef.h"

static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "CS_AppTable", "CS.DefAppTbl", "CS App Tbl",
    "cs_apptbl.tbl", sizeof (CS_Def_App_Table_Entry_t) * CS_MAX_NUM_APP_TABLE_ENTRIES
};

CS_Def_App_Table_Entry_t CS_AppTable[CS_MAX_NUM_APP_TABLE_ENTRIES]= 
{
    /*         State               Name   */
    /*   0 */ { CS_STATE_ENABLED,   "" },
    /*   1 */ { CS_STATE_EMPTY,     ""          },
    /*   2 */ { CS_STATE_EMPTY,     ""          },
    /*   3 */ { CS_STATE_EMPTY,     ""          },
    /*   4 */ { CS_STATE_EMPTY,     ""          },
    /*   5 */ { CS_STATE_EMPTY,     ""          },
    /*   6 */ { CS_STATE_EMPTY,     ""          },
    /*   7 */ { CS_STATE_EMPTY,     ""          },
    /*   8 */ { CS_STATE_EMPTY,     ""          },
    /*   9 */ { CS_STATE_EMPTY,     ""          },
    /*  10 */ { CS_STATE_EMPTY,     ""          },
    /*  11 */ { CS_STATE_EMPTY,     ""          },
    /*  12 */ { CS_STATE_EMPTY,     ""          },
    /*  13 */ { CS_STATE_EMPTY,     ""          },
    /*  14 */ { CS_STATE_EMPTY,     ""          },
    /*  15 */ { CS_STATE_EMPTY,     ""          },
    /*  16 */ { CS_STATE_EMPTY,     ""          },
    /*  17 */ { CS_STATE_EMPTY,     ""          },
    /*  18 */ { CS_STATE_EMPTY,     ""          },
    /*  19 */ { CS_STATE_EMPTY,     ""          },
    /*  20 */ { CS_STATE_EMPTY,     ""          },
    /*  21 */ { CS_STATE_EMPTY,     ""          },
    /*  22 */ { CS_STATE_EMPTY,     ""          },
    /*  23 */ { CS_STATE_EMPTY,     ""          },
};

/************************/
/*  End of File Comment */
/************************/
