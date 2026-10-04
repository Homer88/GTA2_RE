param([int]$Wait = 20)
$g = 'C:\games\GTA2 _old'
Get-Process -Name 'gta2-resurected' -EA SilentlyContinue | Stop-Process -Force -EA SilentlyContinue
Start-Sleep 1
Remove-Item "$g\log\gdi.log","$g\log\video_trace.log","$g\gta2_crash.log" -EA SilentlyContinue
$p = Start-Process -FilePath "$g\gta2-resurected.exe" -WorkingDirectory $g -PassThru
Start-Sleep $Wait
$pr = Get-Process -Id $p.Id -EA SilentlyContinue
if (-not $pr) { "EXITED before $Wait s"; exit }
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;using System.Runtime.InteropServices;
public class W {
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
 [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out R r);
 [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr h, ref P p);
 [StructLayout(LayoutKind.Sequential)] public struct R { public int L,T,Rr,B; }
 [StructLayout(LayoutKind.Sequential)] public struct P { public int X,Y; }
}
"@
$h = $pr.MainWindowHandle
"hWnd=$h  title='$($pr.MainWindowTitle)'  ws=$([math]::Round($pr.WorkingSet64/1MB))MB"
if ($h -eq 0) { "no window"; exit }
$r = New-Object W+R
[void][W]::GetClientRect($h, [ref]$r)
$pt = New-Object W+P
[void][W]::ClientToScreen($h, [ref]$pt)
$w = $r.Rr; $ht = $r.B
"client=${w}x${ht} at screen $($pt.X),$($pt.Y)"
$bmp = New-Object System.Drawing.Bitmap $w, $ht
$gfx = [System.Drawing.Graphics]::FromImage($bmp)
$gfx.CopyFromScreen($pt.X, $pt.Y, 0, 0, $bmp.Size)
$bmp.Save("$env:TEMP\gta2_shot.png", [System.Drawing.Imaging.ImageFormat]::Png)
# count non-black pixels
$nonblack = 0; $colors = @{}
for ($y = 0; $y -lt $ht; $y += 4) {
  for ($x = 0; $x -lt $w; $x += 4) {
    $c = $bmp.GetPixel($x, $y)
    if ($c.R -gt 8 -or $c.G -gt 8 -or $c.B -gt 8) { $nonblack++ }
    $k = "$($c.R),$($c.G),$($c.B)"
    if ($colors.ContainsKey($k)) { $colors[$k]++ } else { $colors[$k] = 1 }
  }
}
"saved: $env:TEMP\gta2_shot.png"
"non-black samples: $nonblack / $((($ht/4)*($w/4)))"
"top colors:"
$colors.GetEnumerator() | Sort-Object Value -Descending | Select-Object -First 6 | ForEach-Object { "   $($_.Key)  x$($_.Value)" }
$log = Get-Content "$g\log\gdi.log" -EA SilentlyContinue
"--- gdi calls ---"
foreach ($n in 'gbh_LoadImage','gbh_BlitImage','gbh_BeginScene','gbh_EndScene','gbh_CloseDLL','gbh_BlitBuffer') {
  "  {0,-18} {1}" -f $n, (($log | Select-String $n | Measure-Object).Count)
}
"  AV in gdi log:      $(($log | Select-String 'ACCESS_VIOLATION' | Measure-Object).Count)"
"  strlen patches:     $((Get-Content "$g\log\video_trace.log" -EA SilentlyContinue | Select-String 'strlen-patched' | Measure-Object).Count)"
