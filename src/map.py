import importlib
import subprocess


def install(package):
    try:
        importlib.import_module(package)
    except ImportError:
        subprocess.check_call(['pip', 'install', package])


try:
    import pygame
except ImportError:
    install('pygame')
    import pygame


def hex_to_rgb(hex_code):
    hex_code = hex_code.lstrip('#')
    return tuple(int(hex_code[i:i + 2], 16) for i in (0, 2, 4))


pygame.init()

PISO = hex_to_rgb("#353D57")
OBSTACLES = hex_to_rgb("#7F93D1")
CAMINO_INICIO_FIN = hex_to_rgb("#F5F1E3")
INICIO = hex_to_rgb("#C8243A")
FIN = hex_to_rgb("#F3B23B")
VACIO = hex_to_rgb("#13161F")
FONDO = hex_to_rgb("#000000")

colors = {
    "0": PISO,  # PISO
    "+": CAMINO_INICIO_FIN,  # CAMINO_INICIO_FIN
    "-": OBSTACLES,  # OBSTACLES
    "A": INICIO,  # INICIO
    "B": FIN,  # FIN
    " ": VACIO,  # VACIÓ
}

with open("data.txt", "r") as f:
    all_lines = f.readlines()
    data = [list(line.strip('\n')) for line in all_lines[5:]]
    data1 = all_lines[:5]
    for i in range(len(data1)):
        data1[i] = data1[i].strip()

    DFS_BFS_TEXT = data1[0]
    INICIO_TEXT = data1[1][8:]
    FIN_TEXT = data1[2][5:]
    ROWS_TEXT = data1[3][5:]
    COLS_TEXT = data1[4][6:]

    rows = len(data)
    cols = len(data[0])

    square_size = min(600 // rows, 600 // cols)

    grid_width = square_size * cols
    grid_height = square_size * rows

    window_width = grid_width
    window_height = grid_height + 100
    window_size = (window_width, window_height)

    window = pygame.display.set_mode(window_size)
    pygame.display.set_caption(DFS_BFS_TEXT)

    clock = pygame.time.Clock()

    grid_rect = pygame.Rect(0, 0, grid_width, grid_height)
    window.fill(FONDO)  # FONDO de toda la ventana
    pygame.draw.rect(window, FONDO, grid_rect)

    for row in range(rows):
        for col in range(cols):
            # rect = pygame.Rect(col * square_size + 2, row * square_size + 2, square_size - 1, square_size - 1)
            rect = pygame.Rect(col * square_size + 2, row * square_size + 2, square_size - 0.5, square_size - 0.5)
            color = colors[data[row][col]]
            pygame.draw.rect(window, color, rect, border_radius=2)
            # pygame.draw.rect(window, color, rect)

    font = pygame.font.SysFont("Consolas", 30)
    dfs_text = font.render(DFS_BFS_TEXT + ROWS_TEXT + "x" + COLS_TEXT, True, OBSTACLES)
    inicio_text = font.render("A:" + INICIO_TEXT, True, INICIO)
    fin_text = font.render("B:" + FIN_TEXT, True, FIN)

    dfs_rect = dfs_text.get_rect()
    dfs_rect.centerx = (grid_width // 4) - 50
    dfs_rect.centery = (grid_height + 50)

    inicio_rect = inicio_text.get_rect()
    inicio_rect.centerx = (grid_width // 2) - 10
    inicio_rect.centery = grid_height + 50

    fin_rect = fin_text.get_rect()
    fin_rect.centerx = 3 * (grid_width // 4) + 50
    fin_rect.centery = grid_height + 50

    window.blit(dfs_text, dfs_rect)
    window.blit(inicio_text, inicio_rect)
    window.blit(fin_text, fin_rect)

    pygame.display.flip()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                text_img = DFS_BFS_TEXT.replace('*', '').replace(':', '')
                print(text_img)
                pygame.image.save(window, "../img/" + text_img + ".png")
                running = False

        pygame.display.flip()

        clock.tick(60)

    pygame.quit()
