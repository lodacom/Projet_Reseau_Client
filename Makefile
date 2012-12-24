Employe: Employe.o sockdist.o sock.o sauvegarde.o
	g++ -o employe Employe.o sockdist.o sock.o sauvegarde.o
    		
sock.o: sock.cpp sock.h
	g++ -c sock.cpp

sockdist.o: sockdist.cpp sockdist.h
	g++ -c sockdist.cpp
	
Employe.o:Employe.cpp Employe.h
	g++ -c Employe.cpp
	
sauvegarde.o:sauvergade.c sauvergade.h
	gcc -c `pkgconfig --cflags --libs gtk+-2.0` sauvegarde.c
