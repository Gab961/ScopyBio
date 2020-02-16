# ScopyBio

Le logiciel **ScopyBio** permet de gagner du temps sur vos analyses de mitochondrie. Il met en évidence les zones intéressantes pour vous, et vous permet de les annoter.


# Utilisation
## Windows (Testé sur Windows 7 et 10)
Récupérez l'archive **ScopyBioWindows** située dans le dossier **Exécutable**. Décompressez l'archive, installez les deux installeurs situés dans le dossier **Prérequis**. Vous pouvez alors lancer l'application située dans le dossier **Build/bin/**.
## Linux (Testé sur Ubuntu 16.04 LTS)
Récupérez l'archive **ScopyBioLinux** située dans le dossier **Exécutable**. Décompressez l'archive, et lancez le script bash **Installation.sh**. Vous pouvez alors lancer l'application située dans le dossier **Build/bin/**.
## MacOs (Non testé)
Une version MacOs est théoriquement possible avec les sources, cependant nous n'avons pas pu la produire.

# Développement
## Prérequis
Il faut tout d'abord installer certains composants.
### Cmake
Téléchargeable à l'adresse suivante : [https://cmake.org/](https://cmake.org/)
### Compilateur
Dépendant de votre système d'exploitation:
- Linux : g++
- Windows : MSVC (obtenable en installant Visual Studio)
- MacOs : clang
### Conan
Conan est un package manager téléchargeable ici : [https://conan.io/](https://conan.io/)
## Compilation
Une fois ces éléments installés, ouvrir un terminal

```bash
conan remote add arsen-deps [https://api.bintray.com/conan/arsen-studio/arsen-deps](https://api.bintray.com/conan/arsen-studio/arsen-deps)
conan remote add bincrafters [https://api.bintray.com/conan/bincrafters/public-conan](https://api.bintray.com/conan/bincrafters/public-conan)
```
Créez un dossier **Build** dans les sources de ScopyBio et s'y déplacer via un terminal. Y écrire ensuite:
```bash
conan install .. --build=missing
cmake ..
cmake --build .
```
L'exécutable est alors produit dans Build/bin.

> Note : Sur Ubuntu, il peut être nécessaire de forcer la compilation avec gcc8: 
> conan install .. -s compiler.version=8 --build=missing

> Note : La première commande prend du temps puisqu'elle télécharge automatiquement tout ce qu'il faut pour pouvoir compiler les sources.

> Note : Seule la dernière commande est à réitérer pour compiler après une modification des sources.