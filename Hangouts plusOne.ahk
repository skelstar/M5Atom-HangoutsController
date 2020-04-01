
;------------------------------------------------------------------

FindTabInActiveFirefox(TabName, SleepForTabSwitch=400)
{
}

;------------------------------------------------------------------

^+k::
  MouseClick, left, 1800, 100
  Sleep 1000
  SendRaw, +1
  Sleep 500
  Send {Enter}
  Sleep 500
  MouseClick, left, 500, 500
  return

 