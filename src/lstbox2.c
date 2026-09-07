/*-----------------------------------------------------------------------
   LSTBOX2.C -- Multi-Column List Box Demo for OS/2 PM

   Demonstrates LS_OWNERDRAW list box handling with WM_MEASUREITEM and
   WM_DRAWITEM to render a two-column list box.  Each list box item is
   stored as "COLUMN1 rest of text" and a blank is used as the column
   separator.

   Originally by Guy Scharf, Software Architects, Inc.
   Completed into a full PM program by Martin Iturbide (2026).
-----------------------------------------------------------------------*/

#define INCL_32
#define INCL_GPI
#define INCL_WIN
#define INCL_WINLISTBOXES
#include <os2.h>
#include <string.h>

/* Watcom headers define PCH but not PCCH */
#ifdef __WATCOMC__
#define PCCH PCH
#endif

#include "lstbox2.h"

/* Sample data: "FILENAME  Description of the file"
   First word (before first space) is column 1; rest is column 2. */
static const char * const apszItems[] = {
    "AUTOEXEC.BAT  Startup batch processor",
    "CLOCK01.BMP   Default system clock bitmap",
    "CONFIG.SYS    OS/2 system configuration",
    "DESKTOP       WPS desktop folder",
    "NOWHERE.EXE   Shredder target program",
    "OS2KRNL       OS/2 kernel image",
    "OS2LDR        OS/2 boot loader",
    "STARTUP.CMD   System startup command file",
    "SWAPPER.DAT   Virtual memory swap file",
    "UNDELETE.LOG  File deletion log",
    NULL
};


/* -----------------------------------------------------------------------
   FillCfgListBox -- populate the owner-draw list box with sample data
   ----------------------------------------------------------------------- */
VOID FillCfgListBox (HWND hwndDlg)
{
    HWND hwndLB = WinWindowFromID (hwndDlg, ID_LISTBOX);
    int  i;

    for (i = 0; apszItems[i] != NULL; i++)
        WinSendMsg (hwndLB, LM_INSERTITEM,
                    (MPARAM) LIT_END, (MPARAM) apszItems[i]);
}


/* -----------------------------------------------------------------------
   SelectDlgProc -- dialog procedure
   ----------------------------------------------------------------------- */
MRESULT EXPENTRY SelectDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    HPS          hPS;
    FONTMETRICS  FontMetrics;
    CHAR         pszItemText[MAX_ITEM_TEXT_LENGTH];
    CHAR        *s;
    OWNERITEM   *poi;
    RECTL        rcl;
    COLOR        clrForeGround;
    COLOR        clrBackGround;

    switch (msg)
        {
        case WM_INITDLG:               /* Initialize the list box */

            FillCfgListBox (hwnd);     /* Fill the list box */

            return (MRESULT) FALSE;


        case WM_MEASUREITEM:           /* Measure text height */

            hPS = WinGetPS (hwnd);
            GpiQueryFontMetrics (hPS, (LONG) sizeof (FONTMETRICS),
                                 &FontMetrics);
            WinReleasePS (hPS);

            return (MRESULT)(LONG) FontMetrics.lMaxBaselineExt;


        case WM_DRAWITEM:              /* Draw a list box entry */

            poi = (OWNERITEM *) mp2;

            if (poi->fsState)          /* Highlighted? */
            {
                clrForeGround = SYSCLR_HILITEFOREGROUND;
                clrBackGround = SYSCLR_HILITEBACKGROUND;
            }
            else
            {
                clrForeGround = CLR_NEUTRAL;
                clrBackGround = CLR_BACKGROUND;
            }

            WinSendMsg (poi->hwnd,
                        LM_QUERYITEMTEXT,
                        (MPARAM) MAKEULONG (poi->idItem,
                                            MAX_ITEM_TEXT_LENGTH),
                        (MPARAM) pszItemText);

            rcl.xLeft   = poi->rclItem.xLeft;
            rcl.xRight  = poi->rclItem.xRight;
            rcl.yTop    = poi->rclItem.yTop;
            rcl.yBottom = poi->rclItem.yBottom;

            s = strchr (pszItemText, ' ');   /* Find column separator */
            if (s)
                *s = '\0';

            WinDrawText (poi->hps,           /* Draw column 1 */
                         -1,
                         (PCCH) pszItemText,
                         &rcl,
                         clrForeGround,
                         clrBackGround,
                         DT_LEFT | DT_VCENTER | DT_ERASERECT);

            if (s)                           /* Draw column 2 */
            {
                rcl.xLeft = 100;
                s++;
                WinDrawText (poi->hps,
                             -1,
                             (PCCH) s,
                             &rcl,
                             clrForeGround,
                             clrBackGround,
                             DT_LEFT | DT_VCENTER);
            }

            poi->fsState = poi->fsStateOld = FALSE;

            return (MRESULT) TRUE;


        case WM_COMMAND:

            switch (SHORT1FROMMP (mp1))
            {
                case DID_OK:
                case DID_CANCEL:
                    WinDismissDlg (hwnd, SHORT1FROMMP (mp1));
                    return (MRESULT) FALSE;
            }
            break;
        }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}


/* -----------------------------------------------------------------------
   main -- initialize PM and run the dialog
   ----------------------------------------------------------------------- */
int main (VOID)
{
    HAB hab;
    HMQ hmq;

    hab = WinInitialize (0);
    hmq = WinCreateMsgQueue (hab, 0);

    WinDlgBox (HWND_DESKTOP, HWND_DESKTOP,
               SelectDlgProc, (HMODULE) 0, ID_DIALOG, NULL);

    WinDestroyMsgQueue (hmq);
    WinTerminate (hab);
    return 0;
}
