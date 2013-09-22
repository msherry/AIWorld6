import pygame
import time
def clearDisplay(window):
	window.fill((0,0,0))
def drawStats(window):
	clearDisplay(window)
	font = pygame.font.Font(None,30)
	i = 0
	statList = getStats()
	for stat in statList:
		textToDisplay = "%s: %s"%(stat[0].strip(),stat[1].strip())
		sur = font.render(textToDisplay,1,(200,200,10))
		window.blit(sur,(10,10+i*30))
		i = i+1
	pygame.display.flip()	
		
def getStats():
	listOfStats = []
	f = open("./outputs/monitor.txt")
	for line in f.readlines():
		pairs = line.split(',');
		for pair in pairs:
			stat = pair.split(':')
			if(len(stat) >= 2):
				listOfStats.append([stat[0],stat[1]])
	return listOfStats
def saveScreen(name):
	print "Hello"
	#pygame.image.save(self.window,"./images/%s.png"%name)

if __name__ == '__main__':
        import sys
	displayX = 640
	displayY = 480
	pygame.init()
	window = pygame.display.set_mode((displayX,displayY))
	#pygame.draw.line(window,(100,100,100),(0,0),(100,100),1)
	pygame.display.flip()
	keepGoing = 1
	while keepGoing == 1:
		time.sleep(1)
		drawStats(window)
		for event in pygame.event.get():
			if event.type == pygame.QUIT or event.type == pygame.KEYDOWN:
				keepGoing = 0
