#!/bin/bash

BLUE = '\033[0;34m' 
RED = "\033[0;31m"
GREEN = '\033[0;32m'
NC = '\033[0m' # No Color


pio_env1 = "standalone"
pio_env2 = "tx"
pio_env3 = "rx"
 
clean_workspace {} {
    junk = (
        ".\.pio\"
        ".\.vscode\" 
        ".\.gitignore"
    )
 
    for item in ${junk[@]}; do
        rm -rf $item
    done
}
 
function upload {
 
    Clear-Host
    $device = Read-Host -Prompt "Upload to Standdalone, TX board, or RX board? [1/2/3] >"
 
    if ($device -eq "1") {
        pio run -t upload -e $pio_env1
    } elseif ($device -eq "2") {
            pio run -t upload -e $pio_env2
    } else {
        Write-Host "Invalid device selection" -fore red
        init
    }
 
}
 
build () {
    Clear
    print "Checking 4 bugs..." -fore green
    pio run
}
function init {
 
    $up = Read-Host -Prompt "Just Build (b) or Upload to Device (u) [b/u] >"
    if ($up -eq "u") {
        upload
    } elseif ($up -eq "b") {
        build
    } else {
        Write-Host "Invalid option" -fore red
    }
}
 
clean_workspace
init