import pygame
def statGraphs_draw(window,x,y,xSize,ySize):
	stats = ['aveEnergy','attacks','replications']
	for i in range(0,len(stats)):
		statGraphs_drawAGraph(window,stats[i],x,y+i*ySize/len(stats),xSize,ySize/len(stats))
	return 0
statGraphs_draw.iterationsSeen = 0
statGraphs_draw.statList = []

def statGraphs_drawAGraph(window,stat,x,y,xSize,ySize):
	font = pygame.font.SysFont(None,20)
	sur = font.render(stat,1,(150,150,150))
	window.blit(sur,(x,y))	

def saveStats(statList):
	statGraphs_draw.statList.append({})
	for stat in statList:	
		try:	
			if(stat[0] != "time"):
				statGraphs_draw.statList[statGraphs_draw.iterationsSeen][stat[0]] = float(stat[1])
		except:
			print "Wasn't able to save the stat '%s'"%stat[0]
			statGraphs_draw.statList[statGraphs_draw.iterationsSeen][stat[0]] = -99
	statGraphs_draw.iterationsSeen += 1
	#Input is a list of pairs
	return 0
