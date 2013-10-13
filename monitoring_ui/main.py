import pygame
import time
import worldMaps
import statList
def clearDisplay(window):
	window.fill((0,0,0))

def checkDataVersion():
	try:
		f = open("./data_from_simulations/world_whichFileToUse.txt")
		s = f.readlines()
		f.close()
		if(s[0] == checkDataVersion.lastVersion):
			return 'x'
		else:
			checkDataVersion.lastVersion = s[0];
			return s[0]
        except:
                return 'x'
checkDataVersion.lastVersion = 'c';

def saveScreen(window,name):
	pygame.image.save(window,"./images_and_video/%04d.png"%name)

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
		version = checkDataVersion()
		if(version != 'x'):
			clearDisplay(window)
			statList.statList_draw(window,10,10)
			worldMaps.worldMaps_draw(window,300,0,version) #Draw world will clear the display if needed
			pygame.display.flip()	
			if(imgNumb < imgMax):
				saveScreen(window,imgNumb)
				imgNumb += 1
		for event in pygame.event.get():
			if event.type == pygame.QUIT or event.type == pygame.KEYDOWN:
				keepGoing = 0
