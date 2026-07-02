# WampAutoSync Install Script
# Run as Administrator

param(
    [string]$InstallPath = "$env:LOCALAPPDATA\WampAutoSync",
    [string]$WampPath = "C:\wamp64"
)

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  WampAutoSync Installer" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Check if running as administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "This script requires Administrator privileges." -ForegroundColor Red
    Write-Host "Please right-click and select 'Run as Administrator'." -ForegroundColor Yellow
    exit 1
}

# Check if WampServer exists
if (-not (Test-Path $WampPath)) {
    Write-Host "WampServer not found at: $WampPath" -ForegroundColor Red
    $WampPath = Read-Host "Enter WampServer path"
    if (-not (Test-Path $WampPath)) {
        Write-Host "Invalid WampServer path. Exiting." -ForegroundColor Red
        exit 1
    }
}

Write-Host "Installing WampAutoSync..." -ForegroundColor Green
Write-Host "  Install Path: $InstallPath" -ForegroundColor Gray
Write-Host "  Wamp Path: $WampPath" -ForegroundColor Gray
Write-Host ""

# Create installation directory
if (-not (Test-Path $InstallPath)) {
    New-Item -ItemType Directory -Path $InstallPath -Force | Out-Null
}

# Copy files
$sourcePath = Split-Path -Parent $PSScriptRoot
$publishPath = Join-Path $sourcePath "build\Release"

if (Test-Path $publishPath) {
    Write-Host "Copying application files..." -ForegroundColor Yellow
    Copy-Item -Path "$publishPath\*" -Destination $InstallPath -Recurse -Force
} else {
    Write-Host "Build directory not found. Please build the project first." -ForegroundColor Red
    Write-Host "Run: msbuild /p:Configuration=Release /p:Platform=x64" -ForegroundColor Yellow
    exit 1
}

# Create config file
$configPath = Join-Path $InstallPath "appsettings.json"
if (-not (Test-Path $configPath)) {
    $config = @{
        WampPath = $WampPath
        WatchPHP = $true
        WatchMySQL = $true
        WatchMariaDB = $false
        BroadcastEnvironment = $true
        UpdateComposer = $true
        AutoStart = $true
        LogLevel = "Information"
    }
    $config | ConvertTo-Json | Out-File -FilePath $configPath -Encoding UTF8
    Write-Host "Created configuration file" -ForegroundColor Green
}

# Create startup shortcut
$startupPath = [Environment]::GetFolderPath("Startup")
$shortcutPath = Join-Path $startupPath "WampAutoSync.lnk"
$exePath = Join-Path $InstallPath "WampAutoSync.exe"

if (Test-Path $exePath) {
    $shell = New-Object -ComObject WScript.Shell
    $shortcut = $shell.CreateShortcut($shortcutPath)
    $shortcut.TargetPath = $exePath
    $shortcut.WorkingDirectory = $InstallPath
    $shortcut.Description = "WampAutoSync - Auto sync PHP and MySQL versions"
    $shortcut.Save()
    Write-Host "Created startup shortcut" -ForegroundColor Green
}

# Add to PATH
$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($currentPath -notlike "*$InstallPath*") {
    [Environment]::SetEnvironmentVariable("Path", "$currentPath;$InstallPath", "User")
    Write-Host "Added to user PATH" -ForegroundColor Green
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  Installation Complete!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "WampAutoSync has been installed to:" -ForegroundColor White
Write-Host "  $InstallPath" -ForegroundColor Yellow
Write-Host ""
Write-Host "The application will start automatically on next login." -ForegroundColor White
Write-Host "You can also run it manually from the installation directory." -ForegroundColor White
Write-Host ""
Write-Host "Press any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
