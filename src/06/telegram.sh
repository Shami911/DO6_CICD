#!/bin/bash
source config.sh
BOT_NAME="ziggsman D06 CI/CD"

send_notification() {
    local status=$1   # Принимаем статус как аргумент
    local stage_name=$2  # Принимаем название этапа как аргумент
    local message="${BOT_NAME}: Этап "${stage_name}" = ${status}"
   
    echo "status: ${status}"
    echo "stage_name: ${stage_name}"
    echo "message: ${message}"

    curl -s -X POST \
        "https://api.telegram.org/bot${TELEGRAM_TOKEN}/sendMessage" \
        -F chat_id=${TELEGRAM_CHAT_ID} \
        -F text="${message}"
}
send_notification "$1" "$2" # Передаем аргументы в send_notification
