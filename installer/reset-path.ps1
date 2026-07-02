# WampAutoSync Reset PATH Script
# This script resets the user PATH to remove WampAutoSync entries

param(
    [switch]$Force
)

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  WampAutoSync PATH Reset" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Get current PATH
$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
Write-Host "Current User PATH:" -ForegroundColor Yellow
Write-Host $currentPath -ForegroundColor Gray
Write-Host ""

# Find WampAutoSync entries
$pathEntries = $currentPath -split ";" | Where-Object { $_ -like "*WampAutoSync*" }

if ($pathEntries.Count -eq 0) {
    Write-Host "No WampAutoSync entries found in PATH." -ForegroundColor Green
    exit 0
}

Write-Host "WampAutoSync entries found:" -ForegroundColor Yellow
foreach ($entry in $pathEntries) {
    Write-Host "  - $entry" -ForegroundColor Red
}
Write-Host ""

if (-not $Force) {
    $confirm = Read-Host "Do you want to remove these entries? (Y/N)"
    if ($confirm -ne "Y") {
        Write-Host "Operation cancelled." -ForegroundColor Yellow
        exit 0
    }
}

# Remove WampAutoSync entries
$newPath = ($currentPath -split ";" | Where-Object { $_ -notlike "*WampAutoSync*" }) -join ";"

# Set new PATH
[Environment]::SetEnvironmentVariable("Path", $newPath, "User")

Write-Host ""
Write-Host "PATH has been reset successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "New User PATH:" -ForegroundColor Yellow
Write-Host $newPath -ForegroundColor Gray
Write-Host ""
Write-Host "Press any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
