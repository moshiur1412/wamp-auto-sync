# WampAutoSync Startup Script
# This script is called on system startup

param(
    [string]$InstallPath = "$env:LOCALAPPDATA\WampAutoSync"
)

# Wait for system to be ready
Start-Sleep -Seconds 10

# Check if WampServer is running
$wampProcess = Get-Process -Name "wampmanager" -ErrorAction SilentlyContinue
if (-not $wampProcess) {
    # Wait for WampServer to start
    $maxWait = 60
    $waited = 0
    while (-not $wampProcess -and $waited -lt $maxWait) {
        Start-Sleep -Seconds 5
        $waited += 5
        $wampProcess = Get-Process -Name "wampmanager" -ErrorAction SilentlyContinue
    }
}

# Start WampAutoSync
$exePath = Join-Path $InstallPath "WampAutoSync.exe"
if (Test-Path $exePath) {
    Start-Process -FilePath $exePath -WindowStyle Hidden
}
