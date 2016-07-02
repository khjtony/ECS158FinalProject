import os, sys
from PIL import Image, ImageDraw, ImageFont
from implementation import *

rawImg = Image.open("binaryMaze.png")

def a_star(graph, start, goal):
    frontier = PriorityQueue()
    frontier.put(start, 0)
    cost_so_far = {}
    cost_so_far[start] = 0
    route = []
    
    while not frontier.empty():
        current = frontier.get()
        if current == goal:
            break
        
        for next in graph.neighbors(current):
            new_cost = cost_so_far[current] + graph.cost(current, next)
            if next not in cost_so_far or new_cost < cost_so_far[next]:
                cost_so_far[next] = new_cost
                priority = new_cost + heuristic(goal, next)
                frontier.put(next, priority)

    # return route
    current = goal
    while(current is not start):
        neighborlist = graph.neighbors(current)
        tempdic = {li:cost_so_far[li] for li in neighborlist}
        mindistance = min(tempdic.values())
        for pos in tempdic.keys():
            if (tempdic[pos] == mindistance):
                current = pos
                route.append(current)
                break


    
    return cost_so_far, route




# for x in range(0,100):
#     for y in range(0,100):
#         pix= im.load()
#         print(pix[x,y])


# newimge = []
# for x in range(0,100):
#     for y in range(0,100):
#         newimge.append((x,y,int((x+y)/2),255))
# img = Image.new('RGBA', (100,100))
# img.putdata(newimge)
# os.remove("temp.png")
# img.save("temp.png", 'PNG')

# create raw data structure
(width, height) = rawImg.size
img = rawImg.load()
maze = GridWithWeights(width, height)
for x in range(0, width):
    for y in range(0, height):
        A = img[y,x]
        if (A==0):
            maze.walls.append((y, x))
        maze.weights[(y, x)]=1

cost_so_far, route = a_star_search(maze, (150,10), (180,310))
print(route)
# draw_grid(maze, width=width, point_to=came_from, start=(150,10), goal=(200,310))

# write 0/1 file
# (width, height) = rawImg.size
# newimge = []
# img = Image.new('1', (width, height))
# pix = rawImg.load()
# for x in range(0, width):
#     for y in range(0, height):
#         (R, G, B, A) = pix[y,x]
#         if (R==0):
#             # its wall
#             newimge.append(0)
#         else:
#             newimge.append(1)
# img.putdata(newimge)

# #draw text
# fnt = ImageFont.truetype('Apple Braille.ttf', 16,encoding='unic')
# draw_handler = ImageDraw.Draw(img)
# draw_handler.text((150,10), "Hello", font=fnt, fill=0)
# draw_handler.text((180,310), "Hello", font=fnt, fill=0)


# if(os.path.isfile("temp.png")):
#     os.remove("temp.png")
# img.save("temp.png", 'PNG')
