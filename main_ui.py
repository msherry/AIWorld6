import pygame
import time
def clearDisplay(window):
	window.fill((0,0,0))

def getBrainColor(brainString):
	#L1;4:5.4:3;L2;3:4:2,2	
	try:
		parts = brainString.split(';')
		level = 0
		r = 0
		g = 0
		b = 0
		for part in parts:
			if(part == "L1"):
				level = 1
			elif(part == "L2"):
				level = 2
			else:
				conn = part.split(':')
				if(level == 1):
					r += int(conn[0])
					b += int(conn[2])
				elif(level == 2):
					g += int(conn[2])
		r = (r/2)%255
		g = (g/2)%255	
		b = (b/2)%255
		return (r,g,b)
	except:
		return (0,0,0)
def drawAgent(window,xLoc,yLoc,energy,brainString):
	try:
		offset = 300
		s = 3 #We have world size of 100, spacing of 3 is appropriate
		xLoc = int(xLoc)
		yLoc = int(yLoc)
		energy = float(energy)
	except:
		f = open("./displayLog.txt","a")
		print("Failed to render agent x:%s y:%s e:%s\n",xLoc,yLoc,energy)
		f.write("Failed to render agent x:%s y:%s e:%s\n",xLoc,yLoc,energy)
		f.close();	
		return 0;
	size = 1
	if(energy > 10):
		size = 2
	if(energy > 100):
		size = 3
	if(energy > 1000):
		size = 4
	color = getBrainColor(brainString)
	pygame.draw.line(window,color,(offset+s*(xLoc)+size,s*yLoc     ),(offset+s*xLoc-size,s*yLoc     ),1)
	pygame.draw.line(window,color,(offset+s*(xLoc)     ,s*yLoc+size),(offset+s*xLoc     ,s*yLoc-size),1)

def drawWorld(window):
	try:
		f = open("./outputs/world_whichFileToUse.txt")
	except:
		return 0
	s = f.readlines()
	f.close()
	newData = 0
	if(s[0] == 'a'):		
		f = open("./outputs/world_a.txt")
		if(drawWorld.last != 'a'): #We want to tell the drawing function when to save an image
			newData = 1
	else:
		f = open("./outputs/world_b.txt")
		if(drawWorld.last != 'b'):
			newData = 1
	drawWorld.last = s[0]
	x = 0
	y = 0
	e = 0
	bs = ''
	for line in f.readlines():
		pairs = line.split(' ')
		for pair in pairs:
			stat = pair.split(',')
			if(stat[0] == 'xLoc'):
				x = stat[1]
			if(stat[0] == 'yLoc'):
				y = stat[1]
			if(stat[0] == 'energy'):
				e = stat[1]
			if(stat[0] == 'br'):
				bs = stat[1]
		#print("drawing agent %i,%i\n",x,y)
		drawAgent(window,x,y,e,bs)
	f.close()
	return newData
drawWorld.last = 'c'	

def drawStats(window):
	font = pygame.font.Font(None,30)
	i = 0
	statList = getStats()
	if(statList == 0):
		return 0 #In case there's no data to get
	for stat in statList:
		textToDisplay = "%s: %s"%(stat[0].strip(),stat[1].strip()) #You cant use \t here
		sur = font.render(textToDisplay,1,(200,200,10))
		window.blit(sur,(10,10+i*30))
		i = i+1
		
def getStats():
	listOfStats = []
	try:
		f = open("./outputs/monitor_whichFileToUse.txt")
	except:
		return 0;
	s = f.readlines()
	f.close()
	if(s[0] == 'a'):
		f = open("./outputs/monitor_a.txt")
	else:
		f = open("./outputs/monitor_b.txt")
	for line in f.readlines():
		pairs = line.split(',');
		for pair in pairs:
			stat = pair.split(':')
			if(len(stat) >= 2):
				listOfStats.append([stat[0],stat[1]])
	return listOfStats
def saveScreen(window,name):
	pygame.image.save(window,"./images/%04d.png"%name)

if __name__ == '__main__':
        import sys
	displayX = 700
	displayY = 500
        imgNumb = 0
        imgMax = 100
	pygame.init()
	window = pygame.display.set_mode((displayX,displayY))
	#pygame.draw.line(window,(100,100,100),(0,0),(100,100),1)
	pygame.display.flip()
	keepGoing = 1
	while keepGoing == 1:
		time.sleep(0.1)
		clearDisplay(window)
		newData = drawWorld(window)
		drawStats(window)
		pygame.display.flip()	
		if(newData == 1 and imgNumb < imgMax):
			saveScreen(window,imgNumb)
			imgNumb += 1
		for event in pygame.event.get():
			if event.type == pygame.QUIT or event.type == pygame.KEYDOWN:
				keepGoing = 0