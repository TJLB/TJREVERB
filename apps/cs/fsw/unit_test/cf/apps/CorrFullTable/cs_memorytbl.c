/************************************************************************
 ** File:
 **   $Id: cs_memorytbl.c 1.1 2011/09/06 14:21:47GMT-05:00 jmdagost Exp  $
 **
 ** Purpose: 
 **  The CFS Checksum (CS) Application Unit Test Memory Table Definition
 **
 ** Notes:
 **  This is a fully-populated table with all entries enabled.
 **  This table should be located in unit_test\cf\apps\CorrFullTable.
 **  The unit test overwrites the StartAddress and NumBytes fields with
 **   valid values after the table is loaded.  Otherwise there is a risk
 **   of generating a segmentation fault.
 **
 ** $Log: cs_memorytbl.c  $
 ** Revision 1.1 2011/09/06 14:21:47GMT-05:00 jmdagost 
 ** Initial revision
 ** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/cs/fsw/unit_test/cf/apps/CorrFullTable/project.pj
 ** Revision 1.2 2010/05/03 17:30:05EDT jmdagost 
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
    "CS_MemoryTable", "CS.DefMemoryTbl", "CS Memory Tbl",
    "cs_memorytbl.tbl", sizeof (CS_Def_EepromMemory_Table_Entry_t) * CS_MAX_NUM_MEMORY_TABLE_ENTRIES
};

CS_Def_EepromMemory_Table_Entry_t CS_MemoryTable[CS_MAX_NUM_MEMORY_TABLE_ENTRIES]= 
{
    /*         State             Filler   StartAddress     NumBytes */
    /*  0 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000100  },
    /*  1 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000200  },
    /*  2 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000400  },
    /*  3 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000800  },
    /*  4 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00001000  },
    /*  5 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000100  },
    /*  6 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000200  },
    /*  7 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000400  },
    /*  8 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000800  },
    /*  9 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00001000  },
    /* 10 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000100  },
    /* 11 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000200  },
    /* 12 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000400  },
    /* 13 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000800  },
    /* 14 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00003000  },
    /* 15 */ { CS_STATE_ENABLED, 0x1234,  0x00034020,      0x00000800  },

};

/************************/
/*  End of File Comment */
/************************/
