#!/bin/bash

CONFIG_DIR="/etc/openvpn"

# Проверка наличия конфигураций
cd "$CONFIG_DIR" || { echo "Директория $CONFIG_DIR не найдена."; exit 1; }

mapfile -t CONFIGS < <(find . -maxdepth 1 -name "*.ovpn" | sed 's|^\./||')

if [ ${#CONFIGS[@]} -eq 0 ]; then
    echo "Нет .ovpn конфигураций в $CONFIG_DIR"
    exit 1
fi

echo "Выберите конфигурацию для подключения:"
select CONFIG in "${CONFIGS[@]}"; do
    if [[ -n "$CONFIG" ]]; then
        echo "Запуск OpenVPN с конфигурацией: $CONFIG"
        sudo openvpn --daemon --config "$CONFIG"
        echo "VPN запущен в фоне."
        break
    else
        echo "Неверный выбор. Попробуйте снова."
    fi
done

