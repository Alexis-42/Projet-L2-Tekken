Jeu vidéo réalisé dans le cadre des séances de projets en deuxième année de license informatique.

<br>
  <ol>
    <li><a href="#Description"> Description</a></li>
    <li>
      <a href="#Getting Started"> Getting Started</a>
      <ul>
        <li><a href="#Dépendances">Dépendances</a></li>
        <li><a href="#Installation">Installation</a></li>
        <li><a href="#Les commandes make">Les commandes make</a></li>
      </ul>    
    </li>
    <li><a href="#Auteurs"> Auteurs</a></li>
  </ol>
<br>

<h2 id="Description" style="font-size:30px;"> Description</h2>


Ce jeu est inspiré du jeu de combat Tekken. Le but est d'affronter un adversaire, contre l'ordinateur ou en local avec un deuxième joueur.
Il y a le choix entre 4 personnages : Pingu, Shrek, Goku ou encore Mickey
Ainsi qu'une large sélection de cartes disponibles !

<br>

  <h3 style="font-size:30px;">Images du jeu</h3>
  <br>
  Menu Principal
  <img src="https://i.imgur.com/qOcWqAP.png">
  <br>
  Menu Selection
  <img src="https://i.imgur.com/V0lWfN0.png">
  <br>
  Shrek vs Pingu
  <img src="https://i.imgur.com/wGNt3LI.png">
  <br>
  Goku vs Mickey
  <img src="https://i.imgur.com/TKdgWhJ.png">


<br>

<h2 id="Getting Started" style="font-size:30px;"> Getting Started</h2>


<br>

<h3 id="Dépendances" style="font-size:20px;">Dépendances</h3>

Dépendances requises dans "$HOME/SDL2" : 
  * <a href="https://www.libsdl.org/download-2.0.php">SDL2</a>
  * <a href="https://www.libsdl.org/projects/SDL_image/">SDL2Image</a>
  * <a href="https://github.com/libsdl-org/SDL_ttf">SDL2TTF</a>

<br>

Fonctionnement approuvé sur Ubuntu

<br>

<h3 id="Installation" style="font-size:20px;">Installation</h3>


```
git clone https://github.com/Alexis-42/Projet-L2-Tekken
```
Dans un terminal à l'emplacement du dossier, exécutez : ```make all```

<br>

<h3 id="Les commandes make" style="font-size:20px;">Les commandes make</h3>


```
make jouer    -> compile et lance le jeu

make docs     -> créer la doc dans le répertoire doc/html

make debug    -> compile et lance le jeu avec les hitbox

make all      -> compile le jeu puis le lance & créer la doc

make clean    -> enleve les .o & l'executable du jeu

make cleanall -> enleve les .o, l'executable du jeu & la doc

make ???????? -> secret
```

<br>

<h2 style="font-size:30px;" align = "center">Auteurs</h2>


<table align = "center">
  <tr align = "center">
    <td><a href="https://github.com/Alexis-42/Projet-L2-Tekken/commits?author=Alexis-42"><img src="https://avatars.githubusercontent.com/u/97942917?v=4" width="175px;" alt=""/><br /><sub><b>🧂 Alexis Guimbert 🧂</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Alexis-42/Projet-L2-Tekken/commits?author=Jck0day"><img src="https://avatars.githubusercontent.com/u/77964646?v=4" width="175px;" alt=""/><br /><sub><b>Charly P</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Alexis-42/Projet-L2-Tekken/commits?author=NoteletL"><img src="https://avatars.githubusercontent.com/u/97942901?v=4" width="175px;" alt=""/><br /><sub><b>Notelet Léo</b></sub></a><br /></td>
  </tr>
</table>
