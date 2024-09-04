# Nom de l'exécutable à générer
TARGET = result

# Compilateur C++
CC = g++

# Options de compilation, par exemple -Wall pour afficher tous les avertissements
#CFLAGS = -Wall

# Fichiers source
SOURCES = ImplicitMethods.cpp ExplicitMethods.cpp Initializer.cpp  main.cpp 

# Convertit les .cpp en .o
OBJECTS = $(SOURCES:.cpp=.o)

# Première règle, celle par défaut, est celle qui est exécutée lorsqu'aucun argument n'est donné à make
all: $(TARGET)

# Lien des fichiers objet pour créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Règle pour créer un fichier objet à partir d'un fichier source
%.o: %.cpp
	$(CC)  -c $< -o $@

# Règle pour nettoyer le projet (supprimer les fichiers objet et l'exécutable)
clean:
	rm -f $(OBJECTS) $(TARGET) *.csv

# Cette ligne est pour éviter des conflits avec des fichiers du même nom que les règles
.PHONY: all clean