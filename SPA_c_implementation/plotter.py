import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import io
from date_list_generator import m
from PIL import Image

def fig2img(fig):
    buf = io.BytesIO()
    fig.savefig(buf)
    buf.seek(0)
    img = Image.open(buf)
    return img

d2r = np.pi/180
r0 = 0.95

with open("./outputs/plot_list.txt") as file:
    lines = [line.rstrip() for line in file]

print(lines)

for line in lines:
    plot_data = pd.read_csv(line)

    thetas = plot_data['theta']
    rs = plot_data['r']
    plt.polar(thetas*d2r, rs-r0)
    plt.show()

print("here")
fig = plt.gcf()
img = fig2img(fig)
img.save('./outputs/Plot_image.png')