/************************************************************************
** File:
**   $Id: cs_apptbl.c 1.3 2012/09/14 13:54:10GMT-05:00 aschoeni Exp  $
**
** Purpose: 
**  The CFS Checksum (CS) Application Default Apps Table Definition
**
** Notes:
**
** $Log: cs_apptbl.c  $
** Revision 1.3 2012/09/14 13:54:10GMT-05:00 aschoeni 
** Now uses macro for header
** Revision 1.2 2010/07/16 13:22:33EDT jmdagost 
** Corrected app name from "CS_APP" to "CS".
** Revision 1.1 2010/03/09 15:30:19EST jmdagost 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/cs/fsw/tables/project.pj
**
*************************************************************************/


/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "cs_platform_cfg.h"
#include "cs_msgdefs.h"
#include "cs_tbldefs.h"
#include "cfe_tbl_filedef.h"

CS_Def_App_Table_Entry_t      CS_AppTable[CS_MAX_NUM_APP_TABLE_ENTRIES] =
{
    /*            State             Name   */
    /*   0 */ { CS_STATE_EMPTY,     ""      },
    /*   1 */ { CS_STATE_EMPTY,     ""      },
    /*   2 */ { CS_STATE_EMPTY,     ""      },
    /*   3 */ { CS_STATE_EMPTY,     ""      },
    /*   4 */ { CS_STATE_EMPTY,     ""      },
    /*   5 */ { CS_STATE_EMPTY,     ""      },
    /*   6 */ { CS_STATE_EMPTY,     ""      },
    /*   7 */ { CS_STATE_EMPTY,     ""      },
    /*   8 */ { CS_STATE_EMPTY,     ""      },
    /*   9 */ { CS_STATE_EMPTY,     ""      },
    /*  10 */ { CS_STATE_EMPTY,     ""      },
    /*  11 */ { CS_STATE_EMPTY,     ""      },
    /*  12 */ { CS_STATE_EMPTY,     ""      },
    /*  13 */ { CS_STATE_EMPTY,     ""      },
    /*  14 */ { CS_STATE_EMPTY,     ""      },
    /*  15 */ { CS_STATE_EMPTY,     ""      },
    /*  16 */ { CS_STATE_EMPTY,     ""      },
    /*  17 */ { CS_STATE_EMPTY,     ""      },
    /*  18 */ { CS_STATE_EMPTY,     ""      },
    /*  19 */ { CS_STATE_EMPTY,     ""      },
    /*  20 */ { CS_STATE_EMPTY,     ""      },
    /*  21 */ { CS_STATE_EMPTY,     ""      },
    /*  22 */ { CS_STATE_EMPTY,     ""      },
    /*  23 */ { CS_STATE_EMPTY,     ""      }

};

/*
** Table file header
*/
CFE_TBL_FILEDEF(CS_AppTable, CS.DefAppTbl, CS App Tbl, cs_apptbl.tbl)

/************************/
/*  End of File Comment */
/************************/
