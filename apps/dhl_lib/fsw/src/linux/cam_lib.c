/*************************************************************************
** File:
**   $Id: cam_lib.c  $
**
** Purpose: 
**   Shared library functions for the Serial Camera on Dellingr
**
**   $Log: cam_lib.c  $
** 
*************************************************************************/

/*************************************************************************
** Includes
*************************************************************************/
#include "dhl_lib.h"

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>

/*************************************************************************
** Macro Definitions
*************************************************************************/

#define CAMERA_DEBUG

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CAM Library Initialization Routine                             */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 CAM_LibInit(void)
{
    return OS_SUCCESS;
 
}/* End CAM_LibInit */

/************************************************************************/
/* Higher level camera functions */

/*
** Power On Camera
*/
void CAM_PowerOnCamera(void)
{
   printf("CAM: Camera ON\n");
}

/*
** Power Off Camera
*/
void CAM_PowerOffCamera(void)
{
   printf("CAM: Camera OFF\n");
}

/*
** Init Camera
*/
int CAM_InitCamera(void)
{

   return 0;
}

int CAM_ResetCamera(void)
{
   int status = 0;

   printf("CAM: reset camera\n");

   return status;
}

/*
** CAM_SetPictureSize:
** Status:  Works, sometimes has to be repeated to take effect
**
** Sizes
** <1> 0x22 : 160*120
** <2> 0x11 : 320*240
** <3> 0x00 : 640*480
** <4> 0x1D : 800*600
** <5> 0x1C : 1024*768
** <6> 0x1B : 1280*960
** <7> 0x21 : 1600*1200
*/
void CAM_SetPictureSize(uint8 Size)
{
   printf("CAM: Set picture size to %02X\n",Size);
}
 
/*
** CAM_GetPictureSize
*/
uint16 CAM_GetPictureSize(void)
{
   return(10000);
}

/*
** Send take picture command
**
*/
int CAM_SnapImage(void)
{
   printf("CAM: Snap Image\n");
   return 0;
}

/*
** Read data
*/
int CAM_GetCapturedImage(int addr)
{
   printf("CAM: Get Captured Image\n");
   return addr;
}
 
int CAM_EndCaptureImage(void)
{
    printf("CAM: End Captured Image\n");
    return 0;
}
 
/*
** Get Next Image Chunk
** This function will read the next section of the image file from the camera memory. 
** It will write the data to the open file descriptor OsalFileFd.
** 
** This function must be available, because the calling application can only process a portion of the data
** per cycle. 
*/
int32 CAM_GetNextImageChunk(int32 OsalFileFd, uint32 ImageOffset)
{
   int32 ByteCount;

   ByteCount = ImageOffset + 32;
   
   if ( ByteCount > 10000 )
   {
      return(CAM_END_OF_FILE);
   }
   else
   {
      return (ByteCount);
   } 

}


int CAM_GetImage(char *FileName)
{
   printf("CAM: Capturing image into file: %s\n",FileName);
   return CAM_EndCaptureImage();
}

/************************/
/*  End of File Comment */
/************************/
