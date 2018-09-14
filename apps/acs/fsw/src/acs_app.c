/*******************************************************************************
** File: acs_app.c
**
** Purpose:
**   This file contains the source code for the ACS App.
**
*******************************************************************************/

/*
**   Include Files:
*/

#include "acs_app.h"
#include "acs_perfids.h"
#include "acs_msgids.h"
#include "acs_msg.h"
#include "acs_events.h"
#include "acs_table.h"
#include "acs_version.h"
#include "acs_top.h"
#include "dhl_lib.h"
#include "sc_msgids.h"
#include "dagr_msgids.h"
#include "dagr_msg.h"
#include "rw_msg.h"
#include "stdint.h"
#include "mode_lib.h"

acs_hk_tlm_t      ACS_HkTlmPkt;
acs_spt_tlm_t     ACS_SptTlmPkt;
acs_sci_tlm_t     ACS_SciTlmPkt;
acs_sdp_tlm_t     ACS_SdpTlmPkt;
acs_ad_tlm_t      ACS_AdTlmPkt;
acs_mpu_tlm_t     ACS_MpuTlmPkt;
dagr_acs_tlm_t    DagrBoomPkt;
rw_torque_cmd_t   RWTorqueCmdPkt;
acs_state_t       ACS_State;

CFE_SB_PipeId_t   ACS_CommandPipe;

int8_t   akf_enable = 0;
static int8_t   rw_config = CFG_RW_IDLE;  //= CFG_RW_SUNPT, CFG_RW_LVLH, CFG_RW_IDLE;
static int8_t   mtc_config = CFG_MTC_IDLE; //CFG_MTC_IDLE; //CFG_MTC_MOMMNG;
//float    gain_att_sci[3] =  {0.0122, 0.0154, 0.0018};
//float    gain_int_sci[3] =  {8.69E-6, 1.1E-5, 1.32E-6};
//float    gain_att_sci[3] =  {0.0, 0.0, 0.0};
//float    gain_int_sci[3] =  {0.0, 0.0, 0.0};
//float    gain_rate_sci[3] =  {0.0435, 0.055, 0.0066};
//float    gain_rate_sci[3] =  {0.0, 0.055, 0.0};
//float    gain_rate_sun[3] =  {0.01, 0.01, 0.01}; 
//float    gain_att_sun[3] =  {0.001, 0.001, 0.001}; 
//float    rate_cmd_sun = 0.000;
//float    targ_cmd_sci[4] = {0.0, 1.0, 0.0, 0.5};
//float    targ_cmd_sci[4] = {0.5, -0.5, 0.5, 0.5};
//float    targ_cmd_sci[4] = {0.0, -0.7071, 0.0, 0.7071};
//float    targ_cmd_sci[4] = {0.7071, 0.0, 0.7071, 0};
//float    rate_cmd_sci[3] = { 0.0, 0.0, 0.0};

acs_diag_flags_t  ACS_DiagTlmFlags = {0, 0, 0, 0};

static CFE_EVS_BinFilter_t  ACS_EventFilters[] =
       {  /* Event ID    mask */
          {ACS_STARTUP_INF_EID,       0x0000},
          {ACS_COMMAND_ERR_EID,       0x0000},
          {ACS_COMMANDNOP_INF_EID,    0x0000},
          {ACS_COMMANDRST_INF_EID,    0x0000},
       };

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* ACS_AppMain() -- Application entry point and main process loop              */
/*                                                                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * * */
void ACS_AppMain( void )
{
    int32             status;
    uint32            RunStatus = CFE_ES_APP_RUN;
    CFE_SB_MsgPtr_t   ACSMsgPtr;

    CFE_ES_PerfLogEntry(ACS_APP_PERF_ID);

    printf("Entering ACS App Main");
	 //printf("gain_AttSci: %f %f %f\n", gain_att_sci[0], gain_att_sci[1], gain_att_sci[2]); 
	 //printf("gain_RateSci: %f %f %f\n", gain_rate_sci[0], gain_rate_sci[1], gain_rate_sci[2]); 
	 //printf("gain_IntSci: %f %f %f\n", gain_int_sci[0], gain_int_sci[1], gain_int_sci[2]); 
	 printf("gain_AttSci: %f %f %f\n", ACS_Constants.gain_att_sci[0], ACS_Constants.gain_att_sci[1], ACS_Constants.gain_att_sci[2]); 
	 printf("gain_RateSci: %f %f %f\n", ACS_Constants.gain_rate_sci[0], ACS_Constants.gain_rate_sci[1], ACS_Constants.gain_rate_sci[2]); 
	 printf("gain_IntSci: %f %f %f\n", ACS_Constants.gain_int_sci[0], ACS_Constants.gain_int_sci[1], ACS_Constants.gain_int_sci[2]); 
    ACS_AppInit();

    /*
    ** ACS Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
        CFE_ES_PerfLogExit(ACS_APP_PERF_ID);

        status = CFE_SB_RcvMsg(&ACSMsgPtr, ACS_CommandPipe, CFE_SB_PEND_FOREVER);
        
        CFE_ES_PerfLogEntry(ACS_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            ACS_ProcessCommandPacket(ACSMsgPtr);
        }

    }

    CFE_ES_ExitApp(RunStatus);

} /* End of ACS_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* ACS_AppInit() --  initialization                                           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void ACS_AppInit(void)
{
    int32 Sbstatus;
    int32 Status;

    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp() ;

    ACS_State.SunPt_FirstCycle = 1;
    ACS_State.Science_FirstCycle = 1;

    /*
    ** Register the events
    */ 
    CFE_EVS_Register(ACS_EventFilters,
                     sizeof(ACS_EventFilters)/sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_BINARY_FILTER);

    /*
    ** Create the Software Bus command pipe and subscribe to housekeeping
    **  messages
    */
    Sbstatus = CFE_SB_CreatePipe(&ACS_CommandPipe, ACS_PIPE_DEPTH,"ACS_CMD_PIPE");
    if ( Sbstatus != CFE_SUCCESS)
       OS_printf("ACS: CFE_SB_CreatePipe returned an error!\n");

    CFE_SB_Subscribe(ACS_CMD_MID, ACS_CommandPipe);
    CFE_SB_Subscribe(ACS_SEND_HK_MID, ACS_CommandPipe);
    CFE_SB_Subscribe(ACS_WAKEUP_MID, ACS_CommandPipe);
    CFE_SB_Subscribe(DAGR_APP_ACS_TLM_MID, ACS_CommandPipe);

    ACS_ResetCounters();

    CFE_SB_InitMsg(&ACS_HkTlmPkt,
                   ACS_HK_TLM_MID,
                   ACS_HK_TLM_LNGTH, TRUE);

    CFE_SB_InitMsg(&ACS_SptTlmPkt,
                   ACS_DIAG_SPT_TLM_MID,
                   ACS_SPT_TLM_LNGTH, TRUE);

    CFE_SB_InitMsg(&ACS_SdpTlmPkt,
                   ACS_DIAG_SDP_TLM_MID,
                   ACS_SDP_TLM_LNGTH, TRUE);

    CFE_SB_InitMsg(&ACS_AdTlmPkt,
                   ACS_DIAG_AD_TLM_MID,
                   ACS_AD_TLM_LNGTH, TRUE);

    CFE_SB_InitMsg(&ACS_MpuTlmPkt,
                   ACS_DIAG_MPU_TLM_MID,
                   ACS_MPU_TLM_LNGTH, TRUE);

    CFE_SB_InitMsg(&ACS_SciTlmPkt,
                   ACS_DIAG_SCI_TLM_MID,
                   ACS_SCI_TLM_LNGTH, TRUE);

    CFE_SB_InitMsg(&RWTorqueCmdPkt,
                   RW_TORQUE_CMD_MID,
                   RW_TORQUE_CMD_LNGTH, TRUE);

    /*
    ** Initialize and load the ACS table(s)
    */
    Status = ACS_ConstantTableInit();

//    ACS_ValidateConstantData();

    CFE_EVS_SendEvent (ACS_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "ACS App Initialized. Version %d.%d.%d.%d",
                ACS_APP_MAJOR_VERSION,
                ACS_APP_MINOR_VERSION, 
                ACS_APP_REVISION, 
                ACS_APP_MISSION_REV);
				
} /* End of ACS_AppInit() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Name:  ACS_ProcessCommandPacket                                           */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the ACS       */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ProcessCommandPacket(CFE_SB_MsgPtr_t MessagePtr)
{
    CFE_SB_MsgId_t  MsgId;

    MsgId = CFE_SB_GetMsgId(MessagePtr);
    //printf("MsgId = %x\n", MsgId);

    switch (MsgId)
    {
        case ACS_CMD_MID:
            ACS_ProcessGroundCommand(MessagePtr);
            break;

        case ACS_SEND_HK_MID:
            ACS_ReportHousekeeping();
            break;

        case ACS_WAKEUP_MID:
            ACS_Run(MessagePtr);
            break;

        case DAGR_APP_ACS_TLM_MID:
            ACS_ProcessDagrBoomPkt(MessagePtr);
            break;

        default:
            ACS_HkTlmPkt.acs_command_error_count++;
            CFE_EVS_SendEvent(ACS_COMMAND_ERR_EID,CFE_EVS_ERROR,
			   "ACS: invalid command packet,MID = 0x%x", MsgId);
            break;
    }

    return;

} /* End ACS_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* ACS_ProcessGroundCommand() -- ACS ground commands                    */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void ACS_ProcessGroundCommand(CFE_SB_MsgPtr_t MessagePtr)
{
    uint16        CommandCode;
    CommandCode = CFE_SB_GetCmdCode(MessagePtr);
    //printf("ProcessCommandCode is %d\n", CommandCode);

    /* Process "known" ACS app ground commands */
    switch (CommandCode)
    {
        case ACS_NOOP_CC:
            ACS_HkTlmPkt.acs_command_count++;
            CFE_EVS_SendEvent(ACS_COMMANDNOP_INF_EID,CFE_EVS_INFORMATION,
			   "ACS: NOOP command");
            break;

        case ACS_RESET_COUNTERS_CC:
            ACS_HkTlmPkt.acs_command_count++;
            ACS_ResetCounters();
            break;

        case ACS_SPT_CC:
            ACS_HkTlmPkt.acs_command_count++;
            ACS_ReportSptTlmPkt();
             break;
		
        case ACS_SCI_CC:
            ACS_HkTlmPkt.acs_command_count++;
            ACS_ReportSciTlmPkt();
             break;
	
        case ACS_SDP_CC:
            ACS_HkTlmPkt.acs_command_count++;
            ACS_ReportSdpTlmPkt();
             break;

        case ACS_MPU_CC:
            ACS_HkTlmPkt.acs_command_count++;
            ACS_ReportMpuTlmPkt();
             break;

        case ACS_AD_CC:
            ACS_HkTlmPkt.acs_command_count++;
            ACS_ReportAdTlmPkt();
             break;

        case ACS_MODE_CC:
            ACS_HkTlmPkt.acs_command_count++;
             ACS_Mode(MessagePtr);
             break;
           
        //case ACS_SCIGAIN_CC:
         //   ACS_HkTlmPkt.acs_command_count++;
         //    ACS_SciGain(MessagePtr);
         //    break;

        //case ACS_SUNGAIN_CC:
        //    ACS_HkTlmPkt.acs_command_count++;
        //     ACS_SunGain(MessagePtr);
        //     break;
        
        //case ACS_RATETARG_CC:
         //   ACS_HkTlmPkt.acs_command_count++;
        //    ACS_RateTarg(MessagePtr);
        //     break;
        
        case ACS_PKTFLAG_CC:
             ACS_HkTlmPkt.acs_command_count++;
             ACS_FlagCheck(MessagePtr);
             break;

        default:
            break;
    }
    return;

} /* End of ACS_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_Mode                                                        */
/*  Purpose:                                                                  */
/*         ACS Mode Command                                               */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * */
void ACS_Mode(CFE_SB_MsgPtr_t MessagePtr)
{
   acs_ModeCmd_t* acs_ModeCmd = (acs_ModeCmd_t *) MessagePtr;
   akf_enable    = acs_ModeCmd->akf_enable; 
   rw_config  = acs_ModeCmd->rw_config;
   mtc_config = acs_ModeCmd->mtc_config;
#ifdef _ACS_DEBUG_ 
   printf("akf_enable is %d\n", akf_enable);
   printf("rw_config is %d\n", rw_config);
   printf("mtc_config is %d\n", mtc_config);
#endif

	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_SciGain                                                          */
/*  Purpose:                                                                  */
/*         ACS Gain Command                                                  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * */
/*
void ACS_SciGain(CFE_SB_MsgPtr_t MessagePtr)
{

   acs_SciGainCmd_t* acs_SciGainCmd = (acs_SciGainCmd_t *) MessagePtr;
   gain_att_sci[0]   = acs_SciGainCmd->gain_att_sci[0];
   gain_att_sci[1]   = acs_SciGainCmd->gain_att_sci[1];
   gain_att_sci[2]   = acs_SciGainCmd->gain_att_sci[2];
   gain_int_sci[0]   = acs_SciGainCmd->gain_int_sci[0];
   gain_int_sci[1]   = acs_SciGainCmd->gain_int_sci[1];
   gain_int_sci[2]   = acs_SciGainCmd->gain_int_sci[2];
   gain_rate_sci[0]  = acs_SciGainCmd->gain_rate_sci[0];
   gain_rate_sci[1]  = acs_SciGainCmd->gain_rate_sci[1];
   gain_rate_sci[2]  = acs_SciGainCmd->gain_rate_sci[2];
   
#ifdef _ACS_DEBUG_ 
	printf("gain_AttSci : %f %f %f\n", gain_att_sci[0], gain_att_sci[1], gain_att_sci[2]); 
	printf("gain_IntSci : %f %f %f\n", gain_int_sci[0], gain_int_sci[1], gain_int_sci[2]); 
	printf("gain_RateSci: %f %f %f\n", gain_rate_sci[0], gain_rate_sci[1], gain_rate_sci[2]); 
#endif

	return;
}
*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_SunGain                                                          */
/*  Purpose:                                                                  */
/*         ACS Sun Gain Command                                                  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * */
/*
void ACS_SunGain(CFE_SB_MsgPtr_t MessagePtr)
{

   acs_SunGainCmd_t* acs_SunGainCmd = (acs_SunGainCmd_t *) MessagePtr;
   gain_rate_sun[0]  = acs_SunGainCmd->gain_rate_sun[0];
   gain_rate_sun[1]  = acs_SunGainCmd->gain_rate_sun[1];
   gain_rate_sun[2]  = acs_SunGainCmd->gain_rate_sun[2];
   gain_att_sun[0]   = acs_SunGainCmd->gain_att_sun[0];
   gain_att_sun[1]   = acs_SunGainCmd->gain_att_sun[1];
   gain_att_sun[2]   = acs_SunGainCmd->gain_att_sun[2];

#ifdef _ACS_DEBUG_ 
	printf("gain_RateSun: %f %f %f\n", gain_rate_sun[0], gain_rate_sun[1], gain_rate_sun[2]); 
	printf("gain_AttSun : %f %f %f\n", gain_att_sun[0], gain_att_sun[1], gain_att_sun[2]); 
#endif

	return;
}
*/


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:    ACS_RateTarg                                                     */
/*  Purpose: ACS RateTarg Command                                             */
/*
void ACS_RateTarg(CFE_SB_MsgPtr_t MessagePtr)
{
   acs_RateTargCmd_t* acs_RateTargCmd = (acs_RateTargCmd_t *) MessagePtr;
   rate_cmd_sun    = acs_RateTargCmd->rate_cmd_sun; 
	targ_cmd_sci[0] = acs_RateTargCmd->targ_cmd_sci[0]; 
	targ_cmd_sci[1] = acs_RateTargCmd->targ_cmd_sci[1]; 
	targ_cmd_sci[2] = acs_RateTargCmd->targ_cmd_sci[2]; 
	targ_cmd_sci[3] = acs_RateTargCmd->targ_cmd_sci[3]; 
	rate_cmd_sci[0]   = acs_RateTargCmd->rate_cmd_sci[0]; 
	rate_cmd_sci[1]   = acs_RateTargCmd->rate_cmd_sci[1]; 
	rate_cmd_sci[2]   = acs_RateTargCmd->rate_cmd_sci[2]; 
#ifdef _ACS_DEBUG_
	printf("rate_cmd_sci: %f %f %f\n", rate_cmd_sci[0], rate_cmd_sci[1], rate_cmd_sci[2]); 
#endif
   return;
}
*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:    ACS_ProcessDagrBoomPkt                                           */
/*  Purpose: Copy the values from the Dagr boom pkt                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void ACS_ProcessDagrBoomPkt(CFE_SB_MsgPtr_t MessagePtr)
{
  dagr_acs_tlm_t *DagrPkt = (dagr_acs_tlm_t *) MessagePtr;

  DagrBoomPkt.boom_mag_x = DagrPkt->boom_mag_x;
  DagrBoomPkt.boom_mag_y = DagrPkt->boom_mag_y;
  DagrBoomPkt.boom_mag_z = DagrPkt->boom_mag_z;

}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:    ACS_FlagCheck                                                    */
/*  Purpose: ACS FlagCheck Command                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void ACS_FlagCheck(CFE_SB_MsgPtr_t MessagePtr)
{
  acs_flag_cmd_t* acsFlagCmd = (acs_flag_cmd_t *) MessagePtr;
#ifdef _ACS_DEBUG_
  printf("ACS --> FlagCheck command: %d, %d, %d, %d\n",
      acsFlagCmd->packet1 ,
      acsFlagCmd->packet2 ,
      acsFlagCmd->packet3 ,
      acsFlagCmd->packet4 );
#endif
           
  if (acsFlagCmd->packet1 == 1)
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Enable SunPt packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet1 = 1;
  }
  else 
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Disable SunPt packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet1 = 0;
  }

  if (acsFlagCmd->packet2 == 1)
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Enable SCI packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet2 = 1;
  }
  else 
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Disable SCI packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet2 = 0;
  }

  if (acsFlagCmd->packet3 == 1)
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Enable SensorData packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet3 = 1;
  }
  else 
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Disable SensorData packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet3 = 0;
  }

  if (acsFlagCmd->packet4 == 1)
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Enable AttDet packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet4 = 1;
  }
  else 
  {
   #ifdef _ACS_DEBUG_
     printf("ACS --> Disable AttDet packet\n"); 
   #endif
     ACS_DiagTlmFlags.packet4 = 0;
  }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*  Name:  ACS_ACSConfig                                                     */
/*  Purpose:                                                                 */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ACS_Run(CFE_SB_MsgPtr_t MessagePtr)
{
   uint8   sc_mode;

   sc_mode = MODE_GetSpacecraftMode();

   switch (sc_mode)
    {
        case MODE_CHARGING:
            rw_config = CFG_RW_SUNPT;
            mtc_config = CFG_MTC_MOMMNG;
		      akf_enable = 1;
           #ifdef _ACS_DEBUG_
            //printf("SC_MODE is CHARGING\n");
           #endif
            break;

        case MODE_SAFE:
            rw_config = CFG_RW_IDLE;
            mtc_config = CFG_MTC_IDLE;
		      akf_enable = 0;
           #ifdef _ACS_DEBUG_
            //printf("SC_MODE is SAFE\n");
           #endif
            break;

        case MODE_DAGR:
            rw_config = CFG_RW_SUNPT;
            mtc_config = CFG_MTC_LATMNG;
		      akf_enable = 1;
           #ifdef _ACS_DEBUG_
            //printf("SC_MODE is DAGR\n");
           #endif
            break;

        case MODE_INMS:
            rw_config = CFG_RW_LVLH;
            mtc_config = CFG_MTC_IDLE;
		      //akf_enable = 0;
		      akf_enable = 1;
           #ifdef _ACS_DEBUG_
            //printf("SC_MODE is INMS\n");
           #endif
            break;

        default:
            rw_config = CFG_RW_SUNPT;
            mtc_config = CFG_MTC_MOMMNG;
           #ifdef _ACS_DEBUG_
            printf("SC_MODE invalid: def to CHARGING\n");
           #endif
            break;
      } 

   acs_top(
           ACS_Constants.targ_cmd_sci,
           ACS_Constants.rate_cmd_sun,
           //rate_cmd_sun,
           ACS_Constants.rate_cmd_sci,
           //(Vector3f *)rate_cmd_sci, 
           akf_enable,
           rw_config,
           mtc_config,
           sc_mode,
           ACS_Constants.gain_att_sci,
           ACS_Constants.gain_int_sci,
           ACS_Constants.gain_rate_sci,
           ACS_Constants.gain_rate_sun,
           ACS_Constants.gain_att_sun);
           //(Vector3f *)gain_att_sci,
           //(Vector3f *)gain_int_sci,
           //(Vector3f *)gain_rate_sci,
           //(Vector3f *)gain_rate_sun,
           //(Vector3f *)gain_att_sun);


 //ACS_SptTlmPkt.rate_cmd_sun = rate_cmd_sun; 
 ACS_SptTlmPkt.rate_cmd_sun = ACS_Constants.rate_cmd_sun; 
 ACS_SptTlmPkt.targ_cmd_sci[0] = ACS_Constants.targ_cmd_sci[0]; 
 ACS_SptTlmPkt.targ_cmd_sci[1] = ACS_Constants.targ_cmd_sci[1]; 
 ACS_SptTlmPkt.targ_cmd_sci[2] = ACS_Constants.targ_cmd_sci[2]; 
 ACS_SptTlmPkt.targ_cmd_sci[3] = ACS_Constants.targ_cmd_sci[3]; 


}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_ReportHousekeeping                                             */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ReportHousekeeping(void)
{

    /*
    ** Send regular housekeeping
    */
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &ACS_HkTlmPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &ACS_HkTlmPkt);

   
    /*
    ** Check the flags and send each diagnostic packet if enabled
    */ 
    if(ACS_DiagTlmFlags.packet1 == 1)
    {
       ACS_ReportSptTlmPkt();
      #ifdef _ACS_DEBUG_
       //printf("ACS --> Sending Sunpt packet\n");
      #endif
    }

    if(ACS_DiagTlmFlags.packet2 == 1)
    {
       ACS_ReportSciTlmPkt();
      #ifdef _ACS_DEBUG_
       //printf("ACS --> Sending Sci packet\n");
      #endif
    }

    if(ACS_DiagTlmFlags.packet3 == 1)
    {
       ACS_ReportSdpTlmPkt();
      #ifdef _ACS_DEBUG_
       //printf("ACS --> Sending SensorData packet\n");
      #endif
    }

    if(ACS_DiagTlmFlags.packet4 == 1)
    {
       ACS_ReportAdTlmPkt();
      #ifdef _ACS_DEBUG_
       //printf("ACS --> Sending AttDet packet\n");
      #endif
    }

    return;

} /* End of ACS_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_ReportSptTlmPkt                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the diagnostics task. This function will gather the Apps      */
/*         telemetry, packetize it and send it to the diagnostics task via    */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ReportSptTlmPkt(void)
{

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &ACS_SptTlmPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &ACS_SptTlmPkt);

    return;

} /* End of ACS_ReportSptTlmPkt() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_ReportSciTlmPkt                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the diagnostics task. This function will gather the Apps      */
/*         telemetry, packetize it and send it to the diagnostics task via    */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ReportSciTlmPkt(void)
{

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &ACS_SciTlmPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &ACS_SciTlmPkt);

    return;

} /* End of ACS_ReportSciTlmPkt() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_ReportSdpTlmPkt                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the diagnostics task. This function will gather the Apps      */
/*         telemetry, packetize it and send it to the diagnostics task via    */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ReportSdpTlmPkt(void)
{

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &ACS_SdpTlmPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &ACS_SdpTlmPkt);

    return;

} /* End of ACS_ReportSdpTlmPkt() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_ReportAdTlmPkt                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the diagnostics task. This function will gather the Apps      */
/*         telemetry, packetize it and send it to the diagnostics task via    */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ReportAdTlmPkt(void)
{

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &ACS_AdTlmPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &ACS_AdTlmPkt);

    return;

} /* End of ACS_ReportAdTlmPkt() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_ReportMpTlmPkt                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the MPU task. This function will gather the Apps      */
/*         telemetry, packetize it and send it to the diagnostics task via    */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ReportMpuTlmPkt(void)
{

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &ACS_MpuTlmPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &ACS_MpuTlmPkt);

    return;

} /* End of ACS_ReportMpuTlmPkt() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACS_ResetCounters                                               */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACS_ResetCounters(void)
{
    /* Status of commands processed by the ACS App */
    ACS_HkTlmPkt.acs_command_count       = 0;
    ACS_HkTlmPkt.acs_command_error_count = 0;

    CFE_EVS_SendEvent(ACS_COMMANDRST_INF_EID, CFE_EVS_INFORMATION,
		"ACS: RESET command");
    return;

} /* End of ACS_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* ACS_VerifyCmdLength() -- Verify command packet length                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
boolean ACS_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{     
    boolean result = TRUE;

    uint16 ActualLength = CFE_SB_GetTotalMsgLength(msg);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID   = CFE_SB_GetMsgId(msg);
        uint16         CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent(ACS_LEN_ERR_EID, CFE_EVS_ERROR,
           "Invalid msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
              MessageID, CommandCode, ActualLength, ExpectedLength);
        result = FALSE;
        ACS_HkTlmPkt.acs_command_error_count++;
    }

    return(result);

} /* End of ACS_VerifyCmdLength() */

