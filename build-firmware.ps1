param(
    [string]$Environment = "lilygo-t-embed-cc1101",
    [string]$CopyTo = "",
    [string]$TargetName = "bruce-2d-cc1101.bin"
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

$pio = Get-Command pio -ErrorAction SilentlyContinue
$pioPath = if ($pio) { $pio.Source } else { Join-Path $env:USERPROFILE ".platformio\penv\Scripts\pio.exe" }
if (-not (Test-Path $pioPath)) { throw "PlatformIO not found. Install it or add pio to PATH." }

$startedAt = Get-Date
& $pioPath run -e $Environment
if ($LASTEXITCODE -ne 0) { throw "Build failed with exit code $LASTEXITCODE" }

$bin = Get-ChildItem -Path $PSScriptRoot -Filter "Bruce2D-*.bin" |
    Where-Object { $_.LastWriteTime -ge $startedAt } |
    Sort-Object LastWriteTime -Descending |
    Select-Object -First 1
if (-not $bin) {
    throw "Merged binary not produced for env '$Environment'"
}

$elapsed = (Get-Date) - $startedAt
Write-Host ""
Write-Host "Build OK in $([int]$elapsed.TotalMinutes)m $($elapsed.Seconds)s"
Write-Host "Firmware: $($bin.FullName) ($($bin.Length) bytes)"

if ($CopyTo) {
    $destination = Join-Path $CopyTo $TargetName
    Copy-Item $bin.FullName $destination -Force
    Write-Host "Copied to: $destination"
}

Start-Process explorer.exe "/select,`"$($bin.FullName)`""
