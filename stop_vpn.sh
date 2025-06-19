#!/bin/bash

# Ищем процессы openvpn
VPN_PIDS=$(pgrep openvpn)

if [[ -z "$VPN_PIDS" ]]; then
    echo "OpenVPN не запущен."
    exit 0
fi

echo "Завершаем процессы OpenVPN..."
sudo kill $VPN_PIDS

echo "VPN отключён."

