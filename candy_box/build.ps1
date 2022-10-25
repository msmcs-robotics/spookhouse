$pio_env1 = "standalone"
$pio_env2 = "tx"
$pio_env3 = "rx"
 
function clean_workspace {
    $junk = @(
        ".\.pio\"
        ".\.vscode\" 
        ".\.gitignore"
    )
 
    foreach($item in $junk) {
        Remove-Item -Recurse -Force $item -ErrorAction SilentlyContinue
    }
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
 
function build {
    Clear-Host
    Write-Host "Checking 4 bugs..." -fore green
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