/*********************************************************************
*
*       Includes
*
**********************************************************************
*/
#include "main.h"
#include "DIALOG.h"
#include "MenuLauncher.h" // For bitmaps and fonts resources

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*
 * STemWin Demonstration context
 */
#define STEMWIN_FIRMWARE_FILE_NAME      (const char*)"STEW_firmware.bin"
#define STEMWIN_FIRMWARE_VERSION        0xC6010000
#define STEMWIN_FIRMWARE_ADDRESS        0x08080000
#define STEMWIN_FIRMWARE_OFFSET         0x200
#define STEMWIN_RESOURCES_FILE_NAME     (const char*)"STEW_resources.bin"
#define STEMWIN_RESOURCES_VERSION       0xD6010000
#define STEMWIN_RESOURCES_ADDRESS       0x90400000
#define STEMWIN_RESOURCES_OFFSET        0x0

/*
 * TouchGFX Demonstration context
 */
#define TOUCHGFX_FIRMWARE_FILE_NAME     (const char*)"TGFX_firmware.bin"
#define TOUCHGFX_FIRMWARE_VERSION       0xC7010000
#define TOUCHGFX_FIRMWARE_ADDRESS       0x08100000
#define TOUCHGFX_FIRMWARE_OFFSET        0x200
#define TOUCHGFX_RESOURCES_FILE_NAME    (const char*)"TGFX_resources.bin"
#define TOUCHGFX_RESOURCES_VERSION      0xD7010000
#define TOUCHGFX_RESOURCES_ADDRESS      0x91800000
#define TOUCHGFX_RESOURCES_OFFSET       0x0

/*
 * EmbeddedWizard Demonstration context
 */
#define EWIZARD_FIRMWARE_FILE_NAME      (const char*)"EWIZ_firmware.bin"
#define EWIZARD_FIRMWARE_VERSION        0xC8010000
#define EWIZARD_FIRMWARE_ADDRESS        0x08180000
#define EWIZARD_FIRMWARE_OFFSET         0x200
#define EWIZARD_RESOURCES_FILE_NAME     (const char*)"EWIZ_resources.bin"
#define EWIZARD_RESOURCES_VERSION       0xD8010000
#define EWIZARD_RESOURCES_ADDRESS       0x92C00000
#define EWIZARD_RESOURCES_OFFSET        0x0

#define GUI_PROGBAR_LIGHTBLUE           0x01DDA949
#define GUI_PROGBAR_DARKBLUE            0x00421000

#define GUI_STCOLOR_LIGHTBLUE           0x00DCA939
#define GUI_STCOLOR_DARKBLUE            0x00522000

#define OCTOSPI_PROG_SECTOR_DURATION_MS 70     /* Assuming one secor erease then programming is taking 70 ms */

/*********************************************************************
*
*       Macros
*
**********************************************************************
*/

/*********************************************************************
*
*       Variables
*
**********************************************************************
*/
int FirstTime = 0;
uint8_t GUI_Initialized = 0;

/* Flag to indicate whether or not software is coming back from a software
   reset or not */
uint32_t software_reset_flag = 0;
char dialog_msg_buton_text[16];

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
enum
{
  ID_BUTTON_MODULE_CENTER = (GUI_ID_USER + 0x01),
  ID_BUTTON_MODULE_TOP,
  ID_BUTTON_MODULE_DOWN,
  ID_BUTTON_INFO,
  ID_BUTTON_BACK,
  ID_DEMO_BUTTON_OK,
  ID_DEMO_FRAMEWIN_DIALOG_BOX,
  ID_DEMO_FRAMEWIN_PROGRESS_BAR,
  ID_DEMO_TEXT_DIALOG_BOX_0,
  ID_DEMO_TEXT_DIALOG_BOX_1,
  ID_DEMO_TEXT_PROGRESS_BAR,
  ID_DEMO_PROGRESS_BAR,
};

typedef struct
{
  uint32_t     address;
  uint32_t     offset;
  uint32_t     version;
  const char * filename;
} DemoInfo_t;

typedef struct
{
  char     demo_name[32];

  DemoInfo_t firmware;
  DemoInfo_t resources;
} DemoContext_t;

typedef struct {
  const GUI_BITMAP    * pBitmap;
  const char          * pText;
  const char          * pExplanation;
  GUI_WRAPMODE          aWm;
  const DemoContext_t * pDemoContext;
} SUBDEMO_ITEM;

typedef struct {
  int xPos;
  int yPos;
  int Index;
} ITEM_INFO;

typedef struct
{
  char            text1[256];
  char            text2[256];
} DIALOGBOX_ITEM;

typedef struct {
  int                  Index;                   // Index # of parameters
  int                  DoAnimation;
  int                  Pos;
  int                  NumItems;
  int                  xSizeItem,   ySizeItem;
  int                  xSizeWindow, ySizeWindow;
  int                  rx,          ry;
  int                  mx,          my;
  int                  FinalMove;
  const SUBDEMO_ITEM * pBitmapItem;
  ITEM_INFO          * pItemInfo;
} PARA;

typedef struct {
  uint32_t  progress_bar_value;
  uint32_t  last_write_nb_bytes;
  uint32_t  last_write_duration;
  uint32_t  nb_chunks;
} PROGRAMMING_INFO;

/*********************************************************************
*
*       _aBitmapItem
*/
static const DemoContext_t SubDemo[] = {
  {
    "STemWin",
    { STEMWIN_FIRMWARE_ADDRESS  , STEMWIN_FIRMWARE_OFFSET  , STEMWIN_FIRMWARE_VERSION   , STEMWIN_FIRMWARE_FILE_NAME  },
    { STEMWIN_RESOURCES_ADDRESS , STEMWIN_RESOURCES_OFFSET , STEMWIN_RESOURCES_VERSION  , STEMWIN_RESOURCES_FILE_NAME }
  },

  {
    "EmbeddedWizard",
    { EWIZARD_FIRMWARE_ADDRESS  , EWIZARD_FIRMWARE_OFFSET  , EWIZARD_FIRMWARE_VERSION   , EWIZARD_FIRMWARE_FILE_NAME  },
    { EWIZARD_RESOURCES_ADDRESS , EWIZARD_RESOURCES_OFFSET , EWIZARD_RESOURCES_VERSION  , EWIZARD_RESOURCES_FILE_NAME }
  },

  {
    "TouchGFX",
    { TOUCHGFX_FIRMWARE_ADDRESS  , TOUCHGFX_FIRMWARE_OFFSET  , TOUCHGFX_FIRMWARE_VERSION   , TOUCHGFX_FIRMWARE_FILE_NAME  },
    { TOUCHGFX_RESOURCES_ADDRESS , TOUCHGFX_RESOURCES_OFFSET , TOUCHGFX_RESOURCES_VERSION  , TOUCHGFX_RESOURCES_FILE_NAME }
  },
};

/*********************************************************************
*
*       _aBitmapItem
*/
static const SUBDEMO_ITEM _aBitmapItem[] = {
  {&bmSTemWin         , "STemWin"        , "STemWin"         , GUI_WRAPMODE_NONE  , &SubDemo[DEMO_ID_0]  },
  {&bmEmbeddedWizard  , "EmbeddedWizard" , "Embedded Wizard" , GUI_WRAPMODE_WORD  , &SubDemo[DEMO_ID_1]  },
  {&bmTouchGFX        , "TouchGFX"       , "TouchGFX"        , GUI_WRAPMODE_NONE  , &SubDemo[DEMO_ID_2]  },
  {&bmSTemWin         , "STemWin"        , "STemWin "        , GUI_WRAPMODE_NONE  , &SubDemo[DEMO_ID_0]  },
  {&bmEmbeddedWizard  , "EmbeddedWizard" , "Embedded Wizard" , GUI_WRAPMODE_WORD  , &SubDemo[DEMO_ID_1]  },
  {&bmTouchGFX        , "TouchGFX"       , "TouchGFX"        , GUI_WRAPMODE_NONE  , &SubDemo[DEMO_ID_2]  },
};

/*********************************************************************
*
*       _cbDialog
*
* Purpose
*   Callback routine of the dialog
*/
 /* Generic Dialog Boc Create */
static const GUI_WIDGET_CREATE_INFO _aDialogMessageCreate[] = {
  { FRAMEWIN_CreateIndirect , "ERROR" , ID_DEMO_FRAMEWIN_DIALOG_BOX   ,   0 ,    0 , 390 , 390 ,   0 , 0x0 , 0 },
  { TEXT_CreateIndirect     , ""      , ID_DEMO_TEXT_DIALOG_BOX_0     ,  65 ,   60 , 260 , 130 ,   0 , 0x0 , 0 },
  { TEXT_CreateIndirect     , ""      , ID_DEMO_TEXT_DIALOG_BOX_1     ,  65 ,  140 , 260 ,  50 ,   0 , 0x0 , 0 },
  { BUTTON_CreateIndirect   , ""      , ID_DEMO_BUTTON_OK             ,  75 ,  200 , 240 , 120 ,   0 , 0x0 , 0 },
};

static const GUI_WIDGET_CREATE_INFO _aProgressBarCreate[] = {
  { FRAMEWIN_CreateIndirect , ""      , ID_DEMO_FRAMEWIN_PROGRESS_BAR ,  15 ,   85 , 320 ,  65 ,   0 , 0x0 , 0 },
  { TEXT_CreateIndirect     , ""      , ID_DEMO_TEXT_PROGRESS_BAR     ,   0 ,    1 , 320 ,  25 ,   TEXT_CF_HCENTER , 0x0 , 0 },
  { PROGBAR_CreateIndirect  , ""      , ID_DEMO_PROGRESS_BAR          ,   2 ,   20 , 306 ,  34 ,   0 , 0x0 , 0 },
};

/**
  * @brief  Paints ok message button
  * @param  hObj: button handle
  * @retval None
  */
static void _OnPaint_okMessage(BUTTON_Handle hObj) {
  GUI_RECT                Rect;

  //
  // Receive the area of the BUTTON widget
  //
  WM_GetClientRectEx(hObj, &Rect);

  if ((WIDGET_GetState(hObj) & BUTTON_STATE_PRESSED))
  {
    GUI_SetColor(GUI_LIGHTGRAY);
  }
  else
  {
    GUI_SetColor(GUI_WHITE);
  }

  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_SetFont(&GUI_Font32B_ASCII);
  GUI_DispStringInRect(dialog_msg_buton_text, &Rect, (GUI_TA_VCENTER | GUI_TA_HCENTER));
}

/**
  * @brief  callback for ok message button
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbButton_okMessage(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      _OnPaint_okMessage(pMsg->hWin);
      break;
    default:
      /* The original callback */
      BUTTON_Callback(pMsg);
      break;
  }
}

/**
* @brief  Paints yes message button
* @param  hObj: button handle
* @retval None
*/
static void _OnPaint_yesMessage(BUTTON_Handle hObj)
{
  GUI_RECT                Rect;

  //
  // Receive the area of the BUTTON widget
  //
  WM_GetClientRectEx(hObj, &Rect);

  if ((WIDGET_GetState(hObj) & BUTTON_STATE_PRESSED))
  {
    GUI_SetColor(GUI_LIGHTGRAY);
  }
  else
  {
    GUI_SetColor(GUI_WHITE);
  }

  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_SetFont(&GUI_Font32B_ASCII);
  GUI_DispStringInRect("YES", &Rect, (GUI_TA_VCENTER | GUI_TA_HCENTER));
}

/**
* @brief  callback for yes message button
* @param  pMsg: pointer to data structure of type WM_MESSAGE
* @retval None
*/
static void _cbButton_yesMessage(WM_MESSAGE * pMsg)
{
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      _OnPaint_yesMessage(pMsg->hWin);
      break;
    default:
      /* The original callback */
      BUTTON_Callback(pMsg);
      break;
  }
}

/**
* @brief  Paints no message button
* @param  hObj: button handle
* @retval None
*/
static void _OnPaint_noMessage(BUTTON_Handle hObj)
{
  GUI_RECT                Rect;

  //
  // Receive the area of the BUTTON widget
  //
  WM_GetClientRectEx(hObj, &Rect);

  if ((WIDGET_GetState(hObj) & BUTTON_STATE_PRESSED))
  {
    GUI_SetColor(GUI_LIGHTGRAY);
  }
  else
  {
    GUI_SetColor(GUI_WHITE);
  }

  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_SetFont(&GUI_Font32B_ASCII);
  GUI_DispStringInRect("NO", &Rect, (GUI_TA_VCENTER | GUI_TA_HCENTER));
}

/**
* @brief  callback for no message button
* @param  pMsg: pointer to data structure of type WM_MESSAGE
* @retval None
*/
static void _cbButton_noMessage(WM_MESSAGE * pMsg)
{
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      _OnPaint_noMessage(pMsg->hWin);
      break;
    default:
      /* The original callback */
      BUTTON_Callback(pMsg);
      break;
  }
}

/**
* @brief  callback for no progress bar frame
* @param  pMsg: pointer to data structure of type WM_MESSAGE
* @retval None
*/
static void _cbProgrbar_frame(WM_MESSAGE * pMsg)
{
}

/**
  * @brief  Callback routine of Progress Bar
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbProgressBar(WM_MESSAGE * pMsg)
{
  WM_HWIN hItem;
  switch (pMsg->MsgId)
  {
    case WM_INIT_DIALOG:
    {
      WM_SetCallback(pMsg->hWin, _cbProgrbar_frame);
      FRAMEWIN_SetFont(pMsg->hWin, &GUI_Font6x8_ASCII);
      FRAMEWIN_SetTextColor(pMsg->hWin, GUI_DARKRED);
      FRAMEWIN_SetTextAlign(pMsg->hWin, GUI_TA_LEFT);
      FRAMEWIN_SetClientColor(pMsg->hWin, GUI_MAKE_COLOR(GUI_PROGBAR_DARKBLUE));
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 2);
      FRAMEWIN_SetTitleVis(pMsg->hWin, 1);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_DEMO_PROGRESS_BAR);
      PROGBAR_SetBarColor(hItem, 0, GUI_GREEN);
      PROGBAR_SetBarColor(hItem, 1, GUI_RED);
      PROGBAR_SetFont(hItem, &GUI_Font16B_ASCII);
      PROGBAR_SetTextColor(hItem, 0, GUI_MAKE_COLOR(GUI_PROGBAR_DARKBLUE));
      PROGBAR_SetTextColor(hItem, 1, GUI_MAKE_COLOR(GUI_PROGBAR_DARKBLUE));

      hItem = WM_GetDialogItem(pMsg->hWin, ID_DEMO_TEXT_PROGRESS_BAR);
      TEXT_SetFont(hItem, &GUI_Font16B_ASCII);
      TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(GUI_PROGBAR_LIGHTBLUE));
      TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
      TEXT_SetWrapMode(hItem, GUI_WRAPMODE_WORD);
    }
    break;
    default:
      break;
  }
}

/*********************************************************************
*
*       _DlgFrameOwnerDraw
*/
static int _DlgFrameOwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
  //
  // Process messages
  //
  switch (pDrawItemInfo->Cmd)
  {
    case WIDGET_ITEM_DRAW_SEP:
    case WIDGET_ITEM_DRAW_FRAME:
      break;

    case WIDGET_ITEM_DRAW_BACKGROUND:
      GUI_DrawBitmap(&bmquestion, 0, 0);
      break;
    default:
      //
      // Anything not handled here will be handled by the default skinning routine.
      //
      return FRAMEWIN_DrawSkinFlex(pDrawItemInfo);
  }
  return 0;
}

/**
  * @brief  Callback routine of Info dialog
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbDialogMessage(WM_MESSAGE * pMsg)
{
  int     NCode;
  int     Id;
  WM_HWIN hItem;
  DIALOGBOX_ITEM * pPara;

  switch (pMsg->MsgId)
  {
    case WM_INIT_DIALOG:
    {
      hItem = WM_GetDialogItem(pMsg->hWin, ID_DEMO_BUTTON_OK);
      WM_SetStayOnTop(hItem, 1);
      WM_SetCallback(hItem, _cbButton_okMessage);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_DEMO_TEXT_DIALOG_BOX_0);
      TEXT_SetFont(hItem, &GUI_Font24B_ASCII);
      TEXT_SetTextColor(hItem, GUI_WHITE);
      TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
      TEXT_SetWrapMode(hItem, GUI_WRAPMODE_WORD);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_DEMO_TEXT_DIALOG_BOX_1);
      TEXT_SetFont(hItem, &GUI_FontComic18B_ASCII);
      TEXT_SetTextColor(hItem, GUI_WHITE);
      TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_BOTTOM);
      TEXT_SetWrapMode(hItem, GUI_WRAPMODE_WORD);
    }
    break;

    case WM_PAINT:
    {
      hItem = WM_GetDialogItem(pMsg->hWin, ID_DEMO_TEXT_DIALOG_BOX_0);
      WM_GetUserData(hItem, &pPara, sizeof(pPara));
      TEXT_SetText(hItem, pPara->text1);
      if(pPara->text2[0] == '\0') // empty text
      {
        // Vertical Center Text1
        TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
      }

      hItem = WM_GetDialogItem(pMsg->hWin, ID_DEMO_TEXT_DIALOG_BOX_1);
      TEXT_SetText(hItem, pPara->text2);
    }
    break;

    case WM_NOTIFY_PARENT:
    {
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch(Id)
      {
        case ID_DEMO_BUTTON_OK: /* Notifications sent by 'OK' */
        {
          switch(NCode)
          {
            case WM_NOTIFICATION_RELEASED:
			  FirstTime = 0;
              GUI_EndDialog(pMsg->hWin, 0);
              break;
          }
        }
        break;
      }
    }
    break;

    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

/**
* @brief callback Message Box
* @param  pMsg : pointer to data structure
* @retval None
*/
static void _cbMessageBox(WM_MESSAGE* pMsg)
{
  WM_HWIN hWin;
  int Id;

  hWin = pMsg->hWin;
  switch (pMsg->MsgId)
  {
    case WM_NOTIFY_PARENT:
      if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
      {
        Id = WM_GetId(pMsg->hWinSrc);
        if (Id == GUI_ID_OK)
        {
          GUI_EndDialog(hWin, 1);
        }
        else if (Id == GUI_ID_CANCEL)
        {
		  FirstTime = 0;
          GUI_EndDialog(hWin, 0);
        }
      }
      break;

    default:
      WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _FrameOwnerDraw
*/
static int _FrameOwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
  //
  // Process messages
  //
  switch (pDrawItemInfo->Cmd)
  {
    case WIDGET_ITEM_DRAW_SEP:
    case WIDGET_ITEM_DRAW_FRAME:
      break;

    case WIDGET_ITEM_DRAW_BACKGROUND:
      GUI_DrawBitmap(&bmquestion, 0, 0);
      GUI_DrawBitmap(&bmquestion_sep, 192, 254);
      break;

    default:
      //
      // Anything not handled here will be handled by the default skinning routine.
      //
      return FRAMEWIN_DrawSkinFlex(pDrawItemInfo);
  }
  return 0;
}

/**
* @brief  Show Message Box
* @param  pTitle: pointer to the title
* @param  pText: pointer to the text
* @param  YesNo player response
* @retval int
*/
/* Generic Dialog Boc Create */
static int _ShowMessageBox(WM_HWIN hWin, const char* pTitle, const char* pText)
{
  WM_HWIN hFrame, hClient, hBut, htext;
  int r = 0;

  //GUI_EnableAlpha(1);

  /* Create frame win */
  hFrame = FRAMEWIN_CreateEx(0, 0, 390, 390, hWin, WM_CF_SHOW | WM_CF_FGND | WM_CF_HASTRANS, FRAMEWIN_CF_MOVEABLE, 0, pTitle, &_cbMessageBox);
  WM_SetHasTrans(hFrame);
  FRAMEWIN_SetFont(hFrame, &GUI_Font16B_ASCII);
  FRAMEWIN_SetTitleHeight(hFrame, 50);
  FRAMEWIN_SetTextAlign(hFrame, GUI_TA_HCENTER|GUI_TA_BOTTOM);
  FRAMEWIN_SetTextColor(hFrame, GUI_WHITE);
  FRAMEWIN_SetBarColor(hFrame, 0, GUI_TRANSPARENT);
  FRAMEWIN_SetBarColor(hFrame, 1, GUI_TRANSPARENT);
  WM_SetHasTrans(WM_GetClientWindow(hFrame));
  FRAMEWIN_SetClientColor(hFrame, GUI_INVALID_COLOR);
  FRAMEWIN_SetSkin(hFrame, _FrameOwnerDraw);

  /* Create dialog items */
  hClient = WM_GetClientWindow(hFrame);
  htext = TEXT_CreateEx(65, 20, 260, 170, hClient, WM_CF_SHOW, GUI_TA_HCENTER | GUI_TA_TOP, 0, pText);
  TEXT_SetFont(htext, &GUI_Font24B_1/*GUI_Font16B_ASCII*/);
  TEXT_SetTextColor(htext, GUI_WHITE);
  TEXT_SetWrapMode(htext, GUI_WRAPMODE_WORD);

  hBut = BUTTON_CreateEx( 45, 200, 140, 120, hClient, WM_CF_SHOW | WM_CF_STAYONTOP, 0, GUI_ID_OK);
  WM_SetCallback(hBut, _cbButton_yesMessage);

  hBut = BUTTON_CreateEx(195, 200, 140, 120, hClient, WM_CF_SHOW | WM_CF_STAYONTOP, 0, GUI_ID_CANCEL);
  WM_SetCallback(hBut, _cbButton_noMessage);

  WM_MakeModal(hFrame);

  LCD_WaitForDisplayCompletion();
  GUI_Exec1();
  LCD_RefreshRequestedByApplicatyion();
  LCD_WaitForDisplayCompletion();

  r = GUI_ExecCreatedDialog(hFrame);

  //GUI_EnableAlpha(0);
  return r;
}

/**
* @brief  Show Message Box
* @param  hWin: pointer to the parent window
* @param  pMsgItem: pointer to the message item data
* @param  text_id: text ID used to get then set the Dialog Box user data
* @retval None
*/
static void _ShowDialogBox(WM_HWIN hWin, const DIALOGBOX_ITEM * pMsgItem, uint32_t text_id, const char* pTitle)
{
  WM_HWIN    hItem, hFrame, hText;

  //GUI_EnableAlpha(1);

  /* Create and display the Dialog Box */
  hItem = GUI_CreateDialogBox(_aDialogMessageCreate,
                              GUI_COUNTOF(_aDialogMessageCreate),
                              _cbDialogMessage, // No callback - no initial WM_INIT_DIALOG event being treated.
                              hWin,
                              0, 0);

  WM_SetHasTrans(hItem); // Set transparency

  /* Setup the Dialog box frame */
  hFrame = WM_GetDialogItem(hWin, ID_DEMO_FRAMEWIN_DIALOG_BOX);
  /* Set user data content only for the Text1 */
  FRAMEWIN_SetFont(hFrame, &GUI_Font16B_ASCII);
  FRAMEWIN_SetTitleHeight(hFrame, 50);
  FRAMEWIN_SetTextAlign(hFrame, GUI_TA_HCENTER | GUI_TA_BOTTOM);
  FRAMEWIN_SetTextColor(hFrame, GUI_WHITE);
  FRAMEWIN_SetBarColor(hFrame, 0, GUI_TRANSPARENT);
  FRAMEWIN_SetBarColor(hFrame, 1, GUI_TRANSPARENT);
  WM_SetHasTrans(WM_GetClientWindow(hFrame));
  FRAMEWIN_SetClientColor(hFrame, GUI_INVALID_COLOR);
  FRAMEWIN_SetText(hFrame, pTitle);
  FRAMEWIN_SetSkin(hFrame, _DlgFrameOwnerDraw);

  /* Set user data content only for the Text1 */
  hText = WM_GetDialogItem(hWin, ID_DEMO_TEXT_DIALOG_BOX_0);
  WM_SetUserData(hText, &pMsgItem, sizeof(pMsgItem));

  /* Show the Dialog Box */
  WM_MakeModal(hItem);

  LCD_WaitForDisplayCompletion();
  GUI_Exec1();
  LCD_RefreshRequestedByApplicatyion();
  LCD_WaitForDisplayCompletion();

  GUI_ExecCreatedDialog(hItem);
  WM_DeleteWindow(hItem);

  //GUI_EnableAlpha(0);
}

static void _cbDisableWindow(WM_HWIN hWin, void *p)
{
  int disable = *(int *)p;
  if(disable)
  {
    WM_DisableWindow(hWin);
  }
  else
  {
    WM_EnableWindow(hWin);
  }
}

#ifndef GUI_SIMULATOR
void _cbFlashProgram( BSP_FlashProgramInfo_t * pInfo)
{
  PROGBAR_Handle hProg = (PROGBAR_Handle)pInfo->user_data;
  if(hProg)
  {
    PROGBAR_SetValue(hProg, pInfo->progress_percent);
    LCD_WaitForDisplayCompletion();
    WM_Exec();
    LCD_RefreshRequestedByApplicatyion();
    LCD_WaitForDisplayCompletion();
  }
}
#endif /* !GUI_SIMULATOR */

/**
  * @brief  SUBDEMO_Start
  * @param  None
  * @retval None
  */
static void SUBDEMO_Start(WM_HWIN hWin, const DemoContext_t *pContext)
{
#ifdef GUI_SIMULATOR
  WM_HWIN hItem;
  static DIALOGBOX_ITEM       MsgItem;
  static PROGRAMMING_INFO     ProgrammingInfo;
  DIALOGBOX_ITEM            * pMsgItem;
  PROGRAMMING_INFO        * pProgrammingInfo;

  PROGBAR_Handle hProg;
  TEXT_Handle hText;
  int Value = 0;
  char acText[256] = { 0 };

  static int test_id = 0;

  //
  // Initialize parameter structure for Dialog Box items to be shown in case of error
  //
  pMsgItem = &MsgItem;
  pMsgItem->text1[0] = '\0';
  pMsgItem->text2[0] = '\0';

  /* Default OK button text is "BACK" */
  snprintf(dialog_msg_buton_text, sizeof(dialog_msg_buton_text), "BACK");

  pProgrammingInfo = &ProgrammingInfo;

  if (test_id == 8)
  {
    test_id = 0;
  }

  if (test_id == 0)
  {
    /* Calculate estimated programming duration */
    uint32_t file_size = 20 * 1024 * 1024; /* 20 MBytes --> 320 * 64 Kbytes sectors */
    uint32_t duration_ms = (file_size/(1024 * 64)) *  OCTOSPI_PROG_SECTOR_DURATION_MS; /* TODO : use appropriate value */
    char message[256];

    snprintf(message, sizeof(message), "%s demo resources download\n\n* Expected duration *\n- %d minutes -\n\nCarry on?", pContext->demo_name, (duration_ms/3600));
    if(!_ShowMessageBox(WM_HBKWIN, "QUESTION", message))
    {
      return;
    }
  }

  if (test_id == 0)
  {
    /* Display error message: No SD Card inserted! */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "No SD Card inserted!");
    snprintf(pMsgItem->text2, sizeof(pMsgItem->text2), "Please insert an SD Card which includes valid binary files.");
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

    test_id++;
  }
  else if (test_id == 1)
  {
    /* Display error message: Invalid Firmware binary file */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Invalid Firmware binary file\nFor %s demo", pContext->demo_name);
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

    test_id++;
  }
  else if (test_id == 2)
  {
    /* Display error message: Invalid Demo Resources file */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Invalid Resources binary file\nFor %s demo", pContext->demo_name);
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

    test_id++;
  }
  else if (test_id == 3)
  {
    /* Display error message: No Firmware binary file */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "No Firmware binary file\nFor %s demo", pContext->demo_name);
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

    test_id++;
  }
  else if (test_id == 4)
  {
    /* Display error message: No Resources binary file */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "No Resources binary file\nFor %s demo", pContext->demo_name);
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

    test_id++;
  }
  else if (test_id == 5)
  {
    /* Simulate Firmware binary file programming */
    snprintf(acText, sizeof(acText), "%s Firmware Programming...", pContext->demo_name);

    /* Create and display the Dialog Box */
    hItem = GUI_CreateDialogBox(_aProgressBarCreate,
            GUI_COUNTOF(_aProgressBarCreate),
            _cbProgressBar, // Default callback.
            hWin,
            20, 80);

    /* Set Progress Bar Min - Max values */
    hProg = WM_GetDialogItem(hWin, ID_DEMO_PROGRESS_BAR);
    WM_SetUserData(hProg, &pProgrammingInfo, sizeof(pProgrammingInfo));
    PROGBAR_SetMinMax(hProg, 0, 8192);
    PROGBAR_SetFont(hProg, &GUI_Font16B_ASCII);
    PROGBAR_SetValue(hProg, 0);

    /* Set the text data */
    hText = WM_GetDialogItem(hWin, ID_DEMO_TEXT_PROGRESS_BAR);
    TEXT_SetText(hText, acText);

    WM_MakeModal(hItem);

    Value = 0;
    while (1)
    {
      int val = PROGBAR_GetValue(hProg);
      if (val == 8192)
              break;
      Value++;
      PROGBAR_SetValue(hProg, Value);
      WM_Exec();
    }

    WM_DeleteWindow(hItem);

    /* Display info message: Flashing completed! */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Firmware successfully programmed!");
    snprintf(pMsgItem->text2, sizeof(pMsgItem->text2), "\nPress Reset button to launch the %s demonstration", pContext->demo_name);
    snprintf(dialog_msg_buton_text, sizeof(dialog_msg_buton_text), "RESET");
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "INFO");

    test_id++;
  }
  else if (test_id == 6)
  {
    /* Simulate Resources binary file programming */
    snprintf(acText, sizeof(acText), "%s Resources Programming...", pContext->demo_name);

    /* Create and display the Dialog Box */
    hItem = GUI_CreateDialogBox(_aProgressBarCreate,
            GUI_COUNTOF(_aProgressBarCreate),
            _cbProgressBar, // Default callback.
            hWin,
            20, 80);

    /* Set Progress Bar Min - Max values */
    hProg = WM_GetDialogItem(hWin, ID_DEMO_PROGRESS_BAR);
    PROGBAR_SetMinMax(hProg, 0, (2 * 8192));
    PROGBAR_SetFont(hProg, &GUI_Font16B_ASCII);
    PROGBAR_SetValue(hProg, 0);

    /* Set the text data */
    hText = WM_GetDialogItem(hWin, ID_DEMO_TEXT_PROGRESS_BAR);
    TEXT_SetText(hText, acText);

    WM_MakeModal(hItem);

    WM_MakeModal(hItem);
    LCD_WaitForDisplayCompletion();
    GUI_Exec1();
    LCD_RefreshRequestedByApplicatyion();
    LCD_WaitForDisplayCompletion();

    GUI_Initialized = 0; /* No more DRAW following this */

    Value = 0;
    while (1)
    {
      int val = PROGBAR_GetValue(hProg);
      if (val == (2 * 8192))
              break;
      Value++;
      PROGBAR_SetValue(hProg, Value);
      WM_Exec();
    }

    GUI_Initialized = 1; /* Now allow DRAW following this */

    WM_DeleteWindow(hItem);

    /* Display info message: Flashing completed! */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Resources successfully programmed!");
    snprintf(pMsgItem->text2, sizeof(pMsgItem->text2), "\nPress Reset button to launch the %s demonstration", pContext->demo_name);
    snprintf(dialog_msg_buton_text, sizeof(dialog_msg_buton_text), "RESET");
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "INFO");

    test_id++;
  }
  else if (test_id == 7)
  {
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Firmware and Resources successfully programmed!");
    snprintf(pMsgItem->text2, sizeof(pMsgItem->text2), "\nPress Reset button to launch the %s demonstration", pContext->demo_name);
    snprintf(dialog_msg_buton_text, sizeof(dialog_msg_buton_text), "RESET");
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "INFO");

    test_id++;
  }
#endif /* GUI_SIMULATOR */

#ifndef GUI_SIMULATOR
  WM_HWIN hItem;
  static DIALOGBOX_ITEM       MsgItem;
  DIALOGBOX_ITEM            * pMsgItem;
  Demo_Header_t * pOspiDemoHeader = (Demo_Header_t *)(pContext->resources.address + pContext->resources.offset);
  Demo_Header_t * pFirmDemoHeader = (Demo_Header_t *)(pContext->firmware.address + pContext->firmware.offset);
  Demo_Header_t   SdDemoHeader    = (Demo_Header_t  ){0};
  FRESULT result = FR_NOT_READY;
  uint32_t numOfReadBytes;
  int card_detected = BSP_SD_IsDetected();

  FIL DEMO_firmware_file = { 0 };
  FIL DEMO_resources_file = { 0 };

  PROGBAR_Handle hProg;
  TEXT_Handle hText;
  char acText[256] = {0};
  
  int IntFlashProgrammingDone = 0, ExtFlashProgrammingDone = 0;

  //
  // Initialize parameter structure for Dialog Box items to be shown in case of error
  //
  pMsgItem = &MsgItem;
  pMsgItem->text1[0] = '\0';
  pMsgItem->text2[0] = '\0';

  /* Default OK button text is "BACK" */
  snprintf(dialog_msg_buton_text, sizeof(dialog_msg_buton_text), "BACK");
  
  
  if ( (pFirmDemoHeader->demo_id == pContext->firmware.version) && (pOspiDemoHeader->demo_id == pContext->resources.version) )
  {
    result = FR_OK;
  }
  else
  if(card_detected)
  {
    /* Check if Flash binary is not the same as requested */
    if (pFirmDemoHeader->demo_id == pContext->firmware.version)
    {
      result = FR_OK;
    }
    else
    {
      /* Open Flash file */
      result = f_open(&DEMO_firmware_file, pContext->firmware.filename, FA_READ);
      if(result == FR_OK)
      {
        /* Read Flash Header */
        result = f_lseek(&DEMO_firmware_file, pContext->firmware.offset);
        if (result == FR_OK)
        {
          result = f_read(&DEMO_firmware_file, &SdDemoHeader, sizeof(Demo_Header_t), (void *)&numOfReadBytes);
          if(result == FR_OK)
          {
            /* Check if the demo located in SD Card is matching the required demo */
            if (SdDemoHeader.demo_id != pContext->firmware.version)
            {
              result = FR_INVALID_OBJECT;
            }
          }
        }

        if(result != FR_OK)
        {
          /* Display error message: Invalid Demo binary files */
          snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Invalid Firmware binary file\nFor %s demo", pContext->demo_name);
          _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

          /* Close flash file as no more needed */
          f_close(&DEMO_firmware_file);
          f_size(&DEMO_firmware_file) = 0;
        }
      }
      else
      {
        /* Display error message: No Demo binary files */
        snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "No Firmware binary file\nFor %s demo", pContext->demo_name);
        _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");
      }
    }

    /* Check if the OctoSPI binary is not the same as requested */
    if ( (result == FR_OK) && (pOspiDemoHeader->demo_id != pContext->resources.version) )
    {
      /* Open the OctoSPI file */
      result = f_open(&DEMO_resources_file, pContext->resources.filename, FA_READ);
      if(result == FR_OK)
      {
        result = f_lseek(&DEMO_resources_file, pContext->resources.offset);
        if (result == FR_OK)
        {
          result = f_read(&DEMO_resources_file, &SdDemoHeader, sizeof(Demo_Header_t), (void *)&numOfReadBytes);
          if(result == FR_OK)
          {
            /* Check if the demo resources located in SD Card is matching the required demo */
            if (SdDemoHeader.demo_id != pContext->resources.version)
            {
              result = FR_INVALID_OBJECT;
            }
          }
        }

        if(result != FR_OK)
        {
          /* Display error message: Invalid Demo Resources file */
          snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Invalid Resources binary file\nFor %s demo", pContext->demo_name);
          _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

          /* Close resources file as no more needed */
          f_close(&DEMO_resources_file);
          f_size(&DEMO_resources_file) = 0;

          /* Close also the firmwaye file to skip the update */
          f_close(&DEMO_firmware_file);
          f_size(&DEMO_firmware_file) = 0;
        }

        /* Notify the user that the expected duration */
        if (result == FR_OK)
        {
          /* Calculate estimated programming duration */
          uint32_t file_size = f_size(&DEMO_resources_file);
          uint32_t duration_ms = (file_size / (1024 * 64)) *  OCTOSPI_PROG_SECTOR_DURATION_MS; /* TODO : use appropriate value */
          char message[256];

          snprintf(message, sizeof(message), "%s demo resources download\n\n* Expected duration *\n- %d minutes -\n\nCarry on?", pContext->demo_name, (duration_ms / 3600));
          if(!_ShowMessageBox(WM_HBKWIN, "QUESTION", message))
          {
            /* Close flash file before returning */
            f_close(&DEMO_firmware_file);
            f_size(&DEMO_firmware_file) = 0;

            /* Close resources file before returning */
            f_close(&DEMO_resources_file);
            f_size(&DEMO_resources_file) = 0;
            
            return; /* Exist immediatly */
          }
        }
      }
      else
      {
        /* Display error message: Invalid Demo binary files */
        snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "No Resources binary file\nFor %s demo", pContext->demo_name);
        _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");

        /* Don't update the internal flash. Close flash file before going on */
        f_close(&DEMO_firmware_file);
        f_size(&DEMO_firmware_file) = 0;
      }
    }

    /*
     * Now Flash binaries
     */
    if((result == FR_OK) && (f_size(&DEMO_firmware_file) > 0))
    {
      snprintf(acText, sizeof(acText), "%s Firmware Programming...", pContext->demo_name);

      /* Create and display the Dialog Box */
      hItem = GUI_CreateDialogBox(_aProgressBarCreate,
                                  GUI_COUNTOF(_aProgressBarCreate),
                                  _cbProgressBar, // Default callback.
                                  hWin,
                                  20, 80);

      /* Set Progress Bar Min - Max values */
      hProg = WM_GetDialogItem(hWin, ID_DEMO_PROGRESS_BAR);
      PROGBAR_SetMinMax(hProg, 0, 100);
      PROGBAR_SetFont(hProg, &GUI_Font16B_ASCII);
      PROGBAR_SetValue(hProg, 0);

      /* Set the text data */
      hText = WM_GetDialogItem(hWin, ID_DEMO_TEXT_PROGRESS_BAR);
      TEXT_SetText(hText, acText);

      WM_MakeModal(hItem);

      LCD_WaitForDisplayCompletion();
      GUI_Exec1();
      LCD_RefreshRequestedByApplicatyion();
      LCD_WaitForDisplayCompletion();

      if (BSP_FlashProgram(hProg, &DEMO_firmware_file, pContext->firmware.address, _cbFlashProgram) < 0)
      {
        /* TODO : display message informing about "Error during Firmware binary Programming" */
        result = FR_DISK_ERR;
      }

      WM_DeleteWindow(hItem);

      f_close(&DEMO_firmware_file);

      IntFlashProgrammingDone = 1;
    }

    if((result == FR_OK) && (f_size(&DEMO_resources_file) > 0))
    {
      GUI_Delay(60);

      snprintf(acText, sizeof(acText), "%s Resources Programming...", pContext->demo_name);

      /* Create and display the Dialog Box */
      hItem = GUI_CreateDialogBox(_aProgressBarCreate,
                                  GUI_COUNTOF(_aProgressBarCreate),
                                  _cbProgressBar, // Default callback.
                                  hWin,
                                  20, 80);

      /* Set Progress Bar Min - Max values */
      hProg = WM_GetDialogItem(hWin, ID_DEMO_PROGRESS_BAR);
      PROGBAR_SetMinMax(hProg, 0, 100);
      PROGBAR_SetFont(hProg, &GUI_Font16B_ASCII);
      PROGBAR_SetValue(hProg, 0);

      /* Set the text data */
      hText = WM_GetDialogItem(hWin, ID_DEMO_TEXT_PROGRESS_BAR);
      TEXT_SetText(hText, acText);

      WM_MakeModal(hItem);
      LCD_WaitForDisplayCompletion();
      GUI_Exec1();
      LCD_RefreshRequestedByApplicatyion();
      LCD_WaitForDisplayCompletion();

      GUI_Initialized = 0; /* No more DRAW following this */

      if (BSP_ResourcesCopy(hProg, &DEMO_resources_file, pContext->resources.address, _cbFlashProgram) < 0)
      {
        /* TODO : display message informing about "Error during Resources binary Programming" */
        result = FR_DISK_ERR;
      }
      GUI_Initialized = 1; /* Allow DRAW following this */

      WM_DeleteWindow(hItem);

      f_close(&DEMO_resources_file);
      f_size(&DEMO_resources_file) = 0;

      ExtFlashProgrammingDone = 1;
    }
  }
  else
  {
    /* Display error message: No SD Card inserted! */
    snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "No SD Card inserted!");
    snprintf(pMsgItem->text2, sizeof(pMsgItem->text2), "Please insert an SD Card which includes valid binary files.");
    _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "ERROR");
  }
    
  /* Jump to new Sub Demo if no errors */
  if(result == FR_OK)
  {
    if((IntFlashProgrammingDone ==1) || (ExtFlashProgrammingDone == 1))
    {
      /* Display info message: Flashing completed! */
      if((IntFlashProgrammingDone ==1) && (ExtFlashProgrammingDone == 1))
      {
        snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Firmware and Resources successfully programmed!");
      }
      else if((IntFlashProgrammingDone ==1) && (ExtFlashProgrammingDone == 0))
      {
        snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Firmware successfully programmed!");
      }
      else
      {
        snprintf(pMsgItem->text1, sizeof(pMsgItem->text1), "Resources successfully programmed!");
      }
      snprintf(pMsgItem->text2, sizeof(pMsgItem->text2), "\nPress Reset button to launch the %s demonstration", pContext->demo_name);
      snprintf(dialog_msg_buton_text, sizeof(dialog_msg_buton_text), "RESET");
      _ShowDialogBox(WM_HBKWIN, pMsgItem, GUI_ID_TEXT0, "INFO");
    }
    BSP_JumpToSubDemo(pContext->firmware.address);
  }
#endif /* !GUI_SIMULATOR */
}

/*********************************************************************
*
*       _cbInfo
*
*  Function description:
*    Callback routine of information screen
*/
static void _cbInfo(WM_MESSAGE * pMsg)
{
  WM_HWIN     hWin;
  int Id, NCode;

  hWin = pMsg->hWin;
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      GUI_DrawBitmap(&bminformation, 0, 0);
      break;

    case WM_NOTIFY_PARENT:
    {
      Id = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch(Id)
      {
        // Only Back Button being attached the Info window
        case ID_BUTTON_BACK:
        {
          switch(NCode)
          {
            case WM_NOTIFICATION_CLICKED:
              break;

            case WM_NOTIFICATION_RELEASED:
            {
              //
              // Delete window and create button
              //
              FirstTime = 0;
              WM_DeleteWindow(hWin);
            }
            break;
          }
        }
        break;
      }
    }
    break;

    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

/**
  * @brief  callback for info button
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbButton(WM_MESSAGE * pMsg)
{
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      break;

    default:
      /* The original callback */
      BUTTON_Callback(pMsg);
      break;
  }
}

/*********************************************************************
*
*       _ShowInfoScreen
*
* Purpose:
*   Show the Info Screen.
*/
void _ShowInfoScreen(WM_HWIN hParent)
{
  WM_HWIN           hInfo;
  BUTTON_Handle     hBut_back;

  hInfo            = WM_CreateWindowAsChild(0, 0, LCD_GetXSize(), LCD_GetYSize(), hParent, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_STAYONTOP, _cbInfo, 0);

  /* Create different buttons to be used */
  hBut_back = BUTTON_CreateEx(100, 320, 190, 70, hInfo, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_STAYONTOP, 0 , ID_BUTTON_BACK);
  WM_SetCallback(hBut_back, _cbButton);

  //
  // Fade in new window
  //
  GUI_EnableAlpha(1);
  GUI_MEMDEV_FadeInWindow(hInfo, 2000);
  GUI_EnableAlpha(0);

  //
  // Make sure background is filled with transparency
  //
  WM_Invalidate(WM_GetDesktopWindowEx(0));
}

/*********************************************************************
*
*       _cbBk
*
*  Function description:
*    Callback routine of desktop window
*/
static void _cbBk(WM_MESSAGE * pMsg)
{
  WM_HWIN     hWin;
  int Id, NCode;

  if (!GUI_Initialized)
  {
    return; /* Not yet initialized! */
  }

  hWin = pMsg->hWin;
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      GUI_DrawBitmap(&bmbackground, 0, 0);
      break;

    case WM_NOTIFY_PARENT:
    {
      Id = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch(NCode)
      {
        //
        // React only if window is not moving.
        //
        case WM_NOTIFICATION_RELEASED:
        {
          // Only Info Button being attached the BKG window
          switch(Id)
          {
            case ID_BUTTON_INFO:
              _ShowInfoScreen(hWin);
              break;
          }
        }
        break;
      }
    }
    break;

    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

/*********************************************************************
*
*       _cbDraw
*
*  Function description:
*    Callback routine of radial menu
*/
static void _cbDraw(WM_MESSAGE * pMsg)
{
  WM_HWIN     hWin;
  PARA      * pPara;
  int         i, a1000, Swap;
  I32         SinHQ;
  I32         CosHQ;
  I32         a;
  ITEM_INFO   ItemInfo;

  hWin = pMsg->hWin;

  if (!GUI_Initialized)
  {
    return; /* Not yet initialized! */
  }

  WM_GetUserData(hWin, &pPara, sizeof(pPara));
  if (!pPara)
  {
    return; /* Widget being initialized and user data aren't yet set! */
  }

  switch (pMsg->MsgId)
  {
    case WM_PAINT:
    {
      //
      // One time initialization of parameter structure
      //
      if (pPara->xSizeItem == 0)
      {
        pPara->xSizeWindow = WM_GetWindowSizeX(hWin);
        pPara->ySizeWindow = WM_GetWindowSizeY(hWin);
        pPara->xSizeItem   = pPara->pBitmapItem[0].pBitmap->XSize;
        pPara->ySizeItem   = pPara->pBitmapItem[0].pBitmap->YSize;
        pPara->rx          = ( pPara->xSizeWindow       - pPara->xSizeItem + 10);
        pPara->ry          = ((pPara->ySizeWindow ) - pPara->ySizeItem - 20) ;
        pPara->mx          = 290;
        pPara->my          = (pPara->ySizeItem + 40) ;
      }

      //
      // Calculate current positions of items
      //
      a1000 = (pPara->Pos * 3600) / pPara->NumItems;
      for (i = 0; i < pPara->NumItems; i++)
      {
        a = 360000 + a1000 + (i * 360000) / pPara->NumItems;
        SinHQ = GUI__SinHQ(a);
        CosHQ = GUI__CosHQ(a);
        pPara->pItemInfo[i].Index = i;
        pPara->pItemInfo[i].xPos  = pPara->mx - ((CosHQ * pPara->rx) >> 16);
        pPara->pItemInfo[i].yPos  = pPara->my + ((SinHQ * pPara->ry) >> 16);
      }
      //
      // Bubble sort items to be able to draw background items first
      //
      do
      {
        Swap = 0;
        for (i = 0; i < (pPara->NumItems - 1); i++)
        {
          if (pPara->pItemInfo[i].yPos > pPara->pItemInfo[i + 1].yPos)
          {
            ItemInfo = pPara->pItemInfo[i];
            pPara->pItemInfo[i] = pPara->pItemInfo[i + 1];
            pPara->pItemInfo[i + 1] = ItemInfo;
            Swap = 1;
          }
        }
      } while (Swap);

      //
      // Draw items
      //
      for (i = 0; i < pPara->NumItems; i++)
      {
        GUI_DrawBitmap((pPara->pBitmapItem + pPara->pItemInfo[i].Index)->pBitmap, pPara->pItemInfo[i].xPos - pPara->xSizeItem / 2, pPara->pItemInfo[i].yPos - pPara->ySizeItem / 2);
      }

      //
      // Draw item text only after final move
      //
      if (pPara->FinalMove || (FirstTime <= 1))
      {
        GUI_RECT Rect = {pPara->xSizeWindow/2, pPara->ySizeWindow/2 - 30, pPara->xSizeWindow/2 + 120, pPara->ySizeWindow/2 + 30};

        GUI_SetTextMode(GUI_TM_TRANS);
        GUI_SetFont(&GUI_FontLucidaSansUnicode25);
        GUI_SetColor(GUI_WHITE);
        GUI_DispStringInRectWrap((pPara->pBitmapItem + pPara->pItemInfo[pPara->NumItems - 3].Index)->pExplanation, &Rect, (GUI_TA_VCENTER | GUI_TA_HCENTER), (pPara->pBitmapItem + pPara->pItemInfo[pPara->NumItems - 3].Index)->aWm);
        FirstTime++;
        pPara->Index = pPara->pItemInfo->Index;
      }
    }
    break;

    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

/*********************************************************************
*
*       _cbMotion
*
*  Function description:
*    Callback routine of transparent motion window which is responsible
*    for processing the motion messages.
*/
static void _cbMotion(WM_MESSAGE * pMsg)
{
  WM_PID_STATE_CHANGED_INFO * pInfoPID;
  WM_MOTION_INFO * pInfoMotion;
  WM_HWIN          hWin;
  PARA           * pPara;
  static int NoMove = 1;
  static int MotionActive;
  int Id, NCode;

  hWin = pMsg->hWin;

  if (!GUI_Initialized)
  {
    return; /* Not yet initialized! */
  }

  WM_GetUserData(hWin, &pPara, sizeof(pPara));
  if (!pPara)
  {
    return; /* Widget being initialized and user data aren't yet set! */
  }

  switch (pMsg->MsgId)
  {
    case WM_MOTION:
    {
      pInfoMotion = (WM_MOTION_INFO *)pMsg->Data.p;
      switch (pInfoMotion->Cmd)
      {
        case WM_MOTION_INIT:
          pInfoMotion->Flags = WM_CF_MOTION_X | WM_MOTION_MANAGE_BY_WINDOW;
          pInfoMotion->SnapX = 100;
          pInfoMotion->Overlap = 49;
          pInfoMotion->Period = 200;
          WM_MOTION_SetThreshold(5);
          WM_MOTION_SetMinMotion(1);
          break;
        case WM_MOTION_MOVE:
          MotionActive = 1;
          NoMove = 0;
          pPara->FinalMove = pInfoMotion->FinalMove;
          if ((pInfoMotion->pState) && (pInfoMotion->pState->y < 195))
          {
            pPara->Pos -= pInfoMotion->dx;
          }
          else
          {
            pPara->Pos += pInfoMotion->dx;
          }
          if (pPara->Pos > pPara->NumItems * 100)
          {
            pPara->Pos -= pPara->NumItems * 100;
            pInfoMotion->StopMotion = 1;
          }
          if (pPara->Pos < 0)
          {
            pPara->Pos += pPara->NumItems * 100;
            pInfoMotion->StopMotion = 1;
          }
          WM_Invalidate(WM_GetParent(hWin));
          if(pInfoMotion->FinalMove)
          {
            MotionActive = 0;
          }
          break;
        case WM_MOTION_GETPOS:
          pInfoMotion->xPos = pPara->Pos;
          break;
      }
    }
    break;
    case WM_PID_STATE_CHANGED:
    {
      pInfoPID = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
      if ((pInfoPID->State == 1) && (pInfoPID->StatePrev == 0))
      {
        NoMove = 1;
      }
      else if ((pInfoPID->State == 0) && (pInfoPID->StatePrev == 1))
      {
        if(NoMove)
        {
          NoMove = 0;
        }
      }
    }
    break;
    case WM_NOTIFY_PARENT:
    {
      Id = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch(NCode)
      {
        //
        // Only Module Button's being attached the Motion window
        //
        case WM_NOTIFICATION_RELEASED:
        {
          //
          // React only if window is not moving.
          //
          if ( (MotionActive == 0)/* && (NoMove == 1)*/ )
          {
            switch(Id)
            {
              case ID_BUTTON_MODULE_CENTER:
              {
                int disable = 1;
                WM_ForEachDesc(WM_HBKWIN, _cbDisableWindow, (void *)&disable);
                SUBDEMO_Start(WM_HBKWIN, (pPara->pBitmapItem + pPara->pItemInfo[pPara->NumItems - 3].Index)->pDemoContext);
                disable = 0;
                WM_ForEachDesc(WM_HBKWIN, _cbDisableWindow, (void *)&disable);
              }
              break;
              case ID_BUTTON_MODULE_TOP:
              {
                WM_MOTION_SetMovement(hWin, GUI_COORD_X, 500, 100);
              }
              break;
              case ID_BUTTON_MODULE_DOWN:
              {
                WM_MOTION_SetMovement(hWin, GUI_COORD_X, -500, 100);
              }
              break;
            }
          }
        }
        break;
      }
    }
    break;
  }
}

/*********************************************************************
*
*       _SplashScreen
*
*  Function description:
*    Show the Splash Screen at startup.
*/
static void _SplashScreen(void)
{
  uint32_t XPos = 110, XOffset = 5;
  const char ST_Slogan[] = "life.augmented";
  const char *p = ST_Slogan;

  GUI_SetBkColor(GUI_WHITE);
  GUI_Clear();
  GUI_DrawBitmap(&bmSTLogo, (LCD_GetXSize() - (bmSTLogo.XSize))/2 , (LCD_GetYSize() - (bmSTLogo.YSize) - 30)/2);

  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_SetColor(GUI_MAKE_COLOR(GUI_STCOLOR_LIGHTBLUE));

  do
  {
    GUI_DispCharAt(*p, XPos , 235);
    XPos += GUI_GetCharDistX(*p++) + XOffset + 1;
    if(*p == '.')
    {
      GUI_SetColor(GUI_MAKE_COLOR(GUI_STCOLOR_DARKBLUE));
      XOffset = 0;
    }
    LCD_WaitForDisplayCompletion();

    GUI_Exec1();
    LCD_RefreshRequestedByApplicatyion();

    LCD_WaitForDisplayCompletion();

    GUI_Delay(50);
  } while (*p != 0);

  GUI_Delay(1000); 
}

/*********************************************************************
*
*       _MenuLauncher
*
*  Function description:
*    Creates and executes a radial menu with motion support.
*/
static void _MenuLauncher(void const * argument)
{
  static ITEM_INFO  aItemInfo[GUI_COUNTOF(_aBitmapItem)];
  static PARA       Para;
  WM_HWIN           hDraw;
  WM_HWIN           hMotion;
  PARA            * pPara;
  int               xSizeWindow;
  int               ySizeWindow;
  int               xSize;
  int               ySize;
  BUTTON_Handle     hBut, hBut_info;

  GUI_LOCK();

  //
  // Get display dimension
  //
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();

  //
  // Limit desktop window to display size
  //
  WM_SetSize(WM_HBKWIN, xSize, ySize);

  //
  // Set the Background Callback
  //
  WM_SetCallback(WM_HBKWIN, _cbBk);

  //
  // Initialize parameter structure for items to be shown
  //
  pPara = &Para;
  pPara->NumItems    = GUI_COUNTOF(_aBitmapItem);
  pPara->pBitmapItem = _aBitmapItem;
  pPara->pItemInfo   = aItemInfo;
  pPara->Pos         = 0;
  pPara->Index       = 0;
  pPara->DoAnimation = 1;

  //
  // Create radial menu window
  //
  hDraw              = WM_CreateWindowAsChild(20, 0, xSize - 40, ySize, WM_HBKWIN, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_BGND, _cbDraw, sizeof(pPara));

  //
  // Create transparent window which receives the motion messages
  //
  xSizeWindow        = WM_GetWindowSizeX(hDraw);
  ySizeWindow        = WM_GetWindowSizeY(hDraw);
  hMotion            = WM_CreateWindowAsChild(0, 0, xSizeWindow, ySizeWindow, hDraw, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_FGND, _cbMotion, sizeof(pPara));

  //
  // Add pointer to parameter structure to windows
  //
  WM_SetUserData(hDraw,   &pPara, sizeof(pPara));
  WM_SetUserData(hMotion, &pPara, sizeof(pPara));

  //
  // Create different buttons to be used
  //
  hBut = BUTTON_CreateEx(29, (ySizeWindow - 108)/2, 108, 108, hMotion, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_STAYONTOP, 0 , ID_BUTTON_MODULE_CENTER);
  WM_SetCallback(hBut, _cbButton);

  hBut = BUTTON_CreateEx(12 + (xSizeWindow - 108) / 2, 0, 108, 76, hMotion, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_STAYONTOP, 0, ID_BUTTON_MODULE_TOP);
  WM_SetCallback(hBut, _cbButton);

  hBut = BUTTON_CreateEx(12 + (xSizeWindow - 108) / 2, (ySizeWindow - 76), 108, 76, hMotion, WM_CF_SHOW | WM_CF_HASTRANS | WM_CF_STAYONTOP, 0, ID_BUTTON_MODULE_DOWN);
  WM_SetCallback(hBut, _cbButton);

  hBut_info = BUTTON_CreateEx(314, 138, 76, 108, WM_HBKWIN, WM_CF_SHOW | WM_CF_HASTRANS, 0 , ID_BUTTON_INFO);
  WM_SetCallback(hBut_info, _cbButton);

#ifdef GUI_SIMULATOR
  GUI_SPY_StartServer();
#endif /* GUI_SIMULATOR */

  GUI_UNLOCK();
}

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void)
{
  /* Initialize the GUI */
  GUI_Init();

  WM_MOTION_Enable(1);

  /* Set the buttons to react only on level changes, only.*/
  BUTTON_SetReactOnLevel();

  WM_MULTIBUF_Enable(1);

  if (software_reset_flag == 0)
  {
    /* Show the Splash Screen before running the Menu Launcher application */
    _SplashScreen();
  }

  _MenuLauncher(NULL);

  GUI_Initialized = 1;

  //
  // Keep demo alive
  //
  while (1)
  {
    LCD_WaitForDisplayCompletion();

    GUI_Exec1();
    LCD_RefreshRequestedByApplicatyion();

    LCD_WaitForDisplayCompletion();
  }
}

/*************************** End of file ****************************/
