import os, sys
from PIL import Image, ImageDraw

fname = "binaryMaze"

rawImg = Image.open(fname+'.png')
if(os.path.isfile(fname+'.txt')):
    os.remove(fname+".txt")
output = open(fname+'.txt', 'w')


(width, height)=rawImg.size
output.write(str(width)+' '+str(height)+'\n')
pix = rawImg.load()
for x in range(0,width):
    for y in range(0, height):
        output.write(str( 1 if pix[y, x]>0 else 0)+'\n')

output.close()
