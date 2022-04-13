from PIL import Image
from numpy import*

temp=asarray(Image.open('game bg.png'))
x=temp.shape[0]
y=temp.shape[1]*temp.shape[2]

print(temp)

temp.resize((x,y)) # a 2D array

print(temp[0][:4])
g_y = 0
y = 0
x = 0
#print(len(temp))
with open('map.txt', 'w') as file:
    file.truncate(0)
while g_y < len(temp):
    y = temp[g_y]
    #print('len y', len(y))
    g_x = 0
    res = ''
    while g_x < len(y):
        x = y[g_x:g_x + 3].tolist()
        #print(x)
        match x:
            case [158, 94, 73]:
                res += ' B '
            case [84, 75, 62]:
                res += ' W '
            case [130, 251, 87]:
                res += ' D '
            case _:
                res += ' - '

        g_x += 60 * 4

    with open('map.txt', 'a') as file:
        file.write(res + '\n')
    #print( res)
    g_y += 60
