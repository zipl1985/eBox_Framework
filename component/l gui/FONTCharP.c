/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUICharP.C
Purpose     : Implementation of Proportional fonts
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
//#include "GUI_Private.h"
#include "lgui_font.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       查找字符，返回字符所在链表地址
*/
const GUI_FONT_PROP * GUIPROP_FindChar(const GUI_FONT_PROP * pProp, uint16_t c) {
  for (; pProp; pProp = pProp->pNext) {
    if ((c>=pProp->First) && (c<=pProp->Last))
      break;
  }
  return pProp;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIPROP_DispChar
*
* Purpose:
*   This is the routine that displays a character. It is used by all
*   other routines which display characters as a subroutine.
*/
void GUIPROP_DispChar(void) {

}

/*********************************************************************
*
*       GUIPROP_GetCharDistX
*/
int GUIPROP_GetCharDistX(const GUI_FONT * pFont,uint16_t c) {
  const GUI_FONT_PROP * pProp = GUIPROP_FindChar(pFont->p.pProp, c);
  return (pProp) ? (pProp->paCharInfo+(c-pProp->First))->XSize * pFont->XMag : 0;
}

/*********************************************************************
*
*       GUIPROP_GetFontInfo
*/
uint16_t GUIPROP_GetFontInfo(void) {
  return GUI_FONTINFO_FLAG_PROP;
}

/*********************************************************************
*
*       GUIPROP_IsInFont
*/
char GUIPROP_IsInFont(const GUI_FONT * pFont, uint16_t c) {
  const GUI_FONT_PROP * pProp = GUIPROP_FindChar(pFont->p.pProp, c);
  return (pProp==NULL) ? 0 : 1;
}

/*************************** End of file ****************************/
