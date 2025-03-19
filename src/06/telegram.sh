#!/bin/bash
TOKEN="7879359050:AAFSFOGLGrGeuOTZC5-Fp7_Zlov2j1O0-qw"
CHAT_ID="7574997054"

send_notification() {
    local status_ci=$1
    local status_cd=$2
    local message="Статус СI: $status_ci, Статус CD: status_cd"

    curl -s -X POST \
        "https://api.telegram.org/bot$TOKEN/sendMessage" \
         -F chat_id=$CHAT_ID \
         -F text="$message"
}
send_notification "Успешно" "Успешно"

