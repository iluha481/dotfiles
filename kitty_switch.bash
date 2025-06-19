#!/bin/bash
# Улучшенный скрипт переключения тем Kitty

CONFIG_DIR="$HOME/.config/kitty"
THEMES_DIR="$CONFIG_DIR/themes"
CURRENT_THEME_FILE="$CONFIG_DIR/current-theme"

# Список тем для ротации
THEMES=(
    "Dimmed Monokai"
    "catppuccin-frappe"
    "catppuccin-latte"
)

# Инициализация при первом запуске
if [ ! -f "$CURRENT_THEME_FILE" ]; then
    echo "0" > "$CURRENT_THEME_FILE"
fi

# Получаем следующую тему
CURRENT_INDEX=$(<"$CURRENT_THEME_FILE")
NEXT_INDEX=$(( (CURRENT_INDEX + 1) % ${#THEMES[@]} ))
NEXT_THEME="${THEMES[$NEXT_INDEX]}"
THEME_FILE="$THEMES_DIR/${NEXT_THEME}.conf"

# Проверка существования темы
if [ ! -f "$THEME_FILE" ]; then
    echo "Error: Theme file not found: $THEME_FILE" >&2
    exit 1
fi

# 1. Обновляем конфиг Kitty
sed -i "s|^include .*|include themes/${NEXT_THEME}.conf|" "$CONFIG_DIR/kitty.conf"

# 2. Применяем тему (3 разных метода для надежности)
{
    # Метод 1: Через kitten (основной)
    kitten themes --reload-in=all "$NEXT_THEME" 2>/dev/null
    
    # Метод 2: Через kitty @ (если есть открытые окна)
    for socket in /tmp/kitty-*; do
        kitty @ --to "unix:$socket" set-colors -a -c "$THEME_FILE" 2>/dev/null
    done
    
    # Метод 3: Для новых окон
    cp "$THEME_FILE" "$CONFIG_DIR/current-theme.conf"
} | grep -v "Failed"

# 3. Сохраняем индекс темы
echo "$NEXT_INDEX" > "$CURRENT_THEME_FILE"

# Уведомление
notify-send "Kitty Theme" "Applied: $NEXT_THEME" -t 2000 2>/dev/null
