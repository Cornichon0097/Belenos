# Belenos

Selon Wikipédia, Bélénos est le dieu gaulois de la jeunesse, l’harmonie, la
beauté, l’intuition, l’invention et du raisonnement ; tout ce que représente
cette bibliothèque graphique finalement...

## Organisation du code

Le code de Bélénos est principalement contenu dans le répertoire [lib](./lib).
Les fichiers C se trouvent dans le sous-répertoire [src](./lib/src) et les
fichiers d’en-tête dans le sous-répertoire [include](./lib/include). Les
fichiers d’en-tête pour Bélénos se trouvent dans le répertoire
[belenos](./lib/include/belenos). Chaque fichier C est associé à un fichier
d’en-tête du même nom.

Le répertoire [test](./test) contient plusieurs programme en C qui peuvent être
exécutés et servent à tester les fonctionnolatiés de Bélénos.

Le répertoire [util](./util) contient des utilitaires qui génèrent des fichiers
par exemple.

Le répertoire [res](./res) contient les ressources de Bélénos, utilisées par
la bibliothèque elle-même ou bien par les outils présents dans le répertoire
[res](./res).

## Compilation et exécution

Bélénos peut être compilée grâce au Makefile présent à la racine du projet. Ce
Makefile est en réalité une interface qui lance le véritable outil de
compilation, à savoir CMake. CMake utilise les fichiers CMakeLists.txt présents
dans différents répertoires pour compiler la bibliothèque. Il est possible de
modifier le fichier à exécuter en modifiant le nom de fichier présent dans
[ce fichier CMakeLists](./test/CMakeLists.txt).

```sh
cmake_minimum_required(VERSION 3.16.3)

project(start)

# Main example.
add_executable(${PROJECT_NAME} file.c) # Subsitute file.c by your own file.
target_link_libraries(${PROJECT_NAME} PUBLIC libbelenos)
```

Attention : le fichier doit se trouver dans le répertoire [test](./test).

Une fois le fichier de test choisi, la commande `make` lancera la compilation.
Enfin, pour exécuter le programme, la commande `make run` est à utiliser.
