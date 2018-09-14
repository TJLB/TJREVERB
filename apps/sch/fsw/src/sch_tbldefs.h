/*
** $Id: sch_tbldefs.h 1.1 2008/10/16 15:08:38EDT dkobe Exp  $
**
** Subsystem: Scheduler (SCH) table definitions
**
** Author:
**
** Notes:
**
** $Log: sch_tbldefs.h  $
** Revision 1.1 2008/10/16 15:08:38EDT dkobe 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/sch/fsw/src/project.pj
*/

/*************************************************************************
**
** Ensure that "this" header is included only once
**
**************************************************************************/

#ifndef _sch_tbldefs_
#define _sch_tbldefs_

/*************************************************************************
**
** SCH table structure definitions
**
**************************************************************************/

/*
** Schedule definition table entry
*/
typedef struct
{
    uint8    EnableState;          /**< \brief State may be #SCH_UNUSED, #SCH_ENABLED, #SCH_DISABLED */
    uint8    Type;                 /**< \brief Activity Type may be #SCH_ACTIVITY_NONE or #SCH_ACTIVITY_SEND_MSG */
    uint16   Frequency;            /**< \brief Number of seconds between Activity execution */
    uint16   Remainder;            /**< \brief Seconds offset to perform Activity */
    uint16   MessageIndex;         /**< \brief Byte index into Message Definition Table */

    uint32   GroupData;            /**< \brief Group and Multi-Group membership definitions */

} SCH_ScheduleEntry_t;

/*
** Message definition table entry
*/
typedef struct
{
    uint16   MessageBuffer[SCH_MAX_MSG_WORDS]; /**< \brief Packed Messages */

} SCH_MessageEntry_t;


#endif /* _sch_tbldefs_ */
