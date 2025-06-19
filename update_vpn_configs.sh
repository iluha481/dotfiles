#!/bin/bash

CONFIG_DIR="/etc/openvpn"
ZIP_FILE="$1"

if [[ -z "$ZIP_FILE" ]]; then
    echo "Использование: $0 путь_к_zip_файлу"
    exit 1
fi

if [[ ! -f "$ZIP_FILE" ]]; then
    echo "Файл $ZIP_FILE не найден."
    exit 1
fi

echo "Удаление старых конфигураций в $CONFIG_DIR..."
sudo find "$CONFIG_DIR" -type f -name "*.ovpn" -delete

echo "Распаковка нового архива конфигураций..."
sudo unzip -o "$ZIP_FILE" -d "$CONFIG_DIR"

echo "Готово. Конфигурации обновлены."

