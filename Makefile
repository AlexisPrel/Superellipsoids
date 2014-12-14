CC = clang
#valgrind --leak-check=yes 
CFLAGS = -Wall -O0 
LFLAGS = -O0 
LIBS = -lgsl -lm 
GRAPH = gnuplot 
BROWSER = google-chrome
FILE = sol
dir = /home/jharvard/projects/final/1
#/path/to/dir/		#uncomment this line and line 18 if you want the output to be opened effortlessly 
URL = https://github.com/AlexisPrel/Superellipsoids.git

run: mc-volume graph clean kindword

mc-volume: main.c 
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)
	./mc-volume > ${FILE} 
	
graph: mc-volume.gpl ${FILE}
	${GRAPH} mc-volume.gpl
	${BROWSER} ${dir}/mc-volume.png
    
git-first:
	touch README.md
	git init
	git add .
	git commit -m 'First commit'
	git remote add origin ${URL}
	# Done initialization
	git-update
	
git-update:
	# Please make sure you have updated README.md
	indent *.c
	git push origin master
	
clean:
	rm -f *.o *~ mc-volume

kindword:
	# Have super great vacations! I will miss you.
