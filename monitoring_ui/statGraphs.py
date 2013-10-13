import pygame
import time
def clearDisplay(window):
	window.fill((0,0,0))

def drawTerrain(window,xOffset,yOffset):
	print "did nothing to draw terrain"

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

def drawAgentDecision(window,x,y,xOffset,yOffset,size,d):
	color = (0,0,0)
	if(d >= 0 and d <= 2):
		color = (0,0,255)
	if(d >= 3 and d <= 4):
		color = (0,125,255)
	if(d == 5):
		color = (255,0,0)
	if(d >= 6 and d <= 7):
		color = (255,0,255)
	if(d == 8):
		color = (0,255,0)
	pygame.draw.rect(window,color,(x*size+xOffset,y*size+yOffset,size,size))		
#define AG_M_F 0 
#define AG_M_L 1
#define AG_M_R 2
#define AG_T_L 3
#define AG_T_R 4
#define AG_A_F 5
#define AG_R   6
#define AG_R_F 7
#define AG_GROW 8

def drawAgentEnergy(window,x,y,xOffset,yOffset,size,e):
	#Want to increase in color from green to red as they get stronger (red:255,0,0 green:0,255,0)
	if(e < 1000): #All Red-to-yellow ratio
		r = 255
		g = e/1000*255
		b = 0
	elif(e < 10000):
		r = e/10000*255
		g = 255
		b = 0
	elif(e < 100000):
		r = 255
		g = 255
		b = e/100000*255
	else:
		r = 255
		g = 255
		b = 255
	pygame.draw.rect(window,(r,g,b),(x*size+xOffset,y*size+yOffset,size,size))		

def drawAgentBrain(window,xLoc,yLoc,xOffset,yOffset,size,brainString):
	color = getBrainColor(brainString)
	pygame.draw.rect(window,color,(xLoc*size+xOffset,yLoc*size+yOffset,size,size))
	#pygame.draw.line(window,color,(offset+s*(xLoc)+size,s*yLoc     ),(offset+s*xLoc-size,s*yLoc     ),1)
	#pygame.draw.line(window,color,(offset+s*(xLoc)     ,s*yLoc+size),(offset+s*xLoc     ,s*yLoc-size),1)
def getAgentData(line):
 	try:
		pairs = line.split(' ')
		for pair in pairs:
			stat = pair.split(',')
			if(stat[0] == 'xLoc'):
				x = int(stat[1])
			if(stat[0] == 'yLoc'):
				y = int(stat[1])
			if(stat[0] == 'energy'): 
				e = float(stat[1])
			if(stat[0] == 'latestDecision'):
				ld = int(stat[1])
			if(stat[0] == 'br'):
				bs = stat[1]
		return [x,y,e,ld,bs]
	except:
		print "Failed to understand agent"
		return [-1,-1,-1,-1,-1]

def drawWorld(window,xOffset,yOffset):
	try:
		f = open("./outputs/world_whichFileToUse.txt")
		s = f.readlines()
		f.close()
		if(s[0] == 'a'):
			if(drawWorld.last == 'a'): #We want to tell the drawing function when to save an image
				return 0
			f = open("./outputs/world_agents_a.txt")
		elif(s[0] == 'b'):
			if(drawWorld.last == 'b'):
				return 0
			f = open("./outputs/world_agents_b.txt")
	except:
		return 0
	drawWorld.last = s[0]
	clearDisplay(window)
	drawTerrain(window,xOffset+300,yOffset+340)
	for line in f.readlines():
		x,y,e,ld,bs = getAgentData(line)
		drawAgentBrain(window,x,y,xOffset,yOffset+30,3,bs)
		drawAgentEnergy(window,x,y,xOffset,yOffset+350,3,e)
		drawAgentDecision(window,x,y,xOffset+300,yOffset+30,3,ld)
	font = pygame.font.Font(None,25)
	label = "Hash of agent's neural network"
	sur = font.render(label,1,(150,150,150));
	window.blit(sur,(xOffset,yOffset+10))
	label = "Agent's energy"
	sur = font.render(label,1,(150,150,150));
	window.blit(sur,(xOffset,yOffset+330))
	label = "Agent's last decision"
	sur = font.render(label,1,(150,150,150));
	window.blit(sur,(xOffset+300,yOffset+10))
	label = "Decision color key:"
	sur = font.render(label,1,(150,150,150));
	window.blit(sur,(xOffset+380,yOffset+330))
	label = "Moving/Turning"
	sur = font.render(label,1,(0,0,255));
	window.blit(sur,(xOffset+400,yOffset+350))
	label = "Growing"
	sur = font.render(label,1,(0,255,0));
	window.blit(sur,(xOffset+400,yOffset+370))
	label = "Attacking"
	sur = font.render(label,1,(255,0,0));
	window.blit(sur,(xOffset+400,yOffset+390))
	label = "Replicating"
	sur = font.render(label,1,(255,0,255));
	window.blit(sur,(xOffset+400,yOffset+410))
	
	return 1
drawWorld.last = 'c'	

def drawStats(window):
	font = pygame.font.SysFont(None,30)
	i = 0
	statList = getStats()
	if(statList == 0):
		return 0 #In case there's no data to get
	for stat in statList:
		textToDisplay = "%s: %s"%(stat[0].strip(),stat[1].strip()) #You cant use \t here
		sur = font.render(textToDisplay,1,(150,150,150))
		window.blit(sur,(10,10+i*30))
		i = i+1
		
def getStats():
	try:
		listOfStats = []
		f = open("./outputs/monitor.txt")
		line = list(f)[-1] #We only want the last line
		pairs = line.split(' ');
		for pair in pairs:
			stat = pair.split(',')
			if(len(stat) >= 2):
				listOfStats.append([stat[0],stat[1]])
		return listOfStats
	except:
		return 0 #The file might be corrupt because we're in the middle of reading it. That's ok, we'll just wait.
def saveScreen(window,name):
	pygame.image.save(window,"./images/%04d.png"%name)

if __name__ == '__main__':
        import sys
	displayX = 900
	displayY = 650
        imgNumb = 0
        imgMax = 1000
	pygame.init()
	window = pygame.display.set_mode((displayX,displayY))
	#pygame.draw.line(window,(100,100,100),(0,0),(100,100),1)
	pygame.display.flip()
	keepGoing = 1
	while keepGoing == 1:
		time.sleep(0.3)
		newData = drawWorld(window,300,0) #Draw world will clear the display if needed
		if(newData == 1 and imgNumb < imgMax):
			drawStats(window)
			pygame.display.flip()	
			saveScreen(window,imgNumb)
			imgNumb += 1
		for event in pygame.event.get():
			if event.type == pygame.QUIT or event.type == pygame.KEYDOWN:
				keepGoing = 0
