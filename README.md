# 🎮 Tetris_C

Projet réalisé dans le cadre d'un cours universitaire en C, en binôme avec un camarade.  
Ce projet propose une version du Tetris jouable avec deux interfaces différentes : **ncurses** (console) et **SDL** (graphique).

🎥 [Voir la vidéo de présentation du projet](https://youtu.be/tC9EkMbOkYw)

---

## 🧠 Architecture

Le projet suit une architecture **MVC (Modèle-Vue-Contrôleur)** :

- **Modèle** : Gère la logique du jeu (matrice, pièces, collisions, score…)
- **Vue** :
  - `ncurses` : Affichage console simple
  - `SDL` : Affichage graphique avec images et sons
- **Contrôleur** : Intégré dans les vues, gère les entrées clavier et événements SDL.

---

## 📁 Arborescence
```
Tetris_C/ 
├── doc/ # Documentation 
├── src/ 
│ ├── images/ # Ressources d'images (SDL) 
│ ├── sons/ # Ressources sonores (SDL) 
│ ├── model/ # Logique du jeu (modèle) 
│ ├── view/ 
│ │ ├── sdl/ # Vue SDL 
│ │ └── ncurses/ # Vue ncurses 
├── build/ # Dossier de compilation 
└── main.c # Point d'entrée
```

---

## 🛠️ Compilation et Lancement

1. Compiler :
   
   `make` + les options suivantes :
   - `sdl` ou `ncurses` : choisir la vue
   - `[level]` (optionnel) : niveau de départ (0 à 19)
   - `[taille_fenetre]` (optionnel, pour SDL) : taille (1 à 10)

⚠️ Si vous voulez définir la taille de la fenêtre, vous devez d'abord spécifier un niveau.

---

## 🎮 Fonctionnalités

- Gestion complète du Tetris : déplacement, rotation, descente, lignes complétées
- Matrice de jeu avec gestion des collisions
- Système de score, niveaux, statistiques
- Sons et textures personnalisés avec SDL
- Contrôle via le clavier

---

## 📦 Structures principales

- `GameState` : État global du jeu
- `Piece` : Pièce active (forme, couleur, position…)
- `Matrix` : Grille du jeu avec cellules
- `Block` : Coordonnées d’un bloc de pièce

---

## 🖼️ Vue SDL

- Gestion des textures
- Sons joués selon les actions (rotation, ligne complétée…)
- Affichage visuel dynamique
- Fonction : `playSound(int index)`

---

## Vue ncurses

- Interface texte simple
- Affichage des scores, niveaux, statistiques
- Contrôle au clavier : déplacements, rotations, pause, quitter

---

## Boucle de jeu

1. Suppression de la pièce actuelle de la matrice
2. Calcul du mouvement ou de la rotation
3. Vérification des collisions
4. Insertion de la pièce mise à jour
5. Affichage
6. Répétition jusqu'à la fin de la partie

---

## 👥 Auteurs

- Brissy Axel
    🔗 [GitHub](https://github.com/oneblack74) - [itch.io](https://oneblack74.itch.io)
  
- Hurez Mattéo
