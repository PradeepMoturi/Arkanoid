import random
import sys

start_x=110
start_y=150
bheight=20
bwidth=80

cnt=[]

cnt.append(int(sys.argv[1])) #Normal
cnt.append(int(sys.argv[2])) #multiple
cnt.append(int(sys.argv[3])) #increase
cnt.append(int(sys.argv[4])) #decrease
cnt.append(int(sys.argv[5])) #fire ball

# hits=1 for normal bricks

# hits=2 for stron bricks

for i in range(0,9):
  hits=1
  power = 1
  temp_x=start_x
  temp_y=start_y
  for j in range(0,6):
    if (j==0 or j==5):
      hits=2
    else :
      hits=1
    x=random.randint(1,10)
    x=x%5
    while(cnt[x]==0):
        x=(x+1)%4
    cnt[x]=cnt[x]-1
    print(x,hits,temp_x,temp_y)
    temp_x+=bwidth
  start_y+=bheight