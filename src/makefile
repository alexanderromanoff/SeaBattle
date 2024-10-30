MyProject : main.o Battleship.o Field.o Ship_Manager.o AbilityManager.o Scaner.o Shelling.o MassiveAttack.o Visitor.o Factory.o
	g++ -o MyProject main.o Battleship.o Field.o Ship_Manager.o AbilityManager.o Scaner.o Shelling.o MassiveAttack.o Visitor.o Factory.o

Battleship.o : Battleship.cpp
	g++ -c Battleship.cpp 
	
Field.o : Field.cpp 
	g++ -c Field.cpp 
	
Ship_Manager.o : Ship_Manager.cpp
	g++ -c Ship_Manager.cpp
	
main.o : main.cpp 
	g++ -c main.cpp 
	
AbilityManager.o: Scaner.o Shelling.o MassiveAttack.o Visitor.o
	g++ -c AbilityManager.cpp

Scaner.o:Scaner.cpp 
	g++ -c Scaner.cpp

MassiveAttack.o:MassiveAttack.cpp 
	g++ -c MassiveAttack.cpp 
	
Shelling.o:Shelling.cpp 
	g++ -c Shelling.cpp 
	
Visitor.o: Scaner.o Shelling.o MassiveAttack.o
	g++ -c Visitor.cpp
Factory.o:
	g++ -c Factory.cpp
	
clean : 
	rm MyProject *.o

