import pygame
import time
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

def worldMaps_draw(window,xOffset,yOffset,version):
	try:
		if(version == 'a'):
			f = open("./data_from_simulations/world_agents_a.txt")
		elif(version == 'b'):
			f = open("./data_from_simulations/world_agents_b.txt")
		else:
			return 0
	except:
		return 0
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

