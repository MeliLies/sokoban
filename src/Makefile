CXX=g++
CXXFLAGS += -std='c++20' -Werror -Wall -Wextra -pedantic
CXXLIBS += -lfltk

main: main.cpp
	make View -B
	make Controller -B
	make Model -B
	make clean
	${CXX} ${CXXFLAGS} -o main main.cpp Model/obj.o View/obj.o Controller/obj.o ${CXXLIBS} || make rm
	make clean
	make rm_obj



Controller: Controller/MainWindowController.cpp Controller/GameController.cpp Controller/EndGameWindowController.cpp
	${CXX} ${CXXFLAGS} -c Controller/GameController.cpp ${CXXLIBS}
	${CXX} ${CXXFLAGS} -c Controller/MainWindowController.cpp ${CXXLIBS}
	${CXX} ${CXXFLAGS} -c Controller/EndGameWindowController.cpp ${CXXLIBS}
	ld -o Controller/obj.o -r MainWindowController.o GameController.o EndGameWindowController.o

View: View/MainWindowView.cpp View/GameView.cpp View/widgets/Box.cpp View/widgets/Cell.cpp View/EndGameWindowView.cpp
	${CXX} ${CXXFLAGS} -c View/MainWindowView.cpp ${CXXLIBS}
	${CXX} ${CXXFLAGS} -c View/GameView.cpp ${CXXLIBS}
	${CXX} ${CXXFLAGS} -c View/EndGameWindowView.cpp ${CXXLIBS}
	${CXX} ${CXXFLAGS} -c View/widgets/Box.cpp ${CXXLIBS}
	${CXX} ${CXXFLAGS} -c View/widgets/Cell.cpp ${CXXLIBS}
	ld -o View/obj.o -r MainWindowView.o GameView.o EndGameWindowView.o Box.o Cell.o

Model: Model/Board.cpp
	${CXX} ${CXXFLAGS} -c Model/Board.cpp ${CXXLIBS}
	ld -o Model/obj.o -r Board.o

clean:
	rm *.o || echo -n ""

rm_obj:
	rm */obj.o || echo -n ""
	
fclean:
	make clean
	make rm_obj
	rm main || echo -n ""