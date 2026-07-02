# WampAutoSync Uninstall Script
# Run as Administrator

param(
    [string]$InstallPath = "$env:LOCALAPPDATA\WampAutoSync"
)

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  WampAutoSync Uninstaller" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Check if running as administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "This script requires Administrator privileges." -ForegroundColor Red
    Write-Host "Please right-click and select 'Run as Administrator'." -ForegroundColor Yellow
    exit 1
}

# Stop running instance
$process = Get-Process -Name "WampAutoSync" -ErrorAction SilentlyContinue
if ($process) {
    Write-Host "Stopping WampAutoSync..." -ForegroundColor Yellow
    Stop-Process -Name "WampAutoSync" -Force
    Start-Sleep -Seconds 2
}

# Remove startup shortcut
$startupPath = [Environment]::GetFolderPath("Startup")
$shortcutPath = Join-Path $startupPath "WampAutoSync.lnk"
if (Test-Path $shortcutPath) {
    Remove-Item -Path $shortcutPath -Force
    Write-Host "Removed startup shortcut" -ForegroundColor Green
}

# Remove from PATH
$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($currentPath -like "*$InstallPath*") {
    $newPath = ($currentPath -split ";" | Where-Object { $_ -ne $InstallPath }) -join ";"
    [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
    Write-Host "Removed from user PATH" -ForegroundColor Green
}

# Remove auto start registry
$runKeyPath = "HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Run"
if (Get-ItemProperty -Path $runKeyPath -Name "WampAutoSync" -ErrorAction SilentlyContinue) {
    Remove-ItemProperty -Path $runKeyPath -Name "WampAutoSync" -Force
    Write-Host "Removed auto start registry" -ForegroundColor Green
}

# Remove installation directory
if (Test-Path $InstallPath) {
    Write-Host "Removing installation directory..." -ForegroundColor Yellow
    Remove-Item -Path $InstallPath -Recurse -Force
    Write-Host "Removed installation directory" -ForegroundColor Green
}

# Remove log files
$logPath = Join-Path $env:LOCALAPPDATA "WampAutoSync"
if (Test-Path $logPath) {
    Remove-Item -Path $logPath -Recurse -Force
    Write-Host "Removed log files" -ForegroundColor Green
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  Uninstallation Complete!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "WampAutoSync has been removed from your system." -ForegroundColor White
Write-Host ""
Write-Host "Press any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
