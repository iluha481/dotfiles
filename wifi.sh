#!/bin/bash

# Конфигурация - задайте здесь параметры домашней сети
HOME_SSID="GamnoAshota"
HOME_PASS="Menyane666"

input="$1"

if [[ "$input" == "home" ]]; then
    # Подключение к домашней сети
    echo "Подключаемся к домашней сети $HOME_SSID..."
    nmcli d wifi connect "$HOME_SSID" password "$HOME_PASS"
elif [[ "$input" == "-l" || "$input" == "--list" ]]; then 
    nmcli d wifi list
elif [[ "$input" == "-c" || "$input" == "--connect" ]]; then 
    # Подключение с ручным вводом параметров
    if [ $# -lt 3 ]; then
        echo "Ошибка: для подключения укажите SSID и пароль"
        echo "Пример: $0 -c SSID password"
        exit 1
    fi
    input_SSID="$2"
    input_pass="$3"
    nmcli d wifi connect "$input_SSID" password "$input_pass"
elif [[ "$input" == "-ch" || "$input" == "--change" ]]; then 
    if [ $# -lt 2 ]; then
        echo "Ошибка: укажите SSID для подключения"
        echo "Пример: $0 -ch SSID"
        exit 1
    fi
    input_SSID="$2"
    nmcli connection up "$input_SSID"
else
    echo "Использование:"
    echo "  $0 home                       - подключиться к домашней сети"
    echo "  $0 [-l|--list]                - список доступных сетей"
    echo "  $0 [-c|--connect <SSID> <password>] - подключиться к указанной сети"
    echo "  $0 [-ch|--change <SSID>]      - переключиться на сохранённое подключение"
    exit 1
fi
