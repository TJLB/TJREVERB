/************************************************************************
 ** File:
 **   $Id: cs_tablestbl.c 1.1 2011/09/06 14:25:03GMT-05:00 jmdagost Exp  $
 **
 ** Purpose: 
 **  The CFS Checksum (CS) Application Unit Test Tables Table Definition
 **
 ** Notes:
 **  This is a partially-populated table with an invalid entry (state).
 **  This table should be located in unit_test\cf\apps\InvldStNonFullTable
 **
 ** $Log: cs_tablestbl.c  $
 ** Revision 1.1 2011/09/06 14:25:03GMT-05:00 jmdagost 
 ** Initial revision
 ** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/cs/fsw/unit_test/cf/apps/InvldStNonFullTable/project.pj
 ** Revision 1.2 2010/05/03 17:30:06EDT jmdagost 
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
    "CS_TablesTable", "CS.DefTablesTbl", "CS Tables Tbl",
    "cs_tablestbl.tbl", sizeof (CS_Def_Tables_Table_Entry_t) * CS_MAX_NUM_TABLES_TABLE_ENTRIES
};

CS_Def_Tables_Table_Entry_t CS_TablesTable[CS_MAX_NUM_TABLES_TABLE_ENTRIES]= 
{
    /*         State               Name   */
    /*   0 */ { 0x12            ,   "CS.DefAppTbl"             },
    /*   1 */ { CS_STATE_ENABLED,   "CS.DefTablesTbl"          },
    /*   2 */ { CS_STATE_ENABLED,   "CS.DefMemoryTbl"          },
    /*   3 */ { CS_STATE_ENABLED,   "CS.DefEepromTbl"          },
    /*   4 */ { CS_STATE_EMPTY,     ""                         },
    /*   5 */ { CS_STATE_EMPTY,     ""                         },
    /*   6 */ { CS_STATE_EMPTY,     ""                         },
    /*   7 */ { CS_STATE_EMPTY,     ""                         },
    /*   8 */ { CS_STATE_EMPTY,     ""                         },
    /*   9 */ { CS_STATE_EMPTY,     ""                         },
    /*  10 */ { CS_STATE_EMPTY,     ""                         },
    /*  11 */ { CS_STATE_EMPTY,     ""                         },
    /*  12 */ { CS_STATE_EMPTY,     ""                         },
    /*  13 */ { CS_STATE_EMPTY,     ""                         },
    /*  14 */ { CS_STATE_EMPTY,     ""                         },
    /*  15 */ { CS_STATE_EMPTY,     ""                         },
    /*  16 */ { CS_STATE_EMPTY,     ""                         },
    /*  17 */ { CS_STATE_EMPTY,     ""                         },
    /*  18 */ { CS_STATE_EMPTY,     ""                         },
    /*  19 */ { CS_STATE_EMPTY,     ""                         },
    /*  20 */ { CS_STATE_EMPTY,     ""                         },
    /*  21 */ { CS_STATE_EMPTY,     ""                         },
    /*  22 */ { CS_STATE_EMPTY,     ""                         },
    /*  23 */ { CS_STATE_EMPTY,     ""                         },
};

/************************/
/*  End of File Comment */
/************************/
