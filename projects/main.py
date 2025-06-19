import os

def count_lines_in_file(file_path):
    """Подсчитывает количество строк в указанном файле."""
    with open(file_path, 'r', encoding='utf-8') as file:
        return sum(1 for line in file)

def count_go_lines(directory):
    """Рекурсивно подсчитывает строки во всех .go файлах в указанной директории."""
    total_lines = 0
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.go'):
                file_path = os.path.join(root, file)
                lines = count_lines_in_file(file_path)
                total_lines += lines
                print(f"{file_path}: {lines} строк")
    return total_lines

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) != 2:
        print("Использование: python count_go_lines.py <директория>")
        sys.exit(1)
    
    directory = sys.argv[1]
    if not os.path.isdir(directory):
        print(f"Ошибка: '{directory}' не является директорией или не существует")
        sys.exit(1)
    
    print(f"Поиск .go файлов в директории: {directory}")
    total = count_go_lines(directory)
    print(f"\nОбщее количество строк в .go файлах: {total}")