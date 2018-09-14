/************************************************************************
 ** File:
 **   $Id: cs_tablestbl.c 1.1 2012/09/14 16:05:14GMT-05:00 aschoeni Exp  $
 **
 ** Purpose: 
 **  The CFS Checksum (CS) Application Unit Test Tables Table Definition
 **
 ** Notes:
 **  This is a fully-populated table of valid entries, with all entries enabled.
 **  This table should be located in unit_test\cf\apps\CorrFullTable
 **
 ** $Log: cs_tablestbl.c  $
 ** Revision 1.1 2012/09/14 16:05:14GMT-05:00 aschoeni 
 ** Initial revision
 ** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/cs/fsw/unit_test/cf/apps/CorrNonFullTable/project.pj
 ** Revision 1.1 2011/09/06 15:21:48EDT jmdagost 
 ** Initial revision
 ** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/cs/fsw/unit_test/cf/apps/CorrFullTable/project.pj
 ** Revision 1.2 2010/05/03 17:30:07EDT jmdagost 
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
    /*   0 */ { CS_STATE_ENABLED,   "CS.DefAppTbl"             },
    /*   1 */ { CS_STATE_ENABLED,   "CS.DefTablesTbl"          },
    /*   2 */ { CS_STATE_ENABLED,   "CS.DefMemoryTbl"          },
    /*   3 */ { CS_STATE_ENABLED,   "CS.DefEepromTbl"          },
    /*   4 */ { CS_STATE_ENABLED,   "AA.Table1"                },
    /*   5 */ { CS_STATE_ENABLED,   "BB.Table1"                },
    /*   6 */ { CS_STATE_ENABLED,   "CC.Table1"                },
    /*   7 */ { CS_STATE_ENABLED,   "DD.Table1"                },
    /*   8 */ { CS_STATE_ENABLED,   "EE.Table1"                },
    /*   9 */ { CS_STATE_ENABLED,   "FF.Table1"                },
    /*  10 */ { CS_STATE_EMPTY,   ""                },
    /*  11 */ { CS_STATE_ENABLED,   "HH.Table1"                },
    /*  12 */ { CS_STATE_ENABLED,   "II.Table1"                },
    /*  13 */ { CS_STATE_ENABLED,   "JJ.Table1"                },
    /*  14 */ { CS_STATE_DISABLED,   "KK.Table1"                },
    /*  15 */ { CS_STATE_ENABLED,   "LL.Table1"                },
    /*  16 */ { CS_STATE_ENABLED,   "MM.Table1"                },
    /*  17 */ { CS_STATE_ENABLED,   "AA.Table2"                },
    /*  18 */ { CS_STATE_ENABLED,   "BB.Table2"                },
    /*  19 */ { CS_STATE_EMPTY,   ""                },
    /*  20 */ { CS_STATE_EMPTY,   ""                },
    /*  21 */ { CS_STATE_ENABLED,   "DD.Table2"                },
    /*  22 */ { CS_STATE_DISABLED,   "EE.Table2"                },
    /*  23 */ { CS_STATE_ENABLED,   "FF.Table2"                },

};

/************************/
/*  End of File Comment */
/************************/
