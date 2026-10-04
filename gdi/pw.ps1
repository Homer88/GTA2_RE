$g = 'C:\games\GTA2 _old'
Get-Process -Name 'gta2-resurected' -EA SilentlyContinue | Stop-Process -Force -EA SilentlyContinue
Start-Sleep 1
$proc = Start-Process -FilePath "$g\gta2-resurected.exe" -WorkingDirectory $g -PassThru
Start-Sleep 22
$p = Get-Process -Id $proc.Id -EA SilentlyContinue
if (-not $p) { "EXITED"; exit }
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;using System.Runtime.InteropServices;
public class PW {
 [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint f);
 [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out R r);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out R r);
 [StructLayout(LayoutKind.Sequential)] public struct R { public int L,T,Rr,B; }
}
"@
$p = Get-Process -Name 'gta2-resurected' -EA SilentlyContinue | Select-Object -First 1
if (-not $p) { "no process"; exit }
$h = $p.MainWindowHandle
"hWnd=$h title='$($p.MainWindowTitle)'"
$r = New-Object PW+R
[void][PW]::GetWindowRect($h, [ref]$r)
$w = $r.Rr - $r.L; $ht = $r.B - $r.T
"window=${w}x${ht}"
$bmp = New-Object System.Drawing.Bitmap $w, $ht
$gfx = [System.Drawing.Graphics]::FromImage($bmp)
$hdc = $gfx.GetHdc()
$ok = [PW]::PrintWindow($h, $hdc, 2)   # PW_RENDERFULLCONTENT
$gfx.ReleaseHdc($hdc)
$gfx.Dispose()
$out = "$env:TEMP\gta2_pw.png"
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Png)
"PrintWindow=$ok  saved=$out"
$nonblack = 0; $colors = @{}
for ($y = 0; $y -lt $ht; $y += 5) {
  for ($x = 0; $x -lt $w; $x += 5) {
    $c = $bmp.GetPixel($x, $y)
    if ($c.R -gt 10 -or $c.G -gt 10 -or $c.B -gt 10) { $nonblack++ }
    $k = "$($c.R),$($c.G),$($c.B)"
    if ($colors.ContainsKey($k)) { $colors[$k]++ } else { $colors[$k] = 1 }
  }
}
$tot = [math]::Ceiling($ht/5) * [math]::Ceiling($w/5)
"non-black: $nonblack / $tot"
"top colors:"
$colors.GetEnumerator() | Sort-Object Value -Descending | Select-Object -First 8 | ForEach-Object { "   $($_.Key)  x$($_.Value)" }
