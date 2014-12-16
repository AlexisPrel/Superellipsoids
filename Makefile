CC = clang 
CFLAGS = -Wall -g 
LFLAGS = -g 
LIBS = -lgsl -lm 
GRAPH = gnuplot 
BROWSER = google-chrome
FILE = sol
# DIR=/path	#uncomment #8 and #27 for output to be opened effortlessly 
URL = https://github.com/AlexisPrel/Superellipsoids.git


all: mc-volume run-careful graph clean kindword

minima: mc-volume run graph

mc-volume: main.c
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)

run:
	./mc-volume > ${FILE}

run-careful:
	# it is highly recommended to run with lower number of points (e.g. 2^5) when checking memory 
	valgrind --leak-check=yes ./mc-volume > ${FILE} 
		
graph: mc-volume.gpl ${FILE}
	${GRAPH} mc-volume.gpl
#	${BROWSER} ${DIR}/mc-volume.png
    
git-first:
	touch README.md
	git init
	git add .
	git commit -m 'First commit'
	git remote add origin ${URL}
	# Done initialization
	make git-update
	
git-update:
	# Please make sure you have updated README.md
	indent *.c
	git push origin master
	
clean:
	rm -f *.o *~ mc-volume

kindword:
	# Have super great vacations! I will miss you.
