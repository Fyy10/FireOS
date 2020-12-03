NAME=TestShell

app: TestShell.cpp TestShell.h PCB.cpp PCB.h kernel.cpp kernel.h
	g++ *.cpp -o $(NAME)

run: app
	./TestShell

clean:
	touch $(NAME) && rm $(NAME)
