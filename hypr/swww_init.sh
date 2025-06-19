#!/bin/bash
# Ждём доступности Wayland
while [ -z "$WAYLAND_DISPLAY" ]; do
    sleep 0.1
done

# Инициализируем swww
swww init && sleep 0.5 && swww img ~/Pictures/hyprland/1.jpg
