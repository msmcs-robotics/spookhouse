#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

env1 = "lady"

files_to_clean=(".pio", ".vscode", ".gitignore")

function clean {
    printf "${YELLOW}[-] Cleaning UP...${NC}\n"
    for file in "${files_to_clean[@]}"; do
        rm -rf $file 2>/dev/null
    done
}

function build {
    read -p "Build (b), Upload (u): " choice1
    if [ "$choice1" = "b" ]; then
    
        printf "\n${GREEN}[+] Building...${NC}\n"
        pio run
    elif [ "$choice1" = "u" ]; then
        read -p "Upload to ${env1} (1) or another (2) (1/2): " choice2
        if [ "$choice2" = "1" ]; then
            printf "\n${GREEN}[+] Uploading to ${env1}...${NC}\n"
            pio run -t upload -e $choice2
        fi
    else
        echo "Invalid input..."
    fi
}

clean
build