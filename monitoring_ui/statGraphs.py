import pygame
def statGraphs_draw():
	return 0
statGraphs_draw.iterationsSeen = 0
statGraphs_draw.statList = []

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
