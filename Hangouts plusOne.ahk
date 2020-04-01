
/*
- clicks on chat icon
- waits for focus
- sends "+1"
- waits, then <enter>
- waits then clicks out in main window
*/

^+k::
  MouseClick, left, 1800, 100
  Sleep 1000
  SendRaw, +1
  Sleep 500
  Send {Enter}
  Sleep 500
  MouseClick, left, 500, 500
  return

 