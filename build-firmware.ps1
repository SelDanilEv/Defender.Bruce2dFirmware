param(
    [string]$Environment = "lilygo-t-embed-cc1101",
    [string]$CopyTo = "",
    [string]$TargetName = "bruce-2d-cc1101.bin",
    [switch]$DebugBuild
)

$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

$pio = Get-Command pio -ErrorAction SilentlyContinue
$pioPath = if ($pio) { $pio.Source } else { Join-Path $env:USERPROFILE ".platformio\penv\Scripts\pio.exe" }
if (-not (Test-Path $pioPath)) { throw "PlatformIO not found. Install it or add pio to PATH." }

$buildEnvironment = if ($DebugBuild) { "$Environment-debug" } else { $Environment }

$startedAt = Get-Date
& $pioPath run -e $buildEnvironment
if ($LASTEXITCODE -ne 0) { throw "Build failed with exit code $LASTEXITCODE" }

$binFilter = if ($DebugBuild) { "Bruce2D-*-dv*.bin" } else { "Bruce2D-*.bin" }
$bin = Get-ChildItem -Path $PSScriptRoot -Filter $binFilter |
    Where-Object { $_.LastWriteTime -ge $startedAt -and ($DebugBuild -or $_.Name -notlike "*-dv*.bin") } |
    Sort-Object LastWriteTime -Descending |
    Select-Object -First 1
if (-not $bin) {
    throw "Merged binary not produced for env '$buildEnvironment'"
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
