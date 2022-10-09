# Stop at first error
$global:ErrorActionPreference = "Stop"

# Init cstpw
$global:CSTPW_SCRIPT_FILE = ".\cstpw.cmd"
. .\cstpw.ps1
Cstpw_CreateScript

# Import setting
. .\recompact.setting.ps1

$compactFolder | ForEach-Object {
    Cstpw_WriteScript ("call compact_folder_exe `"$($PSItem)`" " + $compactAlgorithm)
}

Write-Host "Start recompact folders"
Write-Host "It's now safe to turn off this window"
Cstpw_RunScript -Wait -RunAs
