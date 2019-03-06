import matplotlib
# Uncomment the line below if working in cs50
# matplotlib.use('agg')
import matplotlib.pyplot as plt
import sys

from math import sin, cos, radians

COLORS = ['#000000', '#0000CC', '#00CC00', '#00CCCC', '#CC0000', '#CC00CC', '#CCCC00']


# Example Fractal
def rec_fun(x, y, length, h, color_idx):
    if h == 0:
        return
    new_color_idx = (color_idx + 1) % len(COLORS)
    
    plt.plot([x,x],[y-length/2,y+length/2], color=COLORS[color_idx])
    plt.plot([x-length/2,x+length/2],[y,y], color=COLORS[color_idx])
    
    rec_fun(x-length/4, y-length/4, length/2, h-1, new_color_idx)
    rec_fun(x-length/4, y+length/4, length/2, h-1, new_color_idx)
    rec_fun(x+length/4, y-length/4, length/2, h-1, new_color_idx)
    rec_fun(x+length/4, y+length/4, length/2, h-1, new_color_idx)


# Fractal For Students
def sierpinski_triangle(x, y, length, h, color_idx):
    if h == 0:
        return
    new_color_idx = (color_idx + 1) % len(COLORS)
    
    sierpinski_triangle(x, y+length/4, length/2, h-1, new_color_idx)
    sierpinski_triangle(x-length/4, y-length/4, length/2, h-1, new_color_idx)
    sierpinski_triangle(x+length/4, y-length/4, length/2, h-1, new_color_idx)
    
    plt.plot([x-length/2, x+length/2], [y-length/2,y-length/2], color=COLORS[color_idx])
    plt.plot([x-length/2, x], [y-length/2, y+length/2], color=COLORS[color_idx])
    plt.plot([x+length/2, x], [y-length/2, y+length/2], color=COLORS[color_idx])


# More Advanced (But Satisfying) Fractal
def snowflake(x, y, length, h):
    if h == 0:
        return
    x1 = cos(radians(60))*length/2
    y1 = sin(radians(60))*length/2
    
    plt.plot([x-length/2, x+length/2], [y, y], color=COLORS[3])
    plt.plot([x-x1, x+x1], [y-y1, y+y1], color=COLORS[3])
    plt.plot([x-x1, x+x1], [y+y1, y-y1], color=COLORS[3])
    
    snowflake(x-2*length/3, y, length/3, h-1)
    snowflake(x+2*length/3, y, length/3, h-1)
    snowflake(x-4/3*x1, y-4/3*y1, length/3, h-1)
    snowflake(x+4/3*x1, y+4/3*y1, length/3, h-1)
    snowflake(x-4/3*x1, y+4/3*y1, length/3, h-1)
    snowflake(x+4/3*x1, y-4/3*y1, length/3, h-1)
    snowflake(x, y, length/3, h-1)


def main():
    if len(sys.argv) < 3:
        print('Invalid arguments', 'Usage: python fractals.py fractal_type iterations', sep='\n')
        exit(1)

    name = 'default'

    if sys.argv[1] == 'r':
        rec_fun(0, 0, 512, int(sys.argv[2]), 0)
        name = 'rectangle'
    elif sys.argv[1] == 's':
        snowflake(0, 0, 512, int(sys.argv[2]))
        name = 'snowflake'
    elif sys.argv[1] == 't':
        sierpinski_triangle(0, 0, 512, int(sys.argv[2]), 0)
        name = 'sierpinski'
    else:
        print('Invalid fractal type', 'Options: r, s, t (for rectangle, snowflake, and sierpinski triangle)', sep='\n')
        exit(2)
    if matplotlib.get_backend().lower() == 'agg':
        plt.savefig(name + '.jpg', bbox_inches='tight')
    else:
        plt.show()


main()
