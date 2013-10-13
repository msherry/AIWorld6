import pygame
import time

def statList_draw(window,xLoc,yLoc):
	font = pygame.font.SysFont(None,30)
	i = 0
	statList = getStats()
	if(statList == 0):
		return 0 #In case there's no data to get
	for stat in statList:
		textToDisplay = "%s: %s"%(stat[0].strip(),stat[1].strip()) #You cant use \t here
		sur = font.render(textToDisplay,1,(150,150,150))
		window.blit(sur,(xLoc,yLoc+i*30))
		i = i+1
		
def getStats():
	try:
		listOfStats = []
		f = open("./data_from_simulations/monitor.txt")
		line = list(f)[-1] #We only want the last line
		pairs = line.split(' ');
		for pair in pairs:
			stat = pair.split(',')
			if(len(stat) >= 2):
				listOfStats.append([stat[0],stat[1]])
		return listOfStats
	except:
		print "I'm not finding it..."
		return 0 #The file might be corrupt because we're in the middle of reading it. That's ok, we'll just wait.
