import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.path import Path

def draw_rect(base, size):
    verts = [
        (base[1], base[0]), # left, bottom
        (base[1], base[0] + size[0]), # left, top
        (base[1] + size[1], base[0] + size[0]), # right, top
        (base[1] + size[1], base[0]), # right, bottom
        (0., 0.), # ignored
        ]

    codes = [Path.MOVETO,
             Path.LINETO,
             Path.LINETO,
             Path.LINETO,
             Path.CLOSEPOLY,
             ]

    path = Path(verts, codes)

    return path

def set_ticks_and_grid(ax, m, n):
    major_ticks = list(range(0, max(m,n), 5))
    minor_ticks = list(range(0, max(m,n), 1))

    ax.set_xticks(major_ticks)
    ax.set_xticks(minor_ticks, minor=True)
    ax.set_yticks(major_ticks)
    ax.set_yticks(minor_ticks, minor=True)
    ax.set_xlabel('y')
    ax.set_ylabel('x')

    ax.grid(which='minor', alpha=0.7)
    ax.grid(which='major', alpha=1)

    ax.set_xlim(-1,m + 1)
    ax.set_ylim(-1,n + 1)

    ax.set_aspect('equal', adjustable='box')

def show_solution(inp, out):
    k = int(inp[0].strip())
    m = int(inp[1].strip())
    n = int(inp[2].strip())
    rect = [list(map(int, l.strip().split(" "))) for l in inp[3:]]
    rect = {x[0]:x[1:] for x in rect}

    places = [list(map(int, l.strip().split(" "))) for l in out]

    fig = plt.figure()
    ax = fig.add_subplot(111)

    set_ticks_and_grid(ax, m, n)

    # Ajouter le fond (grand rectangle)
    ax.add_patch(patches.PathPatch(draw_rect([0,0],[n,m]), facecolor='lightgrey', lw=2))

    for (id, h, w) in places:
        base_h, base_w = rect[id]
        pa = patches.PathPatch(draw_rect([h, w],[base_h, base_w]), facecolor='red', lw=2, alpha=0.4)
        ax.add_patch(pa)
        ax.text(w + 0.2, h + 0.2, str(id), fontsize=10)

    plt.show()

def show_solution_swap(inp, out):
    k = int(inp[0].strip())
    m = int(inp[1].strip())
    n = int(inp[2].strip())
    rect = [list(map(int, l.strip().split(" "))) for l in inp[3:]]
    rect = {x[0]:x[1:] for x in rect}

    places = [list(map(int, l.strip().split(" "))) for l in out]

    fig = plt.figure()
    ax = fig.add_subplot(111)

    set_ticks_and_grid(ax, m, n)

    # Ajouter le fond (grand rectangle)
    ax.add_patch(patches.PathPatch(draw_rect([0,0],[n,m]), facecolor='lightgrey', lw=2))

    for (id, h, w, swap) in places:
        if int(swap):
            base_w, base_h = rect[id]
            color = 'blue'
        else:
            base_h, base_w = rect[id]
            color = 'red'

        pa = patches.PathPatch(draw_rect([h, w],[base_h, base_w]), facecolor=color, lw=2, alpha=0.4)
        ax.add_patch(pa)
        ax.text(w + 0.2, h + 0.2, str(id), fontsize=10)

    plt.show()


def show_solution_3D(inp, out):
    k = int(inp[0].strip())
    m = int(inp[1].strip())
    n = int(inp[2].strip())
    o = int(inp[3].strip())
    rect = [list(map(int, l.strip().split(" "))) for l in inp[4:]]
    rect = {x[0]:x[1:] for x in rect}

    places = [list(map(int, l.strip().split(" "))) for l in out]

    fig, axes = plt.subplots(1, o)

    for couche, ax in zip(range(o), axes):
        set_ticks_and_grid(ax, m, n)

        # Ajouter le fond (grand rectangle)
        ax.add_patch(patches.PathPatch(draw_rect([0,0],[n,m]), facecolor='lightgrey', lw=2))

        for (id, h, w, p) in places:
            base_h, base_w, base_p = rect[id]
            if p <= couche < p+base_p:
                pa = patches.PathPatch(draw_rect([h, w],[base_h, base_w]), facecolor='red', lw=2, alpha=0.4)
                ax.add_patch(pa)
                ax.text(w + 0.2, h + 0.2, str(id), fontsize=10)

        ax.set_title("Couche z %i" %couche)

    plt.show()


import subprocess

def call(inp, arg):
    ret = subprocess.check_output(["../solver"] + arg.split(" "), universal_newlines=True, input=open(inp).read())
    out = "\n".join(filter(lambda x: not (x.startswith("|") or x.startswith("=")), ret.split("\n")))
    out = out.replace("  ", " ").replace("  ", " ").replace("  ", " ").replace("  ", " ").split("\n")
    out = list(filter(lambda x: x.strip() != "",map(lambda x: x.strip(), out)))

    inp = open(inp).read().replace("  ", " ").replace("  ", " ").replace("  ", " ").replace("  ", " ").split("\n")
    inp = list(filter(lambda x: x.strip() != "",map(lambda x: x.strip(), inp)))

    return inp, out
